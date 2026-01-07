// Define Blynk Template ID and Template Name
#define BLYNK_TEMPLATE_ID "TMPL37jakfh57"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "oeUoh0BDkpzqtnuoRK-E_0bb6YI6J4Le"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// --- Configuration ---
const int relayPin = 33;
const int moistureSensorPin = 32;

// --- Advanced Engineering Thresholds ---
const int DRY_THRESHOLD = 30;   // Start watering at 30%
const int WET_THRESHOLD = 65;   // Stop watering at 65% (Hysteresis)
const unsigned long MAX_PUMP_TIME = 30000; // 30 seconds Fail-safe

// Variables
int moistureLevel;
bool isPumpRunning = false;
unsigned long pumpStartTime = 0;
bool systemError = false; // To lock system if fail-safe triggers

BlynkTimer timer;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Galaxy M14 5G 22CF";
char pass[] = "akshatlakum";

void sendSoilData() {
  if (systemError) {
    Serial.println("SYSTEM LOCKED: Check for leaks or sensor failure.");
    Blynk.virtualWrite(V6, "ERROR: Check Hardware"); // Send alert to Blynk
    return;
  }

  int rawValue = analogRead(moistureSensorPin);
  
  // Note for Interview: 4095 is dry, ~1000 is wet for most capacitive sensors
  moistureLevel = map(rawValue, 4095, 1000, 0, 100);
  moistureLevel = constrain(moistureLevel, 0, 100);

  Serial.print("Moisture: "); Serial.print(moistureLevel); Serial.println("%");
  Blynk.virtualWrite(V5, moistureLevel);

  // --- Logic with Hysteresis & Fail-safe ---
  
  // 1. Start Pump logic
  if (moistureLevel < DRY_THRESHOLD && !isPumpRunning) {
    digitalWrite(relayPin, HIGH);
    isPumpRunning = true;
    pumpStartTime = millis();
    Serial.println("Relay ON - Watering started.");
  } 
  
  // 2. Stop Pump logic (Hysteresis)
  else if (moistureLevel >= WET_THRESHOLD && isPumpRunning) {
    digitalWrite(relayPin, LOW);
    isPumpRunning = false;
    Serial.println("Relay OFF - Target moisture reached.");
  }

  // 3. Fail-safe Check
  if (isPumpRunning && (millis() - pumpStartTime > MAX_PUMP_TIME)) {
    digitalWrite(relayPin, LOW); // Force shut off
    isPumpRunning = false;
    systemError = true; 
    Serial.println("CRITICAL ERROR: Pump running too long. Potential Leak!");
  }
}

void setup() {
  Serial.begin(115200); // Higher baud rate is standard for ESP32
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  
  analogReadResolution(12);

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(5000L, sendSoilData);
  
  Serial.println("System Ready - Advanced IoT Garden Controller");
}

void loop() {
  Blynk.run();
  timer.run();
}