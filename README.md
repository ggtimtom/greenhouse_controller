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

### 1. The Concept
The core of this system uses **Olla** irrigation: unglazed porous clay pots buried next to plants. Water and dissolved nutrients seep through the clay walls only when the surrounding soil is dry enough, delivering moisture directly to the root zone. This physical feedback loop inherently prevents over-watering and leaching.

Our automation adds a **smart refilling and dosing layer**:
*   **Volumetric Dosing:** Instead of drift-prone pH sensors, we measure the exact water volume and dose fertilizer proportionally using a PWM-controlled pump.
*   **Automated Refill:** A solenoid valve refills the reservoir connected to the Olla pots.

<img width="144" height="256" alt="Olla Pot Example" src="https://github.com/user-attachments/assets/a56fa7fe-c856-4788-8397-1878a92c437d" />

### 2. Complete Hardware List

| Component | Description | Link |
| :--- | :--- | :--- |
| **Olla Irrigation Pots** | Unglazed porous clay pots for passive, self-regulating soil watering. | [🛒 Olla Pots](https://www.amazon.de/dp/B0GTMXBZ1L) |
| **ESP32 with Relay Module** | Control unit. ESP32 for logic, Relay for switching AC loads (Valve). Powered via VIN (12V). | [🛒 ESP32+Relay](https://www.amazon.de/dp/B0G2LLH6WY) |
| **Motor Driver (DRV8871)** | **PWM Motor Driver**. Allows precise speed control of the peristaltic pump via ESP32. Supports 6.5-45V. | [🛒 DRV8871](https://www.amazon.de/dp/B0DGTNVX41) |
| **Power Supply (Logic/Motor)** | **12V 1A DC Power Supply**. Powers ESP32, Flow Meter, and Pump. | [🛒 12V PSU](https://www.amazon.de/gp/product/B0FRRD6P44) |
| **Solenoid Valve (Hunter PGV-101)** | Professional irrigation valve with flow regulation. **Requires 24V AC**. | [🛒 Hunter Valve](https://www.amazon.de/dp/B09RT1QQX5) |
| **Power Supply (Valve)** | **24V AC Transformer**. Dedicated supply for the solenoid valve. | [🛒 24V AC PSU](https://www.amazon.de/dp/B0C19ND3TY) |
| **Peristaltic Pump** | Dosing pump for fertilizer. **Ensure 12V version is selected**. | [🛒 Pump](https://www.amazon.de/dp/B09S6QGP19) |
| **Water Flow Meter** | Hall-effect sensor. Connect to ESP32 **5V pin** for stable signal. | [🛒 Flow Meter](https://www.amazon.de/dp/B0C2GT6LHY) |
| **Waterproof Enclosure (IP65)** | Plastic housing (approx. 190x140x70mm) to protect all electronics. | [🛒 Enclosure](https://www.amazon.de/dp/B01NA7BEJV) |

*(Note: Verify exact pinouts on the product pages. Critical: Do not mix 24V AC and 12V DC lines.)*

#### How It Works
1.  **Measure**: Water flows through the **Flow Meter** (powered by ESP32 5V) into the reservoir. The ESP32 counts pulses to calculate the total volume.
2.  **Calculate**: Based on your configured ratio (e.g., `5ml fertilizer per 10L water`), the controller calculates the required pump runtime and speed.
3.  **Dose**: The **DRV8871 Driver** activates the **Peristaltic Pump** with precise PWM speed control, injecting the exact amount of concentrate.
4.  **Mix**: The solution mixes in the reservoir before passively seeping into the Olla pots.
5.  **Irrigate**: When the reservoir is full or on schedule, the **Hunter Valve** opens via the Relay Module to refill the Olla system.

**Advantages of This Approach:**
*   **No Sensor Drift**: Unlike pH probes, flow meters and peristaltic pumps do not drift over time.
*   **Precision Dosing**: PWM control allows for micro-dosing and soft-start, improving accuracy.
*   **Low Maintenance**: No fragile glass probes to clean. Only pump tubing needs occasional replacement.
*   **Cost-Effective**: Significantly cheaper than industrial pH/EC controllers.
*   **Reliable**: Mechanical dosing is robust against electrical noise.

## ⚡ Power & Wiring Architecture
The system safely separates high-power AC loads from sensitive DC logic within an IP65 enclosure.

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

### 📦 Enclosure & Installation Tips
*   **Cable Glands:** The included grommets may be too large for thin sensor wires. Consider adding **M12 or M16 cable glands** for a truly watertight seal.
*   **Mounting:** Use double-sided tape or plastic standoffs to secure the ESP32, DRV8871, and Relay board inside the box.
*   **Placement:** Mount the box in a shaded area to prevent overheating, as the enclosure is sealed.

*Safety Note: Ensure all 230V mains connections (inputs to the power supplies) are properly insulated. Ideally, place the power supplies outside the small enclosure or use a larger box with proper separation if mains voltage is present inside.*

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
- [x] **Hardware Selection**: Finalizing all components.
- [ ] **Wiring & Assembly**: Building the prototype in the IP65 enclosure.
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
