Smart irrigation
#include <WiFi.h>
#include <ThingSpeak.h>

// ================= WIFI DETAILS =================
const char* ssid = "WIFI_NAME";
const char* password = "WIFI_PASSWORD";

// ================= THINGSPEAK =================
WiFiClient client;
unsigned long channelID = CHANNEL_ID;
const char* writeAPIKey = "WRITE_API_KEY";

// ================= PIN DEFINITIONS =================
#define MOISTURE_PIN 34
#define RELAY_PIN    26
#define LED_PIN      27
#define BUZZER_PIN   25

// ================= SETTINGS =================
// From your readings
// Wet  ≈ 1400–1600
// Dry  ≈ 4095
int threshold = 2500;

// ==================================================

void setup() {
  Serial.begin(9600);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Initial states
  digitalWrite(RELAY_PIN, HIGH);   // Pump OFF
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  // WiFi connect
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  ThingSpeak.begin(client);
}

void loop() {

  // --------- READ MOISTURE (AVERAGE) ---------
  int moisture = 0;
  for (int i = 0; i < 10; i++) {
    moisture += analogRead(MOISTURE_PIN);
    delay(5);
  }
  moisture = moisture / 10;

  Serial.print("Soil Moisture Value: ");
  Serial.println(moisture);

  int motorStatus;
  int soilStatus;

  // ----------------- DRY -----------------
  if (moisture > threshold) {
    digitalWrite(RELAY_PIN, LOW);     // Pump ON
    digitalWrite(LED_PIN, HIGH);      // LED ON
    digitalWrite(BUZZER_PIN, HIGH);   // Buzzer ON

    motorStatus = 1;   // ON
    soilStatus = 1;    // DRY
  }
  // ----------------- WET -----------------
  else {
    digitalWrite(RELAY_PIN, HIGH);    // Pump OFF
    digitalWrite(LED_PIN, LOW);       // LED OFF
    digitalWrite(BUZZER_PIN, LOW);    // Buzzer OFF

    motorStatus = 0;   // OFF
    soilStatus = 0;    // WET
  }

  // --------- SEND DATA TO THINGSPEAK ---------
  ThingSpeak.setField(1, moisture);
  ThingSpeak.setField(2, motorStatus);
  ThingSpeak.setField(3, soilStatus);

  int response = ThingSpeak.writeFields(channelID, writeAPIKey);

  if (response == 200) {
    Serial.println("ThingSpeak update successful");
  } else {
    Serial.print("ThingSpeak error: ");
    Serial.println(response);
  }

  // ThingSpeak needs minimum 15 sec delay
  delay(15000);
}
