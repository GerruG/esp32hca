#include <WiFi.h>
#include <HTTPClient.h>

// WiFi credentials
const char* ssid = "hallonsylt";       // Replace with your WiFi SSID
const char* password = "110b4l3p5";   // Replace with your WiFi password

// REST API endpoint
const char* api_url = "http://192.168.0.207:5000/api/motion"; // Replace with your Raspberry Pi's API URL

// PIR sensor pin
#define PIR_PIN 16

bool motion_detected = false;

// Connect to WiFi
void connectToWiFi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected!");
}

// Send motion data to the API
void sendToAPI(bool motion) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Begin HTTP request
    http.begin(api_url);
    http.addHeader("Content-Type", "application/json");

    // Construct JSON payload
    String jsonPayload = String("{\"motion\":") + (motion ? "true" : "false") + "}";

    // Send POST request
    int httpResponseCode = http.POST(jsonPayload);

    // Handle response
    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error sending POST: ");
      Serial.println(http.errorToString(httpResponseCode));
    }

    // Close connection
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);

  connectToWiFi();
}

void loop() {
  int pir_state = digitalRead(PIR_PIN);

  if (pir_state == HIGH && !motion_detected) {
    Serial.println("Motion Detected!");
    sendToAPI(true);
    motion_detected = true;
  } else if (pir_state == LOW && motion_detected) {
    Serial.println("No Motion.");
    sendToAPI(false);
    motion_detected = false;
  }

  delay(100);  // Small delay to stabilize readings
}
