# 🌿 IoT-Based Smart Garden: Industrial Grade Irrigation System

This project implements a professional-grade automated irrigation system using the **ESP32**. Unlike basic hobbyist projects, this system features **Software Hysteresis** for hardware longevity and a **Temporal Fail-safe** mechanism to prevent environmental flooding.

---

## 📌 Engineering Objectives

The goal was to build a resilient, autonomous system that optimizes water usage while protecting hardware components:
- **Precision Monitoring:** Real-time data acquisition via Soil Moisture (ADC) and DHT sensors.
- **Hardware Optimization:** Integrated Hysteresis logic to prevent "Relay Chattering" (rapid on/off switching).
- **Safety Engineering:** Time-based watchdog to prevent pump burnout or accidental flooding.
- **Remote Orchestration:** Seamless integration with **Blynk IoT** for global monitoring and manual override.

---

## 🛠️ Technical Specifications & Circuitry



### **Hardware Architecture**
| Component | GPIO Pin | Function |
| :--- | :--- | :--- |
| **ESP32** | N/A | Central Processing & Dual-core Wi-Fi Management |
| **Capacitive Soil Sensor** | GPIO 32 | Corrosion-resistant Analog Moisture Detection |
| **1-Channel Relay** | GPIO 33 | Galvanic Isolation for Water Pump Control |
| **DHT11 Sensor** | GPIO 4 | Ambient Temperature & Humidity Monitoring |

---

## 💡 Advanced Engineering Features (The "Pro" Edge)

To move from a prototype to a deployment-ready solution, I implemented two critical engineering upgrades:

### **1. Software Hysteresis (Control System Stability)**
To prevent the relay from toggling rapidly when moisture is exactly at the boundary (noise), I implemented a dual-threshold system:
- **Low Threshold (30%):** Trigger Irrigation.
- **High Threshold (65%):** Terminate Irrigation.
- **Benefit:** This significantly extends the operational life of the mechanical relay and prevents pump motor wear.

### **2. Temporal Fail-Safe (Safety Watchdog)**
If the system detects the pump has been active for more than **30 seconds** without a significant change in soil moisture, it automatically triggers an **Emergency Shutdown**.
- **Benefit:** This prevents water waste and property damage in case of a burst pipe, water tank depletion, or a disconnected sensor.

---

## 💻 Logic Flow & Code Architecture

- **Language:** C++ (Arduino Framework)
- **Frameworks:** Blynk IoT SDK
- **Key Logic:**
  - `map()` & `constrain()`: Standardizing 12-bit ADC values ($0$ to $4095$) to a $0-100\%$ scale.
  - `BlynkTimer`: Utilizing non-blocking timers instead of `delay()` to ensure the ESP32 remains responsive to Cloud commands.
  - **Fail-safe Interrupt:** A software lock that prevents pump restarts until a manual system reset/check is performed.

---

## 📲 Remote Monitoring Interface

The system utilizes a custom **Blynk IoT Dashboard** featuring:
- **Real-time Gauge:** Visual moisture percentage and environmental data.
- **Historical Logs:** Graphing temperature and humidity trends for data-driven gardening.
- **Emergency Alerts:** Push notifications sent to the user if the Fail-Safe watchdog is triggered.

---

## 🚀 Deployment & Testing

1. **Calibration:** The sensor was calibrated using dry soil ($4095$ ADC) and saturated soil ($1000$ ADC).
2. **Stress Test:** Simulated sensor failure by removing the probe from soil during watering to verify the Fail-Safe cutoff.
3. **Resilience:** Verified automatic reconnection logic for Wi-Fi and Blynk Cloud after power interruptions.

---

## 👨‍💻 Project Team (SVNIT)
- **Akshat Lakum** (U22EC040)  
- **Pratham** (U22EC051)  
- **Puneet Tiwari** (U22EC015)  
*Sardar Vallabhbhai National Institute of Technology*

---

## 📜 License
This project is open for educational use and can be extended to full-scale smart agriculture systems.