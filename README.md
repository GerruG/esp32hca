# ESP32 Mailbox Activity Detector

An IoT project that uses an ESP32 and a PIR sensor to detect mailbox activity and send real-time notifications via Telegram.

## Features
- Detects mailbox activity using a PIR sensor.
- Sends notifications via a Flask API and Telegram bot.
- Powered by ESP32 for wireless connectivity.
- Easy to set up and install.

## Requirements
To run this project, you'll need:
- **Hardware**:
  - ESP32 microcontroller
  - PIR sensor
  - Power supply for ESP32
- **Software**:
  - [PlatformIO](https://platformio.org/) for programming the ESP32
  - Python 3.8+ for the Flask API
  - Telegram Bot API token
- **Libraries**:
  - `WiFi.h` and `HTTPClient.h` for ESP32
  - Python libraries (in `requirements.txt` for Flask server):
    - Flask
    - Requests

## Installation

### ESP32 Setup
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/esp32hca.git
   cd esp32hca
   ```
2. Open the project in PlatformIO (VSCode).
3. Connect your ESP32 to your computer.
4. Flash the ESP32 with the code in the `src/` folder:
   ```bash
   platformio run --target upload
   ```

### Flask API Server
1. Navigate to the project directory:
   ```bash
   cd esp32hca
   ```
2. Set up a Python virtual environment (optional but recommended):
   ```bash
   python3 -m venv myenv
   source myenv/bin/activate  # For Linux/Mac
   myenv\Scripts\activate     # For Windows
   ```
3. Install required dependencies:
   ```bash
   pip install -r requirements.txt
   ```
4. Start the Flask API server:
   ```bash
   python3 mqtt_api.py
   ```

### Telegram Bot Setup
1. Create a bot using the [BotFather](https://core.telegram.org/bots#botfather) on Telegram.
2. Note the bot token provided by BotFather.
3. Edit the `mqtt_api.py` file and replace `your_bot_api_token` with your actual bot token.
4. Start the Flask server, and test notifications.

## Flask API Code
Below is the Flask API code used in this project:

```python
import logging
from flask import Flask, request, jsonify
from datetime import datetime
import requests

# Create Flask app instance
app = Flask(__name__)

# Configure logging
logging.basicConfig(
    level=logging.DEBUG,
    format="%(asctime)s - %(levelname)s - %(message)s",
    handlers=[
        logging.FileHandler("mqtt_api.log"),
        logging.StreamHandler(),
    ],
)

# Telegram Bot API Token and Chat ID
TELEGRAM_API_TOKEN = "your_bot_api_token"  # Replace with your actual bot token
TELEGRAM_CHAT_ID = "your_chat_id"  # Replace with your actual chat ID

def send_telegram_notification(message):
    url = f"https://api.telegram.org/bot{TELEGRAM_API_TOKEN}/sendMessage"
    payload = {"chat_id": TELEGRAM_CHAT_ID, "text": message}
    response = requests.post(url, json=payload)
    if response.status_code != 200:
        app.logger.error(f"Failed to send notification: {response.text}")

# Global state
latest_motion_data = {"motion": "inactive", "timestamp": None}

# Define routes
@app.route('/api/motion', methods=['POST'])
def receive_motion_data():
    global latest_motion_data

    data = request.json
    if not data or "motion" not in data:
        return jsonify({"error": "Invalid data"}), 400

    new_state = "active" if data["motion"] else "inactive"

    if new_state != latest_motion_data["motion"]:
        latest_motion_data = {
            "motion": new_state,
            "timestamp": datetime.now().isoformat(),
        }

        if new_state == "active":
            notification_message = f"Mailbox Activity Detected at {latest_motion_data['timestamp']}"
            send_telegram_notification(notification_message)

    return jsonify({"message": "Data received successfully"}), 200

@app.route('/api/motion', methods=['GET'])
def get_motion_data():
    return jsonify(latest_motion_data)
```

## Folder Structure
- `src/`: Contains the ESP32 code.
- `include/`: Header files for ESP32.
- `lib/`: Additional libraries used in the ESP32 project.
- `test/`: Test files and scripts.
- `docs/`: Documentation (e.g., diagrams and additional notes).
- `.gitignore`: Specifies files to exclude from Git tracking.
- `platformio.ini`: Configuration file for PlatformIO.
- `mqtt_api.py`: Python script for the Flask API.

## Example
When motion is detected in the mailbox, the Telegram bot sends a notification like this:

```
Mailbox Activity Detected at 2025-01-09T21:20:40
```

### Screenshot
![1000005356](https://github.com/user-attachments/assets/ccd9c8ce-0297-4aef-a736-2b2d96e992ab)


## System Architecture
![image](https://github.com/user-attachments/assets/52663cac-7ac2-4c83-b4e5-fb300c7c7c2e)


## Future Work
- Implement TLS encryption for secure communication between ESP32 and the Flask server.
- Add a database to store historical mailbox activity.
- Develop a mobile app for managing notifications and configurations.
- Integrate other sensors for additional functionality.

