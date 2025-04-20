#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <BlynkSimpleEsp8266.h>
#include <WiFiManager.h>

WiFiManager wifiManager;

const int dallas = 4;   // PIN untuk sensor Dallas DS18B20

OneWire oneWire(dallas);
DallasTemperature sensors(&oneWire);

#define BLYNK_TEMPLATE_ID "TMPL6QCrULozi"
#define BLYNK_TEMPLATE_NAME "Projek Coba Coba"
#define BLYNK_AUTH_TOKEN "Gq08VKO8VNHrUMROialSfuXcLuuKHNpe"

void setup() {
  // Menyalakan WiFi untuk konfigurasi ssid
  WiFi.mode(WIFI_STA);
  WiFiManager wm;
  // wm.resetSettings(); // jika dinyalakan, maka semua settingan wifi yang tersimpan akan dihapus
  bool res;
  res = wm.autoConnect("NodeMcu", "123456789");
  if (!res) {
    Serial.println("Failed to connect");
    // ESP.restart();
  } else {
    Serial.println("terhubung :)");
  }

  Serial.begin(9600);
  Blynk.config(BLYNK_AUTH_TOKEN);
  sensors.begin();
}

void loop() {

  Blynk.run();

  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);
  if (temperature == DEVICE_DISCONNECTED_C) {
    Serial.println("Failed to read from DS18B20 sensor!");
    return;
  }

  Blynk.virtualWrite(V4, temperature); // mengirim ke vpin 4

  delay(1000); // jeda 1 detik
}