# Soil‑Moisture Monitor

A low‑power Arduino/ESP sketch that reads a capacitive soil‑moisture sensor, displays the result on an SSD1306 OLED, and uploads the data to a remote API every 4 hours.

---

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Hardware](#hardware)
- [Software](#software)
- [Setup & Installation](#setup--installation)
- [Usage](#usage)
- [API Integration](#api-integration)
- [Troubleshooting](#troubleshooting)
- [Contributing](#contributing)
- [License](#license)

---

## Overview
The sketch continuously monitors soil moisture, classifies the soil state, and reports the data to a cloud service.  
- **Sensor** – Capacitive soil‑moisture sensor (analog output)  
- **Display** – 128 × 64 px SSD1306 OLED (I²C)  
- **Connectivity** – Wi‑Fi (via `NetConnect.h`)  
- **Data** – Sent to a REST API (`APIConnect.h`) every 4 hours

---

## Features
| Feature | Description |
|---------|-------------|
| **Automatic Readings** | Sensor read every 4 hours (`14800000 ms`). |
| **Moisture Mapping** | Raw ADC value mapped to 0‑100 % using `AirValue` and `WaterValue`. |
| **Status Classification** | “Wet Soil”, “Moist Soil”, “Water Now!”, or “Out‑of‑Range”. |
| **OLED Feedback** | Two screens: percentage and status, each shown for 5 seconds. |
| **Remote Logging** | Data posted to a server via Wi‑Fi. |
| **Modular Code** | Separate headers for networking (`NetConnect.h`) and API calls (`APIConnect.h`). |

---

## Hardware

| Component | Pin / Connection |
|-----------|------------------|
| **Arduino (or compatible)** | Any board with analog input and Wi‑Fi (e.g., ESP8266, ESP32). |
| **Capacitive Soil‑Moisture Sensor** | Analog output → `A0` |
| **SSD1306 OLED (I²C)** | SDA → `D2` (or board‑specific), SCL → `D1`, VCC → 3.3 V, GND → GND |
| **Power** | 3.3 V (or 5 V if using a level shifter for the OLED). |

> **Tip:** If you’re using an ESP32, the default I²C pins are `SDA = 21`, `SCL = 22`. Adjust the `display` constructor if you change pins.

---

## Software

| Library | Purpose | Install |
|---------|---------|---------|
| `Adafruit_GFX` | Core graphics library | `Sketch → Include Library → Manage Libraries → Adafruit GFX Library` |
| `Adafruit_SSD1306` | OLED driver | `Sketch → Include Library → Manage Libraries → Adafruit SSD1306` |
| `NetConnect.h` | Wi‑Fi connection helper (custom) | Add to project folder |
| `APIConnect.h` | HTTP POST helper (custom) | Add to project folder |

> The custom headers (`NetConnect.h`, `APIConnect.h`) contain your Wi‑Fi credentials and API endpoint. Replace placeholder values with your own.

---

## Setup & Installation

1. **Clone the repo**  
   ```bash
   git clone https://github.com/your-username/soil-moisture-monitor.git
   cd soil-moisture-monitor
