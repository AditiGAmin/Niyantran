#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

// ---------- Pin definitions ----------
#define RAIN_SENSOR_PIN 34
#define DHTPIN 4
#define DHTTYPE DHT11
#define TRIG_PIN 12
#define ECHO_PIN 13

// ---------- Sensor objects ----------
DHT dht(DHTPIN, DHTTYPE);

// ---------- WiFi credentials ----------
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// ---------- Server endpoint ----------
String serverName = "http://YOUR_PC_IP:5000/predict";

// ---------- Ultrasonic function ----------
float readUltrasonic() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2;

  return distance;
}

void setup() {

  Serial.begin(115200);

  dht.begin();

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // ---------- Connect WiFi ----------
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected");
}

void loop() {

  // ---------- Rain Sensor ----------
  int rainValue = analogRead(RAIN_SENSOR_PIN);

  Serial.print("Rain Sensor: ");
  Serial.println(rainValue);

  // ---------- Temperature & Humidity ----------
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" °C  ");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // ---------- Ultrasonic Water Level ----------
  float waterLevel = readUltrasonic();

  Serial.print("Water Level Distance: ");
  Serial.print(waterLevel);
  Serial.println(" cm");

  // ---------- Send Data to ML Server ----------
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    String jsonData = "{\"rain\":" + String(rainValue) +
                      ",\"temp\":" + String(temp) +
                      ",\"humidity\":" + String(humidity) +
                      ",\"waterLevel\":" + String(waterLevel) + "}";

    int httpResponseCode = http.POST(jsonData);

    if (httpResponseCode > 0) {

      String response = http.getString();

      Serial.print("ML Prediction: ");
      Serial.println(response);

    } else {

      Serial.print("Error sending request: ");
      Serial.println(httpResponseCode);

    }

    http.end();
  }

  Serial.println("--------------------------------");

  delay(3000);
}