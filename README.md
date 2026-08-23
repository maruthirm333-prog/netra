# NETRA 🌿

**Network-Independent Environmental Monitoring and Safety Platform**

> Intelligence where the Internet cannot reach.

NETRA is a fully offline environmental monitoring and safety system built for remote farms, forest-edge communities, and isolated settlements where cellular networks and internet connectivity cannot be relied upon.

🌐 **Live landing page:** [maruthirm333-prog.github.io/netra](https://maruthirm333-prog.github.io/netra/)

---

## The Problem

The places that need environmental warnings most — remote farms, tribal communities, off-grid settlements — are often the hardest to connect. Conventional IoT systems silently assume a working internet chain that simply does not exist there.

## The Solution — NETRA Architecture

```
Sensor Node → LoRa → Local Gateway → Local Intelligence → Local Alert
       (no internet. no SIM. no cloud. no app.)
```

### 4-Layer System

| Layer | Hardware | Role |
|-------|----------|------|
| 01 Sensor Node | ESP32 + DHT22 + SX1278 LoRa + Solar | Reads temperature & humidity on-site |
| 02 LoRa Comms | SX1278 Ra-02 433MHz | Long-range, zero-network radio link |
| 03 Gateway | ESP32 + LCD + RTC + SD + RGB LED + Buzzer + DFPlayer Mini | Local intelligence unit at the farmhouse |
| 04 Local AI | Threshold logic + rate-of-change detection | Decides danger level entirely on-site |

## Alert States

| State | Condition | Output |
|-------|-----------|--------|
| 🟢 Normal | Temp 2–30°C, RH OK | Green LED, silent |
| 🟡 Heat Watch | Temp 30–42°C | Amber LED, voice warning |
| 🔴 Frost Alert | Temp ≤ 2°C | Red LED + buzzer + voice alert + SD log |
| 🔴 Fire Alert | Temp ≥ 42°C | Red LED + buzzer + voice alert + SD log |

## What Makes NETRA Different

**Conventional IoT needs (ongoing):** SIM card · Data plan · Cellular coverage · Cloud hosting · Internet-dependent app

**NETRA needs (ongoing):** Nothing. Local sensing, local comms, local storage, local intelligence.

## Project Status

- ✅ Concept and architecture validated
- ✅ Landing page live
- 🚧 Prototype hardware assembly
- 📋 Field testing on Karnataka farmland
- 📋 Multi-sensor LoRa mesh network
- 📋 Crop-specific calibration
- 📋 Institutional deployment (NGO / Government partnerships)

## Team

4-member ECE engineering team — Malnad College of Engineering, Hassan, Karnataka, India.

## Part of

[RuralSense Labs](https://github.com/maruthirm333-prog/ruralsense-labs)
