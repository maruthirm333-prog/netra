# Prahari — Complete System Architecture & Feature Map

This document exists to answer one question clearly: **how does every feature we've discussed actually connect to the physical hardware, and to each other?**

---

## The Three Physical Boards

Everything you're building lives on exactly **three separate physical boards**. Every feature we've discussed attaches to one of these three — nothing floats independently.

### Board 1: Sensor Node (per zone — you've built Zone A)
Its only job: measure the environment, send it wirelessly.

### Board 2: Gateway (one per farm)
Its only job: receive data, decide risk, alert the farmer, log everything.

### Board 3: Camera Module (optional add-on, talks only to the Gateway)
Its only job: take a photo when told to, save it.

---

## Board 1 — Sensor Node — Full Component Map

| Component | Connects via | Feeds which feature? |
|---|---|---|
| ESP32 | — | Runs everything on this board |
| DHT22 (temp/humidity) | GPIO 4 (digital) | Core detection + predictive algorithm |
| SX1278 LoRa module | SPI bus (pins 18/19/23/5/14/2) | Sends all data to Gateway |
| 18650 battery + TP4056 + solar | Power only | Keeps node running in the field |
| *(Optional, not yet built)* MQ2 smoke sensor | Analog pin (e.g. GPIO 34) | Better/faster fire detection |
| *(Optional, not yet built)* IR flame sensor | Digital pin (e.g. GPIO 35) | Direct flame detection, no delay |
| *(Optional, not yet built)* Soil moisture sensor | Analog pin (e.g. GPIO 32) | Drought/irrigation advisory |
| *(Optional, not yet built)* Vibration/tilt sensor | Digital pin | Tamper/theft alert |
| *(Optional, not yet built)* Anemometer (wind) | Digital pulse pin | Wind-aware frost accuracy |

**Everything on this board packages into one LoRa message and sends it.** More sensors just means a longer message — the sending mechanism doesn't change.

---

## Board 2 — Gateway — Full Component Map

| Component | Connects via | Feeds which feature? |
|---|---|---|
| ESP32 | — | Runs everything on this board |
| SX1278 LoRa module | SPI bus (18/19/23/5/14/2) | Receives all sensor data |
| 16x2 LCD | I2C bus (SDA 21 / SCL 22) | Visual display |
| DS3231 RTC | I2C bus (**same** SDA/SCL — shares with LCD) | Accurate timestamps for logging |
| Micro SD card module | SPI bus (**shares** SCK/MISO/MOSI with LoRa, own CS on pin 15) | Insurance proof-logging |
| Piezo buzzer | GPIO 25 | Audible alert (also doubles as hail-impact sensor if reused as input) |
| RGB LED | GPIO 27 / 32 / 33 | Visual risk color-coding |
| ISD1820 voice recorder | Digital pin (e.g. GPIO 26, PLAYE trigger) | Pre-recorded voice alert in local language |
| Speaker (0.5W) | Connects to ISD1820 SPK+/SPK− output | Plays the pre-recorded voice alert |
| *(Optional)* Crop-select switch | Digital pin | Adjusts threshold per crop type |
| *(Optional)* Battery voltage sense | Analog pin, via voltage divider | Low-battery early warning |

**This is the brain of the whole system.** Every decision (frost/fire/heat/normal, log it, speak it, show it) happens here, based on what arrives over LoRa.

---

## Board 3 — Camera Module (fully optional, separate board)

| Component | Connects via | Feeds which feature? |
|---|---|---|
| ESP32-CAM | UART (2 wires) to Gateway's spare pins | Receives "take a photo" command |
| Built-in micro-SD slot | Built into the ESP32-CAM board | Stores photo evidence |
| IR LED array | Powers on with camera | Makes night photos actually visible |

**This board does nothing on its own.** It sits idle, listening, until the Gateway sends it a "capture now, this is Zone A, this timestamp" message — then it takes one photo and saves it under that exact filename, so it lines up with your text log automatically.

---

## How Data Actually Flows, End to End

```
Sensor Node reads DHT22
        ↓
Packages "ZoneA,24.7,74.0" 
        ↓ (LoRa radio)
Gateway receives it
        ↓
Gateway checks thresholds → decides: Normal / Watch / Frost / Fire
        ↓
        ├─→ LCD shows result
        ├─→ RGB LED changes color
        ├─→ Buzzer sounds (if danger)
        ├─→ ISD1820 plays pre-recorded voice alert (if danger)
        ├─→ RTC timestamp + SD card logs the event (insurance record)
        └─→ (optional) Sends "CAPTURE" command to Camera Module
                              ↓
                    Camera takes photo, saves with matching timestamp
```

Every feature is really just **one more thing the Gateway does** at the moment it receives data and makes a decision. Nothing runs independently of this core loop.

---

## Shared Bus Warning — Important Wiring Rule

Notice several components share the same wires:
- **I2C bus (SDA 21 / SCL 22):** LCD + RTC both use this — totally fine, I2C is designed for multiple devices on one line, each has its own address
- **SPI bus (SCK 18 / MISO 19 / MOSI 23):** LoRa + SD card both use this — also fine, but **each device needs its own separate CS (chip select) pin** — LoRa uses GPIO 5, SD card uses GPIO 15. Never give two devices the same CS pin.

---

## Build Phases — What's Confirmed vs What's Still an Idea

**Phase 1 — Core (done and tested):**
Sensor Node (DHT22 + LoRa) → Gateway (LCD + buzzer + LoRa) — frost/fire/heat detection working

**Phase 2 — Confirmed, actively building:**
- RGB LED (wiring fix pending part)
- RTC + SD card → insurance logging
- ISD1820 voice recorder → pre-recorded voice alert (trigger via GPIO 26)
- Predictive rate-of-change algorithm (pure code)

**Phase 3 — Explored in depth, not yet committed to building:**
- ESP32-CAM + IR LEDs → photo evidence
- MQ2 + IR flame sensor → better fire detection
- Heartbeat check + self-test on boot (cheap, pure code — worth prioritizing if you add anything from this list)
- Low-battery warning
- Soil moisture, crop-profile switch, hail detection, tamper detection

**Phase 4 — Future / post-hackathon vision:**
- PCB miniaturization
- Multi-hop mesh for larger areas
- Bluetooth walk-by app
- Village-wide broadcast
- Government/forest department pilot scaling

---

## The One Thing to Remember

However many features this list grows to, **the underlying pattern never changes**: Sensor Node measures and sends → Gateway receives, decides, and acts. Every single feature you add is just the Gateway doing one more thing when it makes that decision. If you ever feel confused about how a new idea fits in, ask: "does this belong on the Sensor Node (something to measure) or the Gateway (something to decide or display)?" — that answers it every time.


---

## ThingSpeak Integration (Phase 2 addition)

Channel: **Prahari Monitor**

| ThingSpeak Field | Sensor / Feature | Unit |
|-----------------|-----------------|------|
| Field 1 | Temperature | °C |
| Field 2 | Humidity | % |
| Field 3 | Water Distance | cm |
| Field 4 | Fire Confidence | % |
| Field 5 | Flood Confidence | % |
| Field 6 | Frost Confidence | % |
| Field 7 | Landslide Confidence | % |
| Field 8 | Pollution Confidence | % |

---

## AI Confidence Scoring — Gateway Logic (Phase 2 addition)

Instead of binary ALERT / NO ALERT, the Gateway computes a **confidence percentage** for each hazard type using multiple sensor inputs weighted together.

| Hazard | Inputs used | Output |
|--------|------------|--------|
| Fire | Flame sensor + MQ2 smoke + temperature rate-of-change | Fire Confidence % |
| Flood | Water distance + rain trend | Flood Confidence % |
| Frost | Temperature + humidity + time-of-day | Frost Confidence % |
| Landslide | Vibration count over rolling window | Landslide Confidence % |
| Pollution | MQ2 ADC baseline drift | Pollution Confidence % |

Alert triggers when confidence crosses threshold (e.g. >70%).

---

## Pending Hardware (bring + wire before next code session)

| Sensor | Purpose | Zone |
|--------|---------|------|
| TDS sensor | Water quality / pollution detection | Zone A |

## Deferred to Next Phase

| Feature | Reason |
|---------|--------|
| Zone B sensor node | Hardware not ready — present as "next phase" to judges |
| Landslide counter (Zone A firmware update) | Code ready, pending TDS session |

---

## Flood Detection — Deployment Note

JSN-SR04T minimum range: **20cm**. Anything closer returns garbage (399/400).

For field deployment: mount probe on a pole **≥ 50cm above** normal water level of drain/canal.
For demo: point straight down at floor from 60–80cm, use hand to simulate rising water.

See [build-log entry 002](https://github.com/maruthirm333-prog/build-log/blob/main/entries/002-jsn-sr04t-minimum-range.md) for full debug notes.
