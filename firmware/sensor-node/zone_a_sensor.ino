#include <SPI.h>
#include <LoRa.h>
#include <DHT.h>

// ─── Pin Definitions ───────────────────────────────────────────
#define DHTPIN      4       // DHT22 data pin
#define DHTTYPE     DHT22

#define LORA_SS     5       // LoRa SX1278 chip select
#define LORA_RST    14      // LoRa reset
#define LORA_DIO0   2       // LoRa interrupt

#define MQ2_PIN     34      // MQ2 smoke sensor (analog)
#define FLAME_PIN   35      // IR flame sensor (digital)
#define VIB_PIN     33      // Vibration/tamper sensor (interrupt)

#define TRIG_PIN    26      // HC-SR04 ultrasonic trigger (water level)
#define ECHO_PIN    27      // HC-SR04 ultrasonic echo

// ─── Objects & State ───────────────────────────────────────────
DHT dht(DHTPIN, DHTTYPE);
volatile bool tamperDetected = false;

// ─── ISR: Tamper/Vibration ─────────────────────────────────────
void IRAM_ATTR vibISR() {
  tamperDetected = true;
}

// ─── Water Level via Ultrasonic ────────────────────────────────
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

// ─── Setup ─────────────────────────────────────────────────────
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

// ─── Main Loop ─────────────────────────────────────────────────
void loop() {
  float t    = dht.readTemperature();
  float h    = dht.readHumidity();
  int smoke  = analogRead(MQ2_PIN);
  int flame  = digitalRead(FLAME_PIN);
  long waterDist = readWaterDistance();

  if (isnan(t) || isnan(h)) {
    Serial.println("DHT22 read failed — check wiring.");
  } else {
    // ── Send LoRa packet ─────────────────────────────────────
    // Format: ZoneA,temp,humidity,smoke,flame,tamper,waterDistance
    LoRa.beginPacket();
    LoRa.print("ZoneA,");
    LoRa.print(t);        LoRa.print(",");
    LoRa.print(h);        LoRa.print(",");
    LoRa.print(smoke);    LoRa.print(",");
    LoRa.print(flame);    LoRa.print(",");
    LoRa.print(tamperDetected ? 1 : 0); LoRa.print(",");
    LoRa.print(waterDist);
    LoRa.endPacket();

    // ── Serial debug ─────────────────────────────────────────
    Serial.print("Sent -> Temp: ");   Serial.print(t);
    Serial.print("C  Hum: ");        Serial.print(h);
    Serial.print("%  Smoke: ");       Serial.print(smoke);
    Serial.print("  Flame: ");        Serial.print(flame);
    Serial.print("  Tamper: ");       Serial.print(tamperDetected ? "YES" : "no");
    Serial.print("  Water: ");        Serial.print(waterDist);
    Serial.println("cm");

    tamperDetected = false;
  }

  delay(2000);
}