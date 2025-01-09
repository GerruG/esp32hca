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
3. Edit the `mqtt_api.py` file and replace `YOUR_BOT_TOKEN` with your actual bot token.
4. Start the Flask server, and test notifications.

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
_Add a screenshot of the Telegram notification here._

## System Architecture
![System Architecture Diagram](diagram.png)
_Replace with the actual architecture diagram if available._

## Future Work
- Implement TLS encryption for secure communication between ESP32 and the Flask server.
- Add a database to store historical mailbox activity.
- Develop a mobile app for managing notifications and configurations.
- Integrate other sensors for additional functionality.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contributing
Contributions are welcome! Please fork the repository and submit a pull request with your changes.

## Support
For any issues or questions, feel free to open an issue on GitHub or contact me via Telegram.
