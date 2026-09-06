# SIH 2026 — Presentation Guide

**Competition:** Smart India Hackathon 2026
**Problem ID:** SIH26178
**Problem setter:** Qualcomm Inc.
**Project:** NETRA — Network-Independent Environmental Monitoring and Safety Platform

---

## Final 6-Slide Structure

| Slide | Content |
|-------|---------|
| 1 | Title page |
| 2 | Proposed solution |
| 3 | Technical approach |
| 4 | Hardware CAD design |
| 5 | Feasibility + field photos + prototype photo |
| 6 | Impact + references (combined) |

---

## Slide-by-Slide Content Guide

### Slide 3 — Technical Approach
**Image to include:** Dashboard screenshot showing confidence bars

### Slide 4 — Hardware CAD Design
**Title:** "Hardware Design — NETRA"
**Layout:** Left half = Zone A sensor node CAD · Right half = Gateway alert unit CAD
**Caption at bottom:**
> "Prototype built and field-tested. Production enclosure targets IP65 certified ABS with pole/wall mounting."

**What to say (20 seconds):**
> "Here is our hardware design. Left is Zone A — the field sensor node, IP65 weatherproof, solar powered, 7 sensors inside, mounts on a pole or wall. Right is the Gateway — sits at the farmhouse, shows alerts on the LCD screen, sounds the buzzer, and speaks in the local language. Both communicate over LoRa radio — no internet, no SIM card."

### Slide 5 — Feasibility
**Images:**
- Field photos with farmers (already placed)
- ✅ TODO: Real prototype photo — both boards powered on, Gateway LCD showing "FIRE RISK!" or active alert

**How to take the prototype photo:**
1. Power on both boards
2. Trigger a fire test (hold flame sensor or heat near MQ2)
3. Photograph both boards together — Zone A on one side, Gateway LCD alert on the other
4. Use this photo on Slide 5 to prove prototype is real and working

### Slide 6 — Impact + References (Combined)

**Impact section:**
- Farmers with no mobile network get early warnings
- Forest-edge and flood-prone villages get local alerts
- Disaster teams see zone-level risk on dashboard
- Prevents ₹15,000–50,000 crop loss per event
- Zero running cost — no SIM card, no data plan

**Vision:**
> One farm → Villages → District → State network

**References:**
- SIH 2026 — SIH26178 (Qualcomm Inc.)
- ESP32 — espressif.com
- LoRa SX1278 — semtech.com
- ThingSpeak — thingspeak.com
- NDMA disaster guidelines — ndma.gov.in
- Field tested with farmers, Hassan district, Karnataka

---

## Pre-Submission Checklist

- [ ] Slide 4: Zone A CAD image added (left)
- [ ] Slide 4: Gateway CAD image added (right)
- [ ] Slide 3: Dashboard screenshot with confidence bars
- [ ] Slide 5: Prototype photo — both boards + LCD showing live alert
- [ ] Slide 5: Field photos with farmers already placed
- [ ] Slide 6: Impact + references merged into one slide
- [ ] Total slide count confirmed = 6
- [ ] File exported as `.pptx` or `.pdf` per SIH format requirement

---

## Hardware CAD Notes

- Gateway bottom view correctly shows **"WiFi (When Available)"** — right wording for hybrid architecture
- Zone A: IP65 weatherproof, solar powered, pole/wall mount
- Gateway: farmhouse unit, LCD + buzzer + ISD1820 voice alert
- Production target: IP65 certified ABS enclosure
