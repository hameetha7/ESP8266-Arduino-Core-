#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// Wi-Fi credentials
#define WIFI_SSID "Airtel_Space_Zee"
#define WIFI_PASSWORD "SpacezeE@1234"

// Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to Wi-Fi");

  // Firebase configuration
  config.host = "two-switch-control-default-rtdb.firebaseio.com"; // No https://
  config.signer.tokens.legacy_token = "YOUR_DATABASE_SECRET";     // Found in Firebase → Project Settings → Service Accounts

  // Start Firebase
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  // Relay pin setup
  pinMode(D1, OUTPUT);
}

void loop() {
  // Read integer from Firebase
  if (Firebase.getInt(fbdo, "/switchValue")) {
    if (fbdo.dataType() == "int") {
      int value = fbdo.intData();
      Serial.printf("Switch Value: %d\n", value);

      // Control relay
      digitalWrite(D1, value == 1 ? HIGH : LOW);
    }
  } else {
    Serial.printf("Firebase read failed: %s\n", fbdo.errorReason().c_str());
  }

  delay(1000);
}
