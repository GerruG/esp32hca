# ESP32 Mailbox Activity Detector

An IoT project that uses an ESP32 and a PIR sensor to detect mailbox activity and send real-time notifications via Telegram.

## Features
- Detects mailbox activity using a PIR sensor.
- Sends notifications via a Flask API and Telegram bot.
- Powered by ESP32 for wireless connectivity.

## Requirements
- ESP32
- PIR sensor
- PlatformIO (IDE)
- Python 3.8+ (för Flask API)
- Telegram Bot API token


## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/esp32hca.git
   cd esp32hca
platformio run --target upload
