# Zone A — Sensor Node Firmware

Full sensor suite for NETRA Zone A outdoor sensor node.

## What this sends (every 2 seconds)

LoRa packet format: `ZoneA,temp,humidity,smoke,flame,tamper,waterDistance`

| Field | Sensor | Pin | Unit |
|-------|--------|-----|------|
| `temp` | DHT22 | GPIO 4 | °C |
| `humidity` | DHT22 | GPIO 4 | % |
| `smoke` | MQ2 analog | GPIO 34 | ADC (0–4095) |
| `flame` | IR flame sensor | GPIO 35 | 0=flame, 1=clear |
| `tamper` | Vibration/tilt | GPIO 33 | 1=tampered, 0=ok |
| `waterDistance` | HC-SR04 ultrasonic | TRIG 26 / ECHO 27 | cm |

## Wiring

| Component | Pin | ESP32 GPIO |
|-----------|-----|-----------|
| DHT22 | DATA | 4 |
| LoRa SX1278 | NSS | 5 |
| LoRa SX1278 | RST | 14 |
| LoRa SX1278 | DIO0 | 2 |
| LoRa SX1278 | SCK/MISO/MOSI | 18/19/23 |
| MQ2 | AOUT | 34 |
| Flame sensor | DOUT | 35 |
| Vibration sensor | DOUT | 33 |
| HC-SR04 | TRIG | 26 |
| HC-SR04 | ECHO | 27 |

## Libraries required
- `LoRa` by Sandeep Mistry
- `DHT sensor library` by Adafruit

## Status
✅ Phase 2 — full sensor suite confirmed, water level added
🔜 Next: Gateway code updated to receive 6-value packet + flood alert logic

## Part of
[NETRA](https://github.com/maruthirm333-prog/netra) — RuralSense Labs
