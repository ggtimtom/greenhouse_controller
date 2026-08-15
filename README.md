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
*   **Hybrid Level Control:** Each Olla unit has its own reservoir with a mechanical float valve (fail-safe) and electronic float switches (smart monitoring).

<img width="144" height="256" alt="Olla Pot Example" src="https://github.com/user-attachments/assets/a56fa7fe-c856-4788-8397-1878a92c437d" />

### 2. Complete Hardware List

| Component | Description | Link |
| :--- | :--- | :--- |
| **Olla Irrigation Pots** | Unglazed porous clay pots for passive, self-regulating soil watering. | [🛒 Olla Pots](https://www.amazon.de/dp/B0GTMXBZ1L) |
| **Reservoir Float Valve** | Mini mechanical valve. Closes automatically when water reaches the top, preventing overflow. Allows parallel connection. | [🛒 Float Valve](https://www.amazon.de/dp/B0D232RPMY) |
| **Float Switch Sensors (2x)** | Magnetic reed switches for electronic level detection per unit (Top/Bottom). | [🛒 Float Switches](https://www.amazon.de/dp/B0F4DM4B91) |
| **ESP32 with Relay Module** | Control unit. ESP32 for logic, Relay for switching AC loads (Main Valve). Powered via VIN (12V). | [🛒 ESP32+Relay](https://www.amazon.de/dp/B0G2LLH6WY) |
| **Motor Driver (DRV8871)** | **PWM Motor Driver**. Allows precise speed control of the peristaltic pump via ESP32. Supports 6.5-45V. | [🛒 DRV8871](https://www.amazon.de/dp/B0DGTNVX41) |
| **Power Supply (Logic/Motor)** | **12V 1A DC Power Supply**. Powers ESP32, Flow Meter, and Pump. | [🛒 12V PSU](https://www.amazon.de/gp/product/B0FRRD6P44) |
| **Solenoid Valve (Hunter PGV-101)** | Professional main irrigation valve with flow regulation. **Requires 24V AC**. | [🛒 Hunter Valve](https://www.amazon.de/dp/B09RT1QQX5) |
| **Power Supply (Valve)** | **24V AC Transformer**. Dedicated supply for the main solenoid valve. | [🛒 24V AC PSU](https://www.amazon.de/dp/B0C19ND3TY) |
| **Peristaltic Pump** | Dosing pump for fertilizer. **Ensure 12V version is selected**. | [🛒 Pump](https://www.amazon.de/dp/B09S6QGP19) |
| **Water Flow Meter** | Hall-effect sensor. Connect to ESP32 **5V pin** for stable signal. | [🛒 Flow Meter](https://www.amazon.de/dp/B0C2GT6LHY) |
| **Waterproof Enclosure (IP65)** | Plastic housing (approx. 190x140x70mm) to protect all electronics. | [🛒 Enclosure](https://www.amazon.de/dp/B01NA7BEJV) |

*(Note: Verify exact pinouts on the product pages. Critical: Do not mix 24V AC and 12V DC lines.)*

### 3. System Architecture

#### A. Flow-Based Fertigation (No pH Sensors)
1.  **Measure**: Water flows through the **Flow Meter** (powered by ESP32 5V) into the main line. The ESP32 counts pulses to calculate total volume.
2.  **Dose**: The **DRV8871 Driver** activates the **Peristaltic Pump** with precise PWM speed control, injecting the exact ratio of fertilizer concentrate (e.g., 5ml per 10L).
3.  **Mix**: The solution mixes in the flow or a small mixing chamber before reaching the Olla reservoirs.

#### B. Smart Reservoir Management (Per-Olla Control)
Each Olla pot is connected to its own small reservoir box equipped with a hybrid control system:
1.  **Filling**: When the **Bottom Float Switch** signals "Empty", the ESP32 opens the main **Hunter Solenoid Valve**.
2.  **Distribution**: Water flows to all connected reservoirs in parallel.
3.  **Auto-Stop (Mechanical)**: As a reservoir fills, its **Mini Float Valve** mechanically restricts and eventually stops the flow when full. This prevents overflow even if electronics fail.
4.  **Auto-Stop (Electronic)**: When the **Top Float Switch** signals "Full", the ESP32 immediately closes the main Hunter Valve.
5.  **Seeping**: Water slowly seeps from the reservoir into the buried Olla pot based on soil moisture demand.

**Benefits of this Setup:**
*   **Fail-Safe**: Mechanical float valves prevent flooding if the ESP32 or main valve sticks.
*   **Scalability**: Connect multiple Olla units to one main line. The system pressurizes until *all* units are full.
*   **Precision**: PWM dosing ensures exact nutrient concentration without expensive sensors.
*   **Low Maintenance**: No pH probes to calibrate; robust mechanical components.

## ⚡ Power & Wiring Architecture
The system safely separates high-power AC loads from sensitive DC logic within an IP65 enclosure.

### 1. DC Circuit (12V Main)
*   **Source:** 12V 1A DC Power Supply.
*   **ESP32:** Connect to **VIN** pin. **Do not connect 12V to the 5V pin!**
*   **Flow Meter:** Connect `VCC` to **ESP32 5V Pin**.
*   **Float Switches:** Connect to ESP32 GPIOs (with internal pull-up/down as needed).
*   **DRV8871 Driver:** `VM` to 12V, Inputs to ESP32 GPIOs.
*   **Pump:** Connected to Driver outputs.

### 2. AC Circuit (24V Valve)
*   **Source:** 24V AC Transformer.
*   **Valve:** Connected via Relay Module (NO/COM terminals).
*   **Safety:** **Never connect 24V AC directly to the ESP32.**

### 📦 Enclosure & Installation Tips
*   **Cable Glands:** Use **M12 or M16 cable glands** for sensor wires to maintain IP65 rating.
*   **Mounting:** Secure all boards (ESP32, Driver, Relay) with standoffs or double-sided tape.
*   **Placement:** Mount the enclosure in a shaded area to prevent overheating.

*Safety Note: Ensure all 230V mains connections (inputs to power supplies) are properly insulated. Ideally, place power supplies outside the enclosure or use a larger box with proper separation.*

## Key Features
- **Self-Regulating Watering**: Olla pots release water only when soil is dry.
- **Hybrid Safety**: Mechanical float valves + electronic sensors prevent overflow.
- **Volumetric Fertigation**: Precise dosing based on flow, no pH/EC sensors needed.
- **PWM Pump Control**: Variable speed for micro-dosing accuracy.
- **Scalable**: Multiple Olla units on a single main line.
- **Fully Local**: Runs on ESP32/ESPHome; no cloud dependency.

## 🚧 Project Status & Roadmap
*This project is currently under active development.*

- [x] **Concept & Design**: Hybrid Olla/Volumetric system with fail-safe reservoirs.
- [x] **Hardware Selection**: All components finalized.
- [ ] **Wiring & Assembly**: Building the prototype in the IP65 enclosure.
- [ ] **Firmware Development**: Implementing flow counting, PWM dosing, and float-switch logic.
- [ ] **Calibration**: Determining pump flow rates at various PWM speeds.
- [ ] **Testing**: Validating multi-unit scaling and nutrient ratios.
- [ ] **Documentation**: Publishing wiring diagrams and code.

## 🔜 Next Steps
The complete source code (ESPHome YAML configuration) and detailed wiring diagrams will be published in the `/config` and `/docs` directories.

## How to Contribute
We welcome contributions! Whether it's improving the firmware logic, designing 3D-printed parts for the reservoirs, or refining the dosing algorithms, please feel free to open an issue or submit a pull request.

---
*Stay tuned for the upcoming code release and detailed build instructions.*   
