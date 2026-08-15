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

![Olla Pot](https://github.com/user-attachments/assets/a56fa7fe-c856-4788-8397-1878a92c437d)

### 2. Flow-Based Fertigation (No pH Sensors Needed)
Instead of relying on drift-prone pH/EC probes, this project implements a **volumetric dosing strategy**. We measure the exact volume of water and dose the fertilizer proportionally.

#### 💧 Hardware: Flow-Based Dosing System

| Component | Description | 
| :--- | :--- | :--- |
| **Peristaltic Pump** | High-precision dosing pump for liquid fertilizer. Adjustable flow rate via voltage/PWM. <br> [🛒 Buy on Amazon (DE)](https://www.amazon.de/dp/B09S6QGP19)  |
| **Water Flow Meter** | Hall-effect sensor to measure exact water volume passing through the main line. Essential for calculating the dosing ratio. <br> [🛒 Buy on Amazon (DE)](https://www.amazon.de/dp/B0C2GT6LHY) |

*(Note: Images are representative. Please verify exact appearance on the product pages.)*

#### How It Works
1.  **Measure**: Water flows through the **Flow Meter** into the reservoir. The ESP32 counts pulses to calculate the total volume (e.g., 10 Liters).
2.  **Calculate**: Based on your configured ratio (e.g., `5ml fertilizer per 10L water`), the controller calculates the required pump runtime.
3.  **Dose**: The **Peristaltic Pump** activates for the calculated duration, injecting the precise amount of concentrate into the water stream or reservoir.
4.  **Mix**: The solution mixes in the reservoir before passively seeping into the Olla pots.

**Advantages of This Approach:**
*   **No Sensor Drift**: Unlike pH probes, flow meters and peristaltic pumps do not drift over time.
*   **Low Maintenance**: No fragile glass probes to clean or replace. Only the pump tubing may need occasional replacement.
*   **Cost-Effective**: Significantly cheaper than industrial pH/EC controllers.
*   **Reliable**: Mechanical dosing is robust against electrical noise and water quality changes.

## Key Features
- **Self-Regulating Watering**: Leverages the physical properties of Olla pots for perfect soil moisture.
- **Volumetric Fertigation**: Precise fertilizer dosing based on water flow, eliminating the need for pH/EC sensors.
- **Leach-Proof**: Passive Olla delivery prevents nutrient runoff even if the reservoir is full.
- **Smart Refilling**: ESPHome-controlled pumps automatically keep Olla reservoirs filled with optimized nutrient solution.
- **Fully Local**: Runs on ESP32/ESP8266 hardware; no cloud dependency required.
- **Home Assistant Ready**: Native integration for dashboarding and advanced automation logic.

## 🚧 Project Status & Roadmap
*This project is currently under active development.*

- [x] **Concept & Design**: Defining the hybrid Olla/Volumetric system.
- [ ] **Hardware Setup**: Wiring ESP32, peristaltic pump, and flow meter.
- [ ] **Firmware Development**: Implementing pulse counting and dosing logic in ESPHome.
- [ ] **Calibration**: Determining exact pump flow rates (ml/sec) and flow meter factors.
- [ ] **Testing**: Validating water usage and nutrient delivery ratios.
- [ ] **Documentation**: Finalizing wiring diagrams and build guides.

## 🔜 Next Steps
The complete source code (ESPHome YAML configuration) and detailed wiring diagrams will be published in the `/config` and `/docs` directories respectively.

## How to Contribute
We welcome contributions! Whether it's improving the firmware logic, designing 3D-printed parts for the reservoirs, or refining the dosing algorithms, please feel free to open an issue or submit a pull request.

---
*Stay tuned for the upcoming code release and detailed build instructions.*   
