# 🌿 Greenhouse Controller: Olla & ESPHome

**Automating irrigation and fertigation using ancient wisdom and modern technology.**

## The Challenge
Precisely dispensing the right amount of water for vegetables is a complex task for traditional controllers. Over-watering wastes resources and harms roots, while under-watering stresses plants. Conventional timer-based systems often fail to adapt to real-time soil conditions.

**The Fertilization Dilemma:**
Adding liquid fertilizer (fertigation) introduces even greater complexity. Continuous or imprecise dosing leads to critical issues:
*   **Over-fertilization & Leaching:** Excess fertilizer leaches out, wasting nutrients and polluting groundwater.
*   **Clogging:** Fertilizer salts precipitate and clog fine emitters.
*   **Sensor Drift:** Traditional pH/EC sensors require frequent calibration and have a limited lifespan.
*   **Inconsistent Concentration:** Traditional injectors deliver decreasing concentrations as the stock tank empties.

## The Solution: Olla Irrigation + Smart Volumetric Dosing
We combine a time-tested method with robust automation to solve these problems without fragile sensors.

### 1. The Concept
The core uses **Olla** irrigation: unglazed porous clay pots buried next to plants. Water and dissolved nutrients seep through the clay walls only when the surrounding soil is dry enough. This physical feedback loop inherently prevents over-watering.

My automation adds a **smart refilling and dosing layer**:
*   **Volumetric Dosing:** Measures exact water volume and doses fertilizer proportionally via a PWM-controlled pump.
*   **Hybrid Level Control:** Each unit has a reservoir with a mechanical float valve (fail-safe) and electronic float switches (smart monitoring).
*   **Upcycled Inlet:** Uses recycled PET bottles as weather-resistant funnels.

<img width="1129" height="646" alt="image" src="https://github.com/user-attachments/assets/0f221c64-054c-4aab-bddc-0d7ac60c2342" />

### 2. Complete Hardware List
## Royal Gardineer Olla Version

<img width="144" height="256" alt="Olla Pot Example" src="https://github.com/user-attachments/assets/a56fa7fe-c856-4788-8397-1878a92c437d" />
<img width="144" height="256" alt="oben" src="https://github.com/user-attachments/assets/51f7de96-0c81-4c9c-b6dc-a04482768458" />

| Component | Description | Link / Details |
| :--- | :--- | :--- |
| **Olla Irrigation Pots** | For small vegetables. | [🛒 Olla Pots](https://www.amazon.de/dp/B0GTMXBZ1L) |
| **Reservoir Box** | **Alutec Insert (Art. 75210)**. Dimensions: 131x91x102 mm. Serves as the water buffer tank. | [Alutec 75210](https://www.alutec.net) (EAN: 4014688752102, Toom Baumarkt) |
| **PET Bottle (Upcycled)** | **Milbona Latte Macchiato Zero (330ml)**. Top part heat-shrunk onto Olla/Reservoir as a funnel. | [Product Info](https://de.openfoodfacts.org/produkt/20036881/latte-macchiato-zero-milbona) |
| **3D-Printed Adapter** | Connects bottle thread to reservoir box. (File coming soon). | *STL File Pending* |
| **Sealing O-Ring** | Rubber gasket for the 3D-printed adapter to bottle connection. | [🛒 O-Ring Set](https://www.amazon.de/dp/B0D9Y21XV2) |

## Spang AquaSafe Version

| Component | Description | Link / Details |
| :--- | :--- | :--- |
| **Spang Flower Pots** | For plants that dont need much water. | [🛒 Spang Flower Pots](https://spang.de/blt-22-cm-m.l.-nat.-pal./001-220-001-000-0-P)|
| **Spang AquaSafe** | For vegetables. | [🛒 Spang AquaSafe](https://spang.de/aquasafe-set-16-cm-o.l.-nat.-ean-e-pal./304-160-101-000-1-E)|
| **Corner Connector** | Adaper to connect the water valve to the Lid on top of the pod. |[🛒 Corner Connector](https://www.amazon.de/dp/B0BPQMRYVR)|

## Both Versions
| Component | Description | Link / Details | Image |
| :--- | :--- | :--- | :--- |
| **Reservoir Float Valve** | Mini mechanical valve. Closes automatically when water reaches the top, preventing overflow. | [🛒 Float Valve](https://www.amazon.de/dp/B0D232RPMY) ||
| **Float Switch Sensors (2x)** | Magnetic reed switches for electronic level detection per unit (Top/Bottom). | [🛒 Float Switches](https://www.amazon.de/dp/B0F4DM4B91) | <img width="300" height="394" alt="image" src="https://github.com/user-attachments/assets/5238efe8-adc0-497c-b79f-5255a8658b90" /> |
| **ESP32 with Relay Module** | Control unit. ESP32 for logic, Relay for switching AC loads (Main Valve). Powered via VIN (12V). | [🛒 ESP32+Relay](https://www.amazon.de/dp/B0G2LLH6WY) ||
| **Motor Driver (DRV8871)** | **PWM Motor Driver**. Allows precise speed control of the peristaltic pump. Supports 6.5-45V. | [🛒 DRV8871](https://www.amazon.de/dp/B0DGTNVX41) ||
| **Power Supply (Logic/Motor)** | **12V 1A DC Power Supply**. Powers ESP32, Flow Meter, and Pump. | [🛒 12V PSU](https://www.amazon.de/gp/product/B0FRRD6P44) ||
| **Solenoid Valve (Hunter PGV-101)** | Professional main irrigation valve. **Requires 24V AC**. | [🛒 Hunter Valve](https://www.amazon.de/dp/B09RT1QQX5) ||
| **Power Supply (Valve)** | **24V AC Transformer**. Dedicated supply for the main solenoid valve. | [🛒 24V AC PSU](https://www.amazon.de/dp/B0C19ND3TY) ||
| **Peristaltic Pump** | Dosing pump for fertilizer. **Ensure 12V version is selected**. | [🛒 Pump](https://www.amazon.de/dp/B09S6QGP19) | |
| **Water Flow Meter** | Hall-effect sensor. Connect to ESP32 **5V pin** for stable signal. | [🛒 Flow Meter](https://www.amazon.de/dp/B0C2GT6LHY) | <img width="207" height="158" alt="image" src="https://github.com/user-attachments/assets/2a7016c1-b1b4-476b-81dc-7c690f1debaf" /> |
| **Waterproof Enclosure (IP65)** | Plastic housing (approx. 190x140x70mm) to protect all electronics. | [🛒 Enclosure](https://www.amazon.de/dp/B01NA7BEJV) ||
| **Pressure Reducer** | Reduce the water pressure for the microdrip system |[🛒 Pressure reducer](https://www.amazon.de/dp/B0BNLNFV2T)||
| **ESP Programmer** | The ESP on the Relaisboard has no USB port, so a programmer is needed|[🛒 ESP Programmer](https://www.amazon.de/AZDelivery-Konverter-kompatibel-Arduino-inklusive/dp/B089QJZ51Z)| <img width="523" height="208" alt="image" src="https://github.com/user-attachments/assets/accd82b8-e6af-4320-84e0-5d6968033ca4" /> |
| **Fertilizer Injector** | bring the fertilizer to the 13mm water pipe |[🛒 Injector]([https://www.amazon.de/dp/B0BNLNFV2T](https://www.amazon.de/dp/B0BNLP8M3P)||


*(Note: Verify exact pinouts on product pages. Critical: Do not mix 24V AC and 12V DC lines.)*

### 3. System Architecture

#### A. Upcycled Inlet & Reservoir
*   **Preparation:** The top of a **Milbona Latte Macchiato Zero** bottle is cut. Using a hot air gun, the plastic is carefully shrunk onto the opening of the Olla pot to create a watertight funnel.
*   **Connection:** A custom **3D-printed adapter** screws into the bottle neck and inserts into the **Alutec 75210 reservoir box**.
*   **Safety:** Inside the box, a **Mini Float Valve** mechanically stops water inflow when full. Two **Float Switches** (Top/Bottom) provide electronic status to the ESP32.

#### B. Flow-Based Fertigation (No pH Sensors)
1.  **Measure**: Water flows through the **Flow Meter** (powered by ESP32 5V). The ESP32 counts pulses to calculate total volume.
2.  **Dose**: The **DRV8871 Driver** activates the **Peristaltic Pump** with precise PWM speed control, injecting the exact fertilizer ratio (e.g., 5ml per 10L).
3.  **Mix**: The solution mixes in the flow before reaching the reservoirs.

#### C. Smart Reservoir Management (Hybrid Control)
1.  **Filling**: When the **Bottom Float Switch** signals "Empty", the ESP32 opens the main **Hunter Solenoid Valve**.
2.  **Distribution**: Water flows to all connected reservoirs in parallel.
3.  **Auto-Stop**:
    *   **Mechanical:** The **Mini Float Valve** in each box closes as it fills, preventing overflow even if electronics fail.
    *   **Electronic:** When the **Top Float Switch** signals "Full", the ESP32 immediately closes the main Hunter Valve.
4.  **Seeping**: Water slowly seeps from the reservoir into the buried Olla pot based on soil moisture demand.

**Benefits:**
*   **Sustainability**: Reuses PET bottles as robust funnels.
*   **Fail-Safe**: Mechanical valves prevent flooding.
*   **Scalability**: Multiple units on one main line.
*   **Precision**: PWM dosing ensures exact nutrient concentration.

## ⚡ Power & Wiring Architecture
The system safely separates high-power AC loads from sensitive DC logic within an IP65 enclosure.

### 1. DC Circuit (12V Main)
*   **Source:** 12V 1A DC Power Supply.
*   **ESP32:** Connect to **VIN** pin. **Do not connect 12V to the 5V pin!**
*   **Flow Meter:** Connect `VCC` to **ESP32 5V Pin**.
*   **Float Switches:** Connect to ESP32 GPIOs (with external pull-up).
*   **DRV8871 Driver:** `VM` to 12V, Inputs to ESP32 GPIOs.
*   **Pump:** Connected to Driver outputs.

### 2. AC Circuit (24V Valve)
*   **Source:** 24V AC Transformer.
*   **Valve:** Connected via Relay Module (NO/COM terminals).
*   **Safety:** **Never connect 24V AC directly to the ESP32.**

### 3. Electronic Float Switches

| Tank | Sensor | GPIO-Pin |
| :--- | :--- | :--- |
| **Tank 1** | Top | GPIO21 |
| **Tank 1** | Bottom | GPIO34 |
| **Tank 2** | Top | GPIO33 |
| **Tank 2** | Bottom | GPIO4 |
| **Tank 3** | Top | GPIO35 |
| **Tank 3** | Bottom | GPIO32 |
| **Tank 4** | Top | GPIO14 |
| **Tank 4** | Bottom | GPIO26 |
| **Tank 5** | Top | GPIO27 |
| **Tank 5** | Bottom | GPIO25 |
| **Tank 6** | Top | GPIO13 |
| **Tank 6** | Bottom | GPIO12 |


### 📦 Enclosure & Installation Tips
*   **Cable Glands:** Use **M12 or M16 cable glands** for sensor wires to maintain IP65 rating.
*   **Mounting:** Secure all boards (ESP32, Driver, Relay) with standoffs or double-sided tape.
*   **Placement:** Mount the enclosure in a shaded area to prevent overheating.

*Safety Note: Ensure all 230V mains connections (inputs to power supplies) are properly insulated. Ideally, place power supplies outside the enclosure.*

## Key Features
- **Self-Regulating Watering**: Olla pots release water only when soil is dry.
- **Upcycled Design**: Uses Milbona PET bottles and Alutec boxes.
- **Hybrid Safety**: Mechanical float valves + electronic sensors prevent overflow.
- **Volumetric Fertigation**: Precise dosing based on flow, no pH/EC sensors needed.
- **PWM Pump Control**: Variable speed for micro-dosing accuracy.
- **Scalable**: Multiple Olla units on a single main line.
- **Fully Local**: Runs on ESP32/ESPHome; no cloud dependency.

## ⚙️ Setup

<img width="377" height="832" alt="image" src="https://github.com/user-attachments/assets/ce796d12-75c6-403c-9cb6-9b62e208acd5" />

  
## 💧 Flowmeter Calibration

To ensure precise water measurement, the flowmeter must be calibrated after installation. Since the correction factor depends on the specific sensor and flow conditions, please follow this one-time process:

### Step-by-Step Instructions

1.  **Preparation:** Ensure a measuring container (at least 10 liters) is ready.
2.  **Reset Water Meter:**
    *   Go to your Home Assistant Dashboard.
    *   Press the '1. Reset Water Meter.' Button.
3.  **Perform Measurement:**
    *   Open the water valve and dispense **exactly 10 liters**.
    *   Close the valve immediately.
4.  **Read Value & Calculate Factor:**
    *   In Home Assistant, press the button '3. Set Correction Factor.' to set Correction Factor.

> **Note:** After setting the factor, the factor will immediately display in configuration.

## 🧪 Fertilizer Pump Calibration

To ensure accurate dosing, the fertilizer pump must be calibrated to determine how many milliliters (ml) of fertilizer are dispensed when 10 liters of water flow through the system at maximum PWM.

### Step-by-Step Instructions

1.  **Connect System:** Attach the liquid fertilizer container to the peristaltic pump intake and ensure the output line is connected to the main water flow path.
2.  **Prime the Pump:**
    *   In Home Assistant, activate the switch/button **"Max PWM Fertilizer Pump"**.
    *   Let it run until all air bubbles are purged from the pump head and tubing, and liquid flows steadily.
    *   Turn the pump **OFF**.
3.  **Prepare Measurement:** Place a graduated cylinder or measuring cup under the fertilizer outlet.
4.  **Dispense Test Volume:**
    *   Activate the **"Max PWM Fertilizer Pump"** again.
    *   Flow exactly **10 Liters** of water (monitor your calibrated water meter).
    *   Stop the fertilizer pump immediately when the 10L water mark is reached.
5.  **Measure & Set Factor:**
    *   Measure the exact volume of fertilizer dispensed in **milliliters (ml)**.
    *   Enter the measured volume (e.g., `15` for 15ml) in the `max PWM 10l` field.
6.  ** Do the same with min PWM

> **Note:** This value represents **ml of fertilizer per 10L of water**. The system will use this ratio to calculate the required pump PWM for any target dosage.   

## 📊 Fertilizer Dosing Strategies

When calibrating your system, you can choose between two common fertilization strategies. The value you enter into the **"Fertilizer per 10L"** field depends on which method you select.

### Strategy 1: Periodic Dosing (Label Recommendation)
*Follow the manufacturer's standard advice (e.g., fertilize 1–2 times per week with the full recommended dose, water only at other times).*

*   **How it works:** You configure your automation to activate the fertilizer pump only on specific days (e.g., Monday and Thursday). On other watering events, only the water valve opens.
*   **Calculation for "Fertilizer per 10L":**
    Enter the **full recommended dose** (in ml) that the manufacturer suggests for a single application per 10L of water.
    > *Example:* If the label says "Add 15ml per 10L, twice a week", enter **15** into the field. Your automation must handle the schedule (only run pump on Tue/Fri).

### Strategy 2: Continuous Dosing (Constant Feed)
*Dilute the fertilizer dose and apply it with every single watering event.*

*   **How it works:** The fertilizer pump runs every time the irrigation system activates, providing a steady, low-level nutrient supply. This prevents nutrient peaks and troughs, often leading to more consistent growth.
*   **Calculation for "Fertilizer per 10L":**
    You must mathematically reduce the weekly dose based on your watering frequency.
    $$ \text{Value to Enter} = \frac{\text{Weekly Recommended Dose}}{\text{Number of Waterings per Week}} $$
    
    > *Example:*
    > *   Label recommendation: **20ml** per 10L, **2 times** per week (Total weekly dose = 40ml).
    > *   Your watering schedule: You water **every day** (7 times per week).
    > *   Calculation: $40\text{ml} / 7 \approx 5.7\text{ml}$.
    > *   **Enter 5.7** into the "Fertilizer per 10L" field.

### Summary Table

| Strategy | Frequency | Input Value for "Fertilizer per 10L" | Automation Requirement |
| :--- | :--- | :--- | :--- |
| **Periodic** | 1–2x / week | Full single dose (e.g., 15ml) | Schedule pump only on specific days |
| **Continuous** | Every watering | (Weekly Total Dose) ÷ (Waterings/Week) | Run pump with every water cycle |

> **Tip:** Continuous dosing (Strategy 2) is often preferred for automated systems with frequent, short watering cycles (like drip irrigation or Olla refills), as it mimics a natural nutrient supply and reduces the risk of fertilizer burn.

## 🛡️ 3-Level Safety System Against Continuous Irrigation

To prevent accidental overwatering, water damage, or fertilizer overdose, the system implements three independent safety layers. All protections run **locally on the ESP**, ensuring they function even if WiFi or Home Assistant fails.

### 1. Timeout "No Fertilizer" (Water Only)
*   **Target:** Switch `Water`
*   **Function:** Limits the maximum runtime for pure water irrigation cycles.
*   **Configuration:** Set the `Timeout no fertilizer` field (e.g., `130 s`).
*   **Scenario:** Prevents a single watering cycle from running indefinitely due to an automation error or stuck logic.

### 2. Timeout "With Fertilizer" (Combined)
*   **Target:** Switch `Water with Fertilizer`
*   **Function:** Limits the maximum runtime for combined water and fertilizer cycles.
*   **Configuration:** Set the `Timeout with fertilizer` field (e.g., `130 s`).
*   **Scenario:** Prevents both overwatering and dangerous fertilizer overdosing if the dosing pump fails to stop.

### 3. Hard Stop at Liters (Total Volume Limit)
*   **Target:** Global System (Water + Fertilizer)
*   **Function:** Immediately shuts down **all** pumps and valves once a defined total water volume has been dispensed.
*   **Configuration:** Set the `Stop at Liters` field (e.g., `200 L`).
*   **Scenario:** 
    *   Acts as the ultimate fail-safe against tank depletion (running the pump dry).
    *   Stops irrigation regardless of active timers if a leak causes excessive water usage.
    *   Provides a hard cap on per-cycle consumption to protect the physical infrastructure.

> **Note:** The `Stop at Liters` limit requires a calibrated flowmeter. Ensure your flowmeter is calibrated (see *Flowmeter Calibration* section) for this safety feature to work accurately.  

## 🚧 Project Status & Roadmap
*This project is currently under active development.*

- [x] **Concept & Design**: Hybrid Olla/Volumetric system with upcycled reservoirs.
- [x] **Hardware Selection**: All components finalized (Milbona, Alutec, Electronics).
- [ ] **3D Modeling**: Designing the bottle-to-box adapter (STL pending).
- [ ] **Wiring & Assembly**: Building the prototype in the IP65 enclosure.
- [ ] **Firmware Development**: Implementing flow counting, PWM dosing, and float-switch logic.
- [ ] **Calibration**: Determining pump flow rates at various PWM speeds.
- [ ] **Testing**: Validating multi-unit scaling and nutrient ratios.
- [ ] **Documentation**: Publishing wiring diagrams and code.

## 🔜 Next Steps
The complete source code (ESPHome YAML configuration), 3D print files (STL), and detailed wiring diagrams will be published in the `/config`, `/stl`, and `/docs` directories.

## How to Contribute
We welcome contributions! Whether it's improving the firmware logic, optimizing the 3D adapter design, or refining the dosing algorithms, please feel free to open an issue or submit a pull request.

---
*Stay tuned for the upcoming code release and detailed build instructions.*   
