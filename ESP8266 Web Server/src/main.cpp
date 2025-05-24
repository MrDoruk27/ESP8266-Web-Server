#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

const char* ssid = "Redmi Note 11 Pro";
const char* password = "asdasas27";

ESP8266WebServer server(80);

void handleRoot() {
   String page = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
      <title>LED Toggle</title>
      <style>
        body {
          margin: 0;
          font-family: 'Segoe UI', sans-serif;
          background: linear-gradient(135deg, #141e30, #243b55);
          color: white;
          display: flex;
          justify-content: center;
          align-items: center;
          height: 100vh;
        }

        .card {
          background-color: #ffffff10;
          padding: 40px;
          border-radius: 20px;
          box-shadow: 0 10px 25px rgba(0,0,0,0.3);
          text-align: center;
          backdrop-filter: blur(8px);
        }

        h1 {
          margin-bottom: 30px;
          font-size: 32px;
        }

        .switch {
          position: relative;
          display: inline-block;
          width: 60px;
          height: 34px;
        }

        .switch input {
          opacity: 0;
          width: 0;
          height: 0;
        }

        .slider {
          position: absolute;
          cursor: pointer;
          top: 0; left: 0;
          right: 0; bottom: 0;
          background-color: #ccc;
          transition: 0.4s;
          border-radius: 34px;
        }

        .slider:before {
          position: absolute;
          content: "";
          height: 26px; width: 26px;
          left: 4px; bottom: 4px;
          background-color: white;
          transition: 0.4s;
          border-radius: 50%;
        }

        input:checked + .slider {
          background-color: #00c851;
        }

        input:checked + .slider:before {
          transform: translateX(26px);
        }
      </style>
      <script>
        function toggleLED(checkbox) {
          const state = checkbox.checked ? "on" : "off";
          fetch("/toggle?state=" + state, { cache: "no-cache" })
            .then(response => response.text())
            .then(data => console.log(data));
        }
      </script>
    </head>
    <body>
      <div class="card">
        <h1>LED Swtich</h1>
        <label class="switch">
          <input type="checkbox" onchange="toggleLED(this)">
          <span class="slider"></span>
        </label>
      </div>
    </body>
    </html>
  )rawliteral";

  server.send(200, "text/html", page);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("mDNS responder started at: http://");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
    server.on("/toggle", []() {
    String state = server.arg("state");
    Serial.println("LED state: " + state);
    
    if (state == "on") {
      digitalWrite(LED_BUILTIN, LOW); // Turn ON LED
    } else {
      digitalWrite(LED_BUILTIN, HIGH); // Turn OFF LED
    }

    server.send(200, "text/plain", "LED set to " + state);
  });

  server.begin();
}

void loop() {
  server.handleClient();
}
