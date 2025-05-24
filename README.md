> ⚠️ To run the project, make sure to open the `src/main.cpp` file and upload it to your ESP8266 using your preferred method (e.g. PlatformIO in VS Code).

---

## ✅ Features

- Wi-Fi connection to your local network
- Real-time LED control from any browser on the same network
- Responsive HTML/CSS UI with a modern toggle switch
- Uses `fetch()` for fast and smooth interaction

---

## 🧰 Requirements

- ESP8266 development board (e.g. NodeMCU, Wemos D1 Mini)
- VS Code with PlatformIO or any compatible uploader
- ESP8266 Libraries:
  - `ESP8266WiFi`
  - `ESP8266WebServer`
  - `ESP8266mDNS`

---

## 🚀 Getting Started

1. Clone or download the repository
2. Open the folder in VS Code
3. Go to `src/main.cpp`
4. Update your Wi-Fi credentials:
   ```cpp
   const char* ssid = "YOUR_WIFI_NAME";
   const char* password = "YOUR_WIFI_PASSWORD";
