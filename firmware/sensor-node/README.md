# Sensor Node Firmware — Zone A

**ESP32 sensor node for NETRA** — reads all environmental sensors and transmits over LoRa every 2 seconds.

## File
| File | Description |
|------|-------------|
| `zone_a_sensor.ino` | Full Zone A firmware — all sensors + LoRa TX |

## Sensors on Zone A

| Sensor | Pin | Type | What it detects |
|--------|-----|------|-----------------|
| DHT22 | GPIO 4 | Digital | Temperature + Humidity |
| MQ2 | GPIO 34 | Analog | Smoke / gas concentration |
| IR Flame sensor | GPIO 35 | Digital | Direct flame presence |
| Vibration sensor | GPIO 33 | Interrupt (RISING) | Tamper / physical disturbance |
| HC-SR04 (water level) | TRIG=GPIO 26, ECHO=GPIO 27 | Ultrasonic | Water level via distance |
| SX1278 LoRa | SPI (SS=5, RST=14, DIO0=2) | SPI | Wireless TX to Gateway |

## LoRa Packet Format

```
ZoneA,<temp>,<humidity>,<smoke>,<flame>,<tamper>,<waterDist>
```

| Field | Type | Example | Notes |
|-------|------|---------|-------|
| ZoneA | String | ZoneA | Zone identifier |
| temp | float | 27.4 | °C from DHT22 |
| humidity | float | 68.0 | % RH from DHT22 |
| smoke | int | 1240 | ADC 0–4095 from MQ2 |
| flame | int | 0 or 1 | 0 = flame detected, 1 = clear |
| tamper | int | 0 or 1 | 1 = vibration triggered since last packet |
| waterDist | long | 18 | cm from HC-SR04 (lower = higher water level) |

## Wiring Summary

```
ESP32
├── GPIO 4   → DHT22 data
├── GPIO 34  → MQ2 AOUT
├── GPIO 35  → Flame sensor DOUT
├── GPIO 33  → Vibration sensor OUT
├── GPIO 26  → HC-SR04 TRIG
├── GPIO 27  → HC-SR04 ECHO
└── SPI bus (18/19/23) + SS=5, RST=14, DIO0=2 → LoRa SX1278
```

## Libraries Required
Install via Arduino Library Manager:
- **LoRa** by Sandeep Mistry
- **DHT sensor library** by Adafruit
- **Adafruit Unified Sensor** (dependency)

## Build Status
✅ Phase 2 complete — all 6 sensors confirmed working, LoRa TX verified
