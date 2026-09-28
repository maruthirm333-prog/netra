/* ==========================================================================
   NETRA ZONE A NODE  --  field-study firmware
   --------------------------------------------------------------------------
   Two additions to the demo firmware, both needed for the paper:

   1. SEQUENCE NUMBER on every packet.
      The gateway logs it, so gaps in the sequence tell you exactly how
      many packets were lost across the whole 30 days. That gives you a
      real packet delivery ratio for the deployment, not just for the
      afternoon of the range test.

   2. BATTERY VOLTAGE on every packet.
      Needs a 100k / 100k divider from the 18650 positive terminal to
      GPIO32 (junction to GPIO32, bottom of the divider to GND). Without
      it the value reads near zero and the analysis simply ignores it,
      but then you have no endurance result.

      18650 max 4.2 V, divided by 2 -> 2.1 V, safely inside the ADC range.

   Radio settings match the gateway: 433.92 MHz, 8 dBm, CRC on.
   Both boards must use identical settings or they will not hear each other.
   ========================================================================== */

#include <SPI.h>
#include <LoRa.h>
#include <DHT.h>

#define DHTPIN     4
#define DHTTYPE    DHT22
#define LORA_SS    5
#define LORA_RST   14
#define LORA_DIO0  2
#define MQ2_PIN    34
#define FLAME_PIN  35
#define VIB_PIN    33
#define MQ135_PIN  36
#define TRIG_PIN   12
#define ECHO_PIN   39
#define VBAT_PIN   32        // 100k/100k divider from battery positive

#define LORA_FREQ    433920000L
#define LORA_TX_DBM  8
#define VBAT_CAL     1.00    // trim against a multimeter reading if needed

DHT dht(DHTPIN, DHTTYPE);

volatile int vibCount = 0;
unsigned long vibWindowStart = 0;
uint32_t seq = 0;

void IRAM_ATTR vibISR() { vibCount++; }

float readDistance() {
  digitalWrite(TRIG_PIN, LOW);  delayMicroseconds(20);
  digitalWrite(TRIG_PIN, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long dur = pulseIn(ECHO_PIN, HIGH, 50000);
  if (dur == 0) return -1;
  float d = dur * 0.0343 / 2.0;
  return (d < 20 || d > 600) ? -1 : d;
}

float medianDistance() {
  float a = readDistance(); delay(30);
  float b = readDistance(); delay(30);
  float c = readDistance();
  if (a > 0 && b > 0 && c > 0) {
    float s[3] = {a, b, c}, t;
    if (s[0] > s[1]) { t = s[0]; s[0] = s[1]; s[1] = t; }
    if (s[1] > s[2]) { t = s[1]; s[1] = s[2]; s[2] = t; }
    if (s[0] > s[1]) { t = s[0]; s[0] = s[1]; s[1] = t; }
    return s[1];
  }
  if (a > 0) return a;
  if (b > 0) return b;
  return c;                     // -1 if all three failed
}

float readBattery() {
  uint32_t sum = 0;
  for (int i = 0; i < 16; i++) { sum += analogRead(VBAT_PIN); delay(2); }
  float raw = sum / 16.0;
  return (raw / 4095.0) * 3.3 * 2.0 * VBAT_CAL;
}

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(FLAME_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);
  attachInterrupt(digitalPinToInterrupt(VIB_PIN), vibISR, RISING);
  vibWindowStart = millis();

  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(LORA_FREQ)) { Serial.println("LoRa failed"); while (1); }
  LoRa.setTxPower(LORA_TX_DBM);
  LoRa.enableCrc();

  Serial.println("Zone A field node ready.");
}

void loop() {
  float t     = dht.readTemperature();
  float h     = dht.readHumidity();
  int   smoke = analogRead(MQ2_PIN);
  int   flame = digitalRead(FLAME_PIN);
  int   aq    = analogRead(MQ135_PIN);
  float water = medianDistance();
  float vbat  = readBattery();

  if (millis() - vibWindowStart > 60000UL) { vibCount = 0; vibWindowStart = millis(); }
  int vib = vibCount;

  if (isnan(t) || isnan(h)) {          // skip rather than send garbage
    Serial.println("DHT read failed, skipping this cycle");
    delay(2000);
    return;
  }

  seq++;

  LoRa.beginPacket();
  LoRa.print("ZoneA,");     LoRa.print(seq);   LoRa.print(",");
  LoRa.print(t, 2);         LoRa.print(",");
  LoRa.print(h, 2);         LoRa.print(",");
  LoRa.print(smoke);        LoRa.print(",");
  LoRa.print(flame);        LoRa.print(",");
  LoRa.print(vib);          LoRa.print(",");
  LoRa.print(aq);           LoRa.print(",");
  LoRa.print(water, 1);     LoRa.print(",");
  LoRa.print(vbat, 3);
  LoRa.endPacket();

  Serial.print("seq="); Serial.print(seq);
  Serial.print("  T=");  Serial.print(t, 1);
  Serial.print("  H=");  Serial.print(h, 0);
  Serial.print("  S=");  Serial.print(smoke);
  Serial.print("  F=");  Serial.print(flame);
  Serial.print("  V=");  Serial.print(vib);
  Serial.print("  AQ="); Serial.print(aq);
  Serial.print("  W=");  Serial.print(water, 0);
  Serial.print("  Vb="); Serial.println(vbat, 2);

  delay(2000);
}
