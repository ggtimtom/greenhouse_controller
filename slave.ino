#include <SoftwareSerial.h>
#include <ModbusRTUSlave.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define SLAVE_ID 1          
#define SENSOR_PIN 2        // Hall-Sensor Signal des Durchflussmessers
#define PIN_TANK_VOLL 4     // Schwimmerschalter oben (Voll-Melder)
#define PIN_TANK_LEER 5     // Schwimmerschalter unten (Leer-Melder)
#define ONE_WIRE_BUS 6      // DS18B20 Datenleitung (mit 4,7k Pull-Up gegen 5V!)

// RS485 Pins für SoftwareSerial zum Adapter (mit 10k Pull-Up an Pin 10 gegen 5V!)
#define SOFT_RX_PIN 10  
#define SOFT_TX_PIN 11  

const float CALIBRATION_FACTOR = 73.0; 

volatile unsigned long pulseCount = 0; 
unsigned long oldTime = 0;

float flowRate = 0.0;
unsigned long totalMilliLiters = 0;

// Array auf 5 Register erweitert:
// Register 0: Flussrate | Register 1&2: Gesamtmenge | Register 3: Schalter | Register 4: Temperatur
uint16_t holdingRegisters[5] = {0, 0, 0, 0, 0};

// OneWire und DallasTemperature Instanzen erstellen
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tempSensors(&oneWire);

SoftwareSerial mySerial(SOFT_RX_PIN, SOFT_TX_PIN);
ModbusRTUSlave modbus(mySerial);

void pulseCounter() {
  pulseCount++;
}

void setup() {
  mySerial.begin(9600); 

  // Modbus für 5 Register konfigurieren und starten
  modbus.configureHoldingRegisters(holdingRegisters, 5);
  modbus.begin(SLAVE_ID, 9600);

  // DS18B20 initialisieren
  tempSensors.begin();

  pinMode(SENSOR_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), pulseCounter, FALLING);
  
  pinMode(PIN_TANK_VOLL, INPUT_PULLUP);
  pinMode(PIN_TANK_LEER, INPUT_PULLUP);
  
  oldTime = millis();
}

void loop() {
  unsigned long currentMillis = millis();

  // Alle Sensordaten jede Sekunde berechnen/auslesen
  if ((currentMillis - oldTime) >= 1000) {
    unsigned long timePassed = currentMillis - oldTime;
    oldTime = currentMillis;
    
    // 1. DURCHFLUSS
    noInterrupts(); 
    unsigned long copyPulseCount = pulseCount;
    pulseCount = 0; 
    interrupts(); 
    
    flowRate = ((1000.0 / timePassed) * copyPulseCount) / CALIBRATION_FACTOR;
    totalMilliLiters += (flowRate / 60.0) * timePassed;

    // 2. SCHWIMMERSCHALTER
    uint16_t tankVoll = (digitalRead(PIN_TANK_VOLL) == HIGH) ? 1 : 0;
    uint16_t tankLeer = (digitalRead(PIN_TANK_LEER) == HIGH) ? 1 : 0;

    // 3. TEMPERATUR (DS18B20)
    tempSensors.requestTemperatures(); // Messung triggern
    float tempC = tempSensors.getTempCByIndex(0); // Wert auslesen
    
    // Fehler abfangen (falls Sensor nicht angeschlossen oder Kabelbruch)
    uint16_t modbusTemp = 0;
    if (tempC != DEVICE_DISCONNECTED_C) {
      modbusTemp = (uint16_t)(tempC * 100.0); // Z.B. 23.54 °C wird zu 2354
    }

    // --- MODBUS REGISTER BEFÜLLEN ---
    holdingRegisters[0] = (uint16_t)(flowRate * 100.0);
    holdingRegisters[1] = (uint16_t)(totalMilliLiters >> 16);   
    holdingRegisters[2] = (uint16_t)(totalMilliLiters & 0xFFFF); 
    holdingRegisters[3] = (tankVoll) | (tankLeer << 1);
    holdingRegisters[4] = modbusTemp; // Neues Register 4 belegen
  }

  // Modbus-Abfragen im Hintergrund beantworten
  modbus.poll();
}
