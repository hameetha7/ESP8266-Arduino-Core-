README – Firebase Switch Control Device
Version: 1.0
Author: Syed Hameetha

📌 Project Overview
This project demonstrates how to control an electrical device remotely using Firebase Realtime Database and a NodeMCU ESP8266 microcontroller. The device's ON/OFF status is updated through Firebase, and the ESP8266 listens for changes in real time to switch a relay accordingly.

🛠️ Hardware Requirements
NodeMCU ESP8266 development board

Relay Module (5V or 3.3V depending on ESP8266 logic)

Push Button (optional, for manual control)

Jumper Wires

Breadboard

Power Supply (USB or external)

Load (e.g., light bulb, fan, or LED)

💻 Software Requirements
Arduino IDE (latest version recommended)

Firebase Arduino Client Library for ESP8266

ESP8266 Board Package installed in Arduino IDE

Firebase Project with Realtime Database enabled

⚙️ Firebase Setup
Go to Firebase Console and create a new project.

Navigate to Realtime Database → Create Database.

Set rules for testing:

json
Copy
Edit
{
  "rules": {
    ".read": "true",
    ".write": "true"
  }
}
Copy your Database URL (e.g., https://your-project-id-default-rtdb.firebaseio.com/).

Get your Database Secret from Project Settings → Service Accounts → Database Secrets.

🔌 Circuit Connections
ESP8266 Pin	Relay Pin	Description
D1	IN	Relay Signal Input
3V3	VCC	Relay Power Supply
GND	GND	Relay Ground
(Optional) D2	Push Button	Manual Control

📜 Arduino Code
Install Firebase ESP8266 Client Library via Arduino IDE Library Manager.

Install ESP8266 Boards in Arduino IDE (Tools → Board Manager).

Use the sample code below (update with your Firebase credentials):

cpp
Copy
Edit
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#define FIREBASE_HOST "your-project-id-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "your-database-secret"
#define WIFI_SSID "your-wifi-name"
#define WIFI_PASSWORD "your-wifi-password"

FirebaseData firebaseData;
int relayPin = D1;

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  
  pinMode(relayPin, OUTPUT);
}

void loop() {
  if (Firebase.getInt(firebaseData, "/switch")) {
    int switchState = firebaseData.intData();
    digitalWrite(relayPin, switchState ? LOW : HIGH); // Active LOW relay
    Serial.println(switchState ? "Relay ON" : "Relay OFF");
  }
  delay(500);
}
🌐 Web/Android Control
Create a small HTML page or use Firebase Console to set /switch value to:

1 → Turns relay ON

0 → Turns relay OFF

🧪 Testing
Upload the code to ESP8266.

Open Serial Monitor to verify connection.

Change /switch value from Firebase Console or webpage and see the relay switch.

⚠️ Safety Notes
If controlling high-voltage appliances, ensure proper insulation and follow electrical safety guidelines.

Use opto-isolated relay modules for safer operation.

📄 License
This project is free to use for educational and personal purposes.
