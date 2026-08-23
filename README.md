# NETRA 👁️

> **Intelligence where the Internet cannot reach.**

**NETRA** is a network-independent environmental monitoring and safety platform for remote areas — farms, forest-edge communities, and settlements where cellular networks, Wi-Fi, and cloud services cannot be relied upon.

No SIM. No internet. No cloud. It still works.

---

## The problem

The places that need early warnings most — remote farms, tribal settlements, isolated communities — are exactly the places where conventional connected IoT fails. A conventional system says: Sensor → Internet → Cloud → App → User. If any link in that chain is missing, the warning never arrives.

NETRA removes the chain.

---

## Architecture

```
Sensor Node → LoRa → Local Gateway → Local Decision → Local Alert
```

### 01 / Sensor Node
Weatherproof field unit measuring temperature and humidity continuously. Battery-powered with solar charging.

| Component | Purpose |
|-----------|---------|
| ESP32 | Main controller |
| SX1278 Ra-02 | LoRa radio (long-range, no SIM) |
| DHT22 | Temperature + humidity sensor |
| Battery + solar panel | Standalone power |

### 02 / LoRa Communication
Sensor nodes reach the gateway over LoRa radio — no SIM, no Wi-Fi, no internet anywhere in the path.

- Tested: ~100m in dense urban environment
- Open-field range: currently being validated in real conditions

### 03 / Local Gateway
Installed at the farmhouse. Receives sensor readings and makes decisions entirely on-site.

| Component | Purpose |
|-----------|---------|
| ESP32 | Main controller |
| LoRa module | Receives sensor data |
| 16×2 LCD | Displays live readings and alert status |
| DS3231 RTC | Keeps accurate time offline |
| SD card module | Offline event logging |
| RGB LED | Visual alert indicator |
| Active buzzer | Audio alert |
| DFPlayer Mini | Voice alert playback (planned) |

### 04 / Local Intelligence
Threshold logic running entirely on the gateway — no cloud required:

| Condition | Threshold | Alert |
|-----------|-----------|-------|
| Frost | ≤ 2°C | 🔴 FROST ALERT — buzzer + red LED |
| Heat watch | 30–42°C | 🟡 HEAT WATCH — amber LED |
| Fire alert | ≥ 42°C | 🔴 FIRE ALERT — buzzer + red LED |
| Normal | 2–30°C | 🟢 Normal — green LED |

Trend-based early warning (alert before threshold is crossed) is the next planned feature.

---

## What it does not need

| Conventional IoT | NETRA |
|-----------------|-------|
| SIM card | ❌ Not needed |
| Data plan | ❌ Not needed |
| Cellular coverage | ❌ Not needed |
| Cloud hosting | ❌ Not needed |
| Internet connection | ❌ Not needed |

---

## Current prototype status

| Component | Status |
|-----------|--------|
| Zone A sensor node | ✅ Working — transmitting real readings |
| Gateway (LCD + buzzer) | ✅ Working — receiving data, alerts confirmed |
| RGB LED | 🔧 Under troubleshooting |
| RTC (DS3231) | 🔧 In progress |
| SD card logging | 📋 Next |
| DFPlayer voice alerts | 📋 Planned |
| Zone B sensor node | 📋 Planned |
| Weatherproof enclosure + solar | 📋 Field MVP stage |

---

## Offline event logging

Every alert is timestamped using the onboard RTC and written to SD card — building a local, durable record of what happened and when. Sample log:

```
NETRA EVENT RECORD
ZONE        : A
DATE        : 21 AUG 2026
TIME        : 04:17:32
TEMPERATURE : 1.8°C
HUMIDITY    : 91%
EVENT       : FROST ALERT
```

---

## Voice alerts

A DFPlayer Mini module plays pre-recorded local-language warnings through a speaker — so the alert works for anyone who might not read a screen, especially at night.

Example (Kannada): *"ಎಚ್ಚರಿಕೆ — ಹಿಮಪಾತದ ಅಪಾಯ ಇದೆ."*
Language is configurable per deployment.

---

## Roadmap

| Stage | Milestone |
|-------|-----------|
| ✅ NOW | Zone A sensor + gateway communicating over LoRa |
| 🔧 NEXT | RTC + SD card offline logging |
| 🔧 NEXT | RGB LED + voice alerts (DFPlayer) |
| 📋 NEXT | Zone B — second sensor node, multi-zone |
| 📋 FIELD MVP | Weatherproof enclosure + solar power testing |
| 📋 PILOT | Real farmer testing in actual field conditions |
| 📋 PRODUCT | Manufacturing and productization |
| 📋 SCALE | Government, NGO, institutional deployment |

---

## Primary use case

🌾 **Remote agriculture** — frost, fire, and heat-stress early warnings for farms where internet is absent or unreliable.

Also applicable (subject to validation): forest-edge monitoring, remote communities, disaster response zones, isolated worksites.

---

## Team

4 ECE engineers — Malnad College of Engineering, Hassan, Karnataka, India.

- Founder / Product & Technology Lead
- Market & Customer Lead
- Government / Partnerships Lead
- Business & Strategy Lead

---

## Landing page

`index.html` — interactive product landing page with live gateway simulation. Open it in a browser to explore the prototype.

---

## Part of
[RuralSense Labs](https://github.com/maruthirm333-prog/ruralsense-labs)
