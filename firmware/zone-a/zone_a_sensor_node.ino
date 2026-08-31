#include <SPI.h>
#include <LoRa.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22

#define LORA_SS 5
#define LORA_RST 14
#define LORA_DIO0 2

#define MQ2_PIN 34
#define FLAME_PIN 35
#define VIB_PIN 33

#define TRIG_PIN 26
#define ECHO_PIN 27

DHT dht(DHTPIN, DHTTYPE);
volatile bool tamperDetected = false;

void IRAM_ATTR vibISR() {
  tamperDetected = true;
}

long readWaterDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  long distanceCm = duration * 0.034 / 2;
  return distanceCm;
}

void setup() {
  Serial.begin(9600);
  while (!Serial);

  dht.begin();

  pinMode(FLAME_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(VIB_PIN), vibISR, RISING);

  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed. Check your wiring.");
    while (1);
  }

  Serial.println("Zone A sensor node ready — full sensor suite + water level.");
}

void loop() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  int smoke  = analogRead(MQ2_PIN);
  int flame  = digitalRead(FLAME_PIN);
  long waterDist = readWaterDistance();

  if (isnan(t) || isnan(h)) {
    Serial.println("DHT22 read failed — check wiring.");
  } else {
    LoRa.beginPacket();
    LoRa.print("ZoneA,");
    LoRa.print(t);    LoRa.print(",");
    LoRa.print(h);    LoRa.print(",");
    LoRa.print(smoke); LoRa.print(",");
    LoRa.print(flame); LoRa.print(",");
    LoRa.print(tamperDetected ? 1 : 0); LoRa.print(",");
    LoRa.print(waterDist);
    LoRa.endPacket();

    Serial.print("Sent -> Temp: "); Serial.print(t);
    Serial.print("C  Hum: ");       Serial.print(h);
    Serial.print("%  Smoke: ");     Serial.print(smoke);
    Serial.print("  Flame: ");      Serial.print(flame);
    Serial.print("  Tamper: ");     Serial.print(tamperDetected ? "YES" : "no");
    Serial.print("  Water: ");      Serial.print(waterDist);
    Serial.println("cm");

    tamperDetected = false;
  }

  delay(2000);
}