# 🌿 IoT-Based Smart Garden: Industrial Grade Irrigation System

This project implements a professional-grade automated irrigation system using the **ESP32**. The system is designed for high reliability, featuring integrated **Software Hysteresis** for hardware longevity and a **Temporal Fail-safe** mechanism to prevent environmental flooding.

---

## 📌 Engineering Objectives

The system provides a resilient, autonomous solution that optimizes water usage while protecting hardware components:
- **Precision Monitoring:** Real-time data acquisition via Soil Moisture (ADC) and environmental sensors.
- **Hardware Optimization:** Integrated Hysteresis logic to eliminate "Relay Chattering" (rapid on/off switching).
- **Safety Engineering:** Time-based watchdog to prevent pump burnout and accidental water waste.
- **Remote Orchestration:** Seamless integration with **Blynk IoT** for global monitoring and manual override.

---

## 🧰 System Components

| Component | Quantity | Purpose |
| :--- | :---: | :--- |
| **ESP32** | 1 | Central Processing & Dual-core Wi-Fi Management |
| **Capacitive Soil Sensor** | 1 | Corrosion-resistant Analog Moisture Detection |
| **Relay Module** | 1 | Galvanic Isolation for Water Pump Control |
| **DHT11 Sensor** | 1 | Ambient Temperature & Humidity Monitoring |
| **Breadboard** | 1 | Circuit assembly and prototyping |
| **Jumper Wires** | As needed | Inter-component signal and power connections |
| **Soil Container** | 1 | Environment for testing and demonstration |

---

## 🛠️ Technical Specifications & Pin Mapping

### **Hardware Architecture**
| Component | GPIO Pin | Function |
| :--- | :--- | :--- |
| **Soil Moisture Sensor** | GPIO 32 | Analog signal input (ADC) |
| **1-Channel Relay** | GPIO 33 | Digital output for Pump Control |
| **DHT11 Sensor** | GPIO 4 | Digital signal for Temp/Humidity |

---

## 💡 Operational Logic

The system is engineered to move beyond simple threshold switching by employing industrial control principles:

### **1. Control System Stability (Hysteresis)**
To protect the mechanical relay and pump from rapid cycling caused by sensor noise at the boundary, a dual-threshold loop is used:
- **Activation Threshold (30%):** Trigger Irrigation.
- **Deactivation Threshold (65%):** Terminate Irrigation once saturation is reached.
- **Result:** This significantly extends the operational life of the mechanical components.

### **2. Safety Watchdog (Temporal Fail-Safe)**
A background timer monitors the active state of the pump. If the system detects the pump has been active for more than **30 seconds** without a corresponding rise in soil moisture:
- **Action:** Automatic Emergency Shutdown.
- **Result:** Prevents property damage and pump damage in the event of tank depletion or sensor displacement.

---

## 💻 Firmware Architecture

- **Language:** C++ (Arduino Framework)
- **Cloud Platform:** Blynk IoT SDK
- **Key Logic Implementation:**
  - `map()` & `constrain()`: Standardizing 12-bit ADC values ($0$ to $4095$) to a human-readable $0-100\%$ scale.
  - `BlynkTimer`: Utilizing non-blocking timers instead of `delay()` to maintain constant Cloud connectivity.
  - **Emergency Lock:** A software interrupt that halts operation until the hardware state is manually verified.

---

## 📲 Remote Monitoring Interface

The **Blynk IoT Dashboard** provides:
- **Real-time Gauges:** Instant visualization of soil moisture and environmental metrics.
- **Historical Data:** Graphing moisture trends for precision agriculture analytics.
- **Push Alerts:** Instant notifications sent to the user if the safety watchdog is triggered.

---

## 🧪 Deployment & Testing

1. **Calibration:** Sensor baseline established using dry soil ($4095$ ADC) and saturated soil ($1000$ ADC).
2. **Safety Verification:** Simulated sensor failure during active watering to confirm the 30-second cutoff.
3. **Network Resilience:** Verified automatic reconnection logic for both local Wi-Fi and Blynk Cloud.

---

## 👨‍💻 Project Team (SVNIT)
- **Akshat Lakum** (U22EC040)  
- **Pratham** (U22EC051)  
- **Puneet Tiwari** (U22EC015)  
*Sardar Vallabhbhai National Institute of Technology*

---

## 📜 License
This project is open for educational use and can be scaled for professional smart agriculture applications.
