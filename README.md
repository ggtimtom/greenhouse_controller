# 🌿 Greenhouse Controller: Olla & ESPHome

**Automating irrigation and fertigation using ancient wisdom and modern technology.**

## The Challenge
Precisely dispensing the right amount of water for vegetables is a complex task for traditional controllers. Over-watering wastes resources and harms roots, while under-watering stresses plants. Conventional timer-based systems often fail to adapt to real-time soil conditions.

**The Fertilization Dilemma:**
Adding liquid fertilizer (fertigation) introduces even greater complexity. Continuous or imprecise dosing leads to critical issues:
*   **Over-fertilization & Leaching:** If irrigation volume isn't perfectly matched to plant uptake, excess fertilizer leaches out, wasting nutrients and polluting groundwater.
*   **Clogging:** Fertilizer salts can precipitate and clog fine emitters or valves.
*   **Sensor Drift & Maintenance:** Traditional pH/EC sensors require frequent calibration, are prone to drifting, and have a limited lifespan in nutrient-rich water.
*   **Inconsistent Concentration:** Traditional injector systems often deliver decreasing concentrations as the stock tank empties.

## The Solution: Olla Irrigation + Smart Volumetric Dosing
We combine a time-tested method with robust automation to solve these problems without fragile sensors.

### 1. Passive Watering with Olla
The **Olla** (unglazed porous clay pot) creates a passive, self-regulating irrigation system. Water and dissolved nutrients seep through the clay walls only when the surrounding soil is dry enough, delivering moisture directly to the root zone exactly when the plant needs it. This physical feedback loop inherently prevents over-watering and leaching.

<img width="144" height="256" alt="Olla Pot" src="https://github.com/user-attachments/assets/a56fa7fe-c856-4788-8397-1878a92c437d" />

### 2. Flow-Based Fertigation (No pH Sensors Needed)
Instead of relying on drift-prone pH/EC probes, this project implements a **volumetric dosing strategy**. We measure the exact volume of water and dose the fertilizer proportionally using a high-precision motor driver.

#### 💧 Hardware: Flow-Based Dosing System

| Component | Description | Voltage | Link |
| :--- | :--- | :--- | :--- |
| **ESP32 with Relay Module** | Control unit. ESP32 for logic, Relay for switching AC loads (Valve). | 3.3V/5V (Logic) | [🛒 ESP32+Relay](https://www.amazon.de/dp/B0G2LLH6WY) |
| **Motor Driver (DRV8871)** | **PWM Motor Driver**. Allows precise speed control of the peristaltic pump via ESP32. Requires 2 GPIOs. | 6.5-45V DC | [🛒 DRV8871](https://www.amazon.de/dp/B0DGTNVX41) |
| **Power Supply (Logic/Motor)** | **12V 1A DC Power Supply**. Powers ESP32 (via VIN), Flow Meter (via ESP32 5V), and Pump (via Driver). | **12V DC** | [🛒 12V PSU](https://www.amazon.de/gp/product/B0FRRD6P44) |
| **Solenoid Valve (Hunter PGV-101)** | Professional irrigation valve with flow regulation. | **24V AC** | [🛒 Hunter Valve](https://www.amazon.de/dp/B09RT1QQX5) |
| **Power Supply (Valve)** | **24V AC Transformer**. Dedicated supply for the solenoid valve. | **24V AC** | [🛒 24V AC PSU](https://www.amazon.de/dp/B0C19ND3TY) |
| **Peristaltic Pump** | Dosing pump. Connect to DRV8871 outputs. **Must be the 12V version!** | **12V DC** | [🛒 Pump](https://www.amazon.de/dp/B09S6QGP19) |
| **Water Flow Meter** | Hall-effect sensor. Connect to ESP32 **5V** pin for stable signal. | 5V DC | [🛒 Flow Meter](https://www.amazon.de/dp/B0C2GT6LHY) |

*(Note: Images are representative. Please verify exact pinouts and voltage requirements on the product pages.)*

#### How It Works
1.  **Measure**: Water flows through the **Flow Meter** (powered by ESP32 5V) into the reservoir. The ESP32 counts pulses to calculate the total volume.
2.  **Calculate**: Based on your configured ratio (e.g., `5ml fertilizer per 10L water`), the controller calculates the required pump runtime and speed.
3.  **Dose**: The **DRV8871 Driver** activates the **Peristaltic Pump** with precise PWM speed control, injecting the exact amount of concentrate.
4.  **Mix**: The solution mixes in the reservoir before passively seeping into the Olla pots.
5.  **Irrigate**: When the reservoir is full or on schedule, the **Hunter Valve** opens via the Relay Module to refill the Olla system (or directly water if configured).

**Advantages of This Approach:**
*   **No Sensor Drift**: Unlike pH probes, flow meters and peristaltic pumps do not drift over time.
*   **Precision Dosing**: PWM control allows for micro-dosing and soft-start, preventing splashing and improving accuracy.
*   **Low Maintenance**: No fragile glass probes to clean. Only pump tubing needs occasional replacement.
*   **Cost-Effective**: Significantly cheaper than industrial pH/EC controllers.
*   **Reliable**: Mechanical dosing is robust against electrical noise.

## ⚡ Power & Wiring Architecture
The system safely separates high-power AC loads from sensitive DC logic.

### 1. DC Circuit (12V Main)
*   **Source:** 12V 1A DC Power Supply.
*   **ESP32:** Connect to **VIN** pin (internal regulator steps down to 3.3V/5V). **Do not connect 12V to the 5V pin!**
*   **Flow Meter:** Connect `VCC` to the **ESP32 5V Pin**, `GND` to GND, `Signal` to GPIO.
*   **DRV8871 Driver:** `VM` to 12V, `GND` to common GND. Inputs (`IN1`, `IN2`) to ESP32 GPIOs.
*   **Pump:** Connected to Driver outputs (`OUT1`, `OUT2`).

### 2. AC Circuit (24V Valve)
*   **Source:** 24V AC Transformer.
*   **Valve:** Connected via Relay Module (NO/COM terminals).
*   **Safety:** The Relay Module acts as the bridge. **Never connect 24V AC directly to the ESP32 or Driver.**

*Safety Note: Ensure all 230V mains connections are properly insulated. Use an IP65 rated enclosure for greenhouse environments.*

## Key Features
- **Self-Regulating Watering**: Leverages the physical properties of Olla pots for perfect soil moisture.
- **Volumetric Fertigation**: Precise fertilizer dosing based on water flow, eliminating the need for pH/EC sensors.
- **PWM Pump Control**: Variable speed dosing for maximum accuracy.
- **Leach-Proof**: Passive Olla delivery prevents nutrient runoff.
- **Fully Local**: Runs on ESP32 hardware; no cloud dependency required.
- **Home Assistant Ready**: Native integration for dashboarding.

## 🚧 Project Status & Roadmap
*This project is currently under active development.*

- [x] **Concept & Design**: Defining the hybrid Olla/Volumetric system.
- [x] **Hardware Selection**: Finalizing components (ESP32, DRV8871, Hunter Valve, Sensors).
- [ ] **Wiring & Assembly**: Building the prototype in an IP65 enclosure.
- [ ] **Firmware Development**: Implementing pulse counting and PWM dosing logic in ESPHome.
- [ ] **Calibration**: Determining exact pump flow rates (ml/sec) at different PWM speeds.
- [ ] **Testing**: Validating water usage and nutrient delivery ratios.
- [ ] **Documentation**: Publishing wiring diagrams and code.

## 🔜 Next Steps
The complete source code (ESPHome YAML configuration) and detailed wiring diagrams will be published in the `/config` and `/docs` directories respectively.

## How to Contribute
We welcome contributions! Whether it's improving the firmware logic, designing 3D-printed parts for the reservoirs, or refining the dosing algorithms, please feel free to open an issue or submit a pull request.

---
*Stay tuned for the upcoming code release and detailed build instructions.*   
