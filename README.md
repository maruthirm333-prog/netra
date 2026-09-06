# NETRA 🌿

**Network-Independent Environmental Monitoring and Safety Platform**

> Intelligence where the Internet cannot reach.

NETRA is a fully offline environmental monitoring and safety system for remote farms, forest-edge communities, and isolated settlements — where cellular networks and internet cannot be relied upon.

🌐 **Landing page:** [maruthirm333-prog.github.io/netra](https://maruthirm333-prog.github.io/netra/)
📊 **Dashboard:** [maruthirm333-prog.github.io/netra/dashboard.html](https://maruthirm333-prog.github.io/netra/dashboard.html)
📐 **Architecture:** [docs/architecture.md](docs/architecture.md)
🏆 **SIH 2026:** Problem ID SIH26178 (Qualcomm Inc.) — [Presentation guide](docs/sih-2026/presentation-guide.md)

---

## The Problem

The places that need environmental warnings most — remote farms, tribal communities, off-grid settlements — are the hardest to connect. Conventional IoT silently assumes a working internet chain that simply does not exist there.

## Architecture

```
Sensor Node → LoRa → Gateway → Local Intelligence → Local Alert
     (no internet. no SIM. no cloud. no app.)
```

### 3-Board System

| Board | Hardware | Role |
|-------|----------|------|
| 01 Sensor Node | ESP32 + DHT22 + MQ2 + Flame + Vibration + Water level + LoRa | Measures 6 parameters, sends wirelessly |
| 02 Gateway | ESP32 + LCD + RTC + SD + RGB LED + Buzzer + ISD1820 | Receives, decides, alerts, logs |
| 03 Camera *(optional)* | ESP32-CAM + IR LEDs | Photo evidence on trigger |

## LoRa Packet Format

```
ZoneA,temperature,humidity,smoke,flame,tamper,waterDistance
```

## Alert States

| State | Condition | Output |
|-------|-----------|--------|
| 🟢 Normal | Temp 2–30°C | Green LED, silent |
| 🟡 Heat Watch | Temp 30–42°C | Amber LED, voice warning |
| 🔴 Frost Alert | Temp ≤ 2°C | Red LED + buzzer + voice + SD log |
| 🔴 Fire Alert | Temp ≥ 42°C | Red LED + buzzer + voice + SD log |
| 🔴 Flood Alert | Water distance < threshold | Red LED + buzzer + voice + SD log |

## Build Status

| Phase | What | Status |
|-------|------|--------|
| Phase 1 | Sensor Node + Gateway — frost/fire/heat detection | ✅ Done & tested |
| Phase 2 | RGB LED, RTC + SD logging, ISD1820 voice, predictive AI, water level | 🚧 Active |
| Phase 3 | ESP32-CAM, MQ2+flame, TDS sensor, heartbeat check | 📋 Planned |
| Phase 4 | PCB, mesh network, Bluetooth app, government pilot | 🔭 Future |

## Firmware

| Board | File | Sensors |
|-------|------|---------|
| Zone A Sensor Node | [firmware/zone-a/zone_a_sensor_node.ino](firmware/zone-a/zone_a_sensor_node.ino) | DHT22 · MQ2 · Flame · Vibration · Water level · LoRa |
| Gateway | *Coming after TDS session* | LCD · RTC · SD · ISD1820 · RGB LED · LoRa |

## Docs

| Document | Contents |
|----------|---------|
| [docs/architecture.md](docs/architecture.md) | Full 3-board system, ThingSpeak fields, AI confidence scoring |
| [docs/sih-2026/presentation-guide.md](docs/sih-2026/presentation-guide.md) | 6-slide structure, speaking notes, submission checklist |

## Part of

[RuralSense Labs](https://github.com/maruthirm333-prog/ruralsense-labs) · Built in Hassan, Karnataka, India
