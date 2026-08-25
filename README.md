# NETRA 🌿

**Network-Independent Environmental Monitoring and Safety Platform**

> Intelligence where the Internet cannot reach.

NETRA is a fully offline environmental monitoring and safety system built for remote farms, forest-edge communities, and isolated settlements where cellular networks and internet connectivity cannot be relied upon.

🌐 **Live landing page:** [maruthirm333-prog.github.io/netra](https://maruthirm333-prog.github.io/netra/)
📐 **System architecture:** [docs/architecture.md](docs/architecture.md)

---

## The Problem

The places that need environmental warnings most — remote farms, tribal communities, off-grid settlements — are often the hardest to connect. Conventional IoT systems silently assume a working internet chain that simply does not exist there.

## The Solution — NETRA Architecture

```
Sensor Node → LoRa → Gateway → Local Intelligence → Local Alert
     (no internet. no SIM. no cloud. no app.)
```

### 3-Board System

| Board | Hardware | Role |
|-------|----------|------|
| 01 Sensor Node | ESP32 + DHT22 + SX1278 LoRa + Solar + 18650 | Measures environment, sends wirelessly |
| 02 Gateway | ESP32 + LCD + RTC + SD + RGB LED + Buzzer + DFPlayer Mini | Receives, decides, alerts, logs |
| 03 Camera Module *(optional)* | ESP32-CAM + IR LEDs | Photo evidence on trigger |

## Alert States

| State | Condition | Output |
|-------|-----------|--------|
| 🟢 Normal | Temp 2–30°C, RH OK | Green LED, silent |
| 🟡 Heat Watch | Temp 30–42°C | Amber LED, voice warning |
| 🔴 Frost Alert | Temp ≤ 2°C | Red LED + buzzer + voice + SD log |
| 🔴 Fire Alert | Temp ≥ 42°C | Red LED + buzzer + voice + SD log |

## Build Status

| Phase | What | Status |
|-------|------|--------|
| Phase 1 | Sensor Node + Gateway core — frost/fire/heat detection | ✅ Done & tested |
| Phase 2 | RGB LED, RTC + SD logging, DFPlayer voice alert, predictive algorithm | 🚧 Active |
| Phase 3 | ESP32-CAM, MQ2/IR flame, heartbeat check, low-battery warning | 📋 Planned |
| Phase 4 | PCB, mesh network, Bluetooth app, government pilot | 🔭 Future |

→ Full breakdown: [docs/architecture.md](docs/architecture.md)

## What Makes NETRA Different

**Conventional IoT needs:** SIM card · Data plan · Cellular coverage · Cloud hosting · App

**NETRA needs (ongoing):** Nothing. Local sensing → local comms → local intelligence → local alert.

## Team

4-member ECE engineering team — Malnad College of Engineering, Hassan, Karnataka, India.

## Part of

[RuralSense Labs](https://github.com/maruthirm333-prog/ruralsense-labs)
