// Import librairies requises
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <Servo.h>

// à remplacer avec vos identifiants wifi
const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";



// permet de dire que le graphbar possède 6 led
const int ledCount = 6;

// definition array led 
const int ledPins[] = {
  D1, D2, D3, D5, D6, D7
};



#define analogPin A0 // on utilise le pin A0 pour mesurer la tension du condensateur
#define chargePin 
#define dischargePin
#define resistorValue 10000.0F // on entre la valeur de la résistance que l'on utilise
// le F permet de mettre la valeur de la résistance en float

unsigned long startTime;
unsigned long elapsedTime
float microFarads;
float nanoFarads;
float mesureSonde;

// boolean pour l'ouverture du clapet %STATECLAPET%
bool isOpen;

// Stores LED state %STATELEDS%
String ledState;

// Stores motor state %STATEMOTOR%
String motorState;

// Stores sonde state %STATESONDE%
String sondeState;

// creation AsyncWebServer objet sur port 80
AsyncWebServer server(80);

// création de l'objet moteur
Servo motor;
// attache le servo motor au gpio D8
motor.attach(D8);

// exemple fonction
String getPressure() {
  float pressure = bme.readPressure() / 100.0F;
  Serial.println(pressure);
  return String(pressure);
}



// Remplacement placeholder avec valeur d'etat au travers des fonctions get()
String processor(const String& var) {
  Serial.println(var);
  if (var == "STATE") {
    if (digitalRead(ledPin)) {
      ledState = "ON";
    }
    else {
      ledState = "OFF";
    }
    Serial.print(ledState);
    return ledState;
  }
  else if (var == "TEMPERATURE") {
    return getTemperature();
  }
  else if (var == "HUMIDITY") {
    return getHumidity();
  }
  else if (var == "PRESSURE") {
    return getPressure();
  }
}

void setup() {
  // Port serie pour debugging
  Serial.begin(115200);

  // Initialize SPIFFS
  if (!SPIFFS.begin()) {
    Serial.println("une erreur s'est produite à l'initialisation du SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connexion au WiFi..");
  }

  // Print esp8266 Address IP locale
  Serial.println(WiFi.localIP());


  // Route pour root(racine du site web) / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Route pour charger fichiers style.css
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });

  // exemple
  // Route pour mettre GPIO led à HIGH
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest * request) {
    digitalWrite(ledPin, HIGH);
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  //exemple
  // Route pour mettre GPIO led à LOW
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest * request) {
    digitalWrite(ledPin, LOW);
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  //exemple
  // Route pour afficher IP/temperature avec fonction getTemperature()
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", getTemperature().c_str());
  });


  // Start server
  server.begin();

}

void loop() {
  // put your main code here, to run repeatedly:

}
