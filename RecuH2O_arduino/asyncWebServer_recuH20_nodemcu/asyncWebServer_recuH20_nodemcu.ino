// Import librairies requises
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <Servo.h>


// à remplacer avec vos identifiants wifi
const char* ssid = "Reseau Wi-Fi de mehdi";
const char* password = "emyTourniquet1988";



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

// entier pour sauvegarder le niveau
int niveau;

// valeur de la capacitance lorsque la cuve est pleine
float capFull;

//valeur de la capacitance à l'instant ou l'on mesure
float capInstant;

// creation AsyncWebServer objet sur port 80
AsyncWebServer server(80);

// création de l'objet moteur
Servo motor;
// attache le servo motor au gpio D8
motor.attach(D8);

// on créer une booléene pour avoir une condition pour connaitre l'état du moteur
bool isOpen;

// exemple fonction
String getPressure() {
  float pressure = bme.readPressure() / 100.0F;
  Serial.println(pressure);
  return String(pressure);
}

int measureSonde() {

  analogRead(A0); // mesure de la capacitance //FAUX!!!!!!!!
  niveau = ((capInstant*100)/capFull) //transforme la capacitance en niveau en %
  niveau = (niveau*6)/100 // on transforme le niveau en % en niveau compris entre 0 et 6
  return int(niveau)
}

int displayLed(niveau) {

  niveau -= 1; // on enlève 1 a la valeur du niveau
  for (int i = ledCount; i >= niveau; i--) { // pour i allant au nombre de led (6) a la valeur du niveau, on décrémente i de 1
    digitalWrite(ledPins[i], LOW); // on éteind la led correspondant a la valeur de i
  }

  for (int i = 0; i <= niveau; i++) { // pour i allant de 0 a la valeur du niveau, on incrémente i de 1
    digitalWrite(ledPins[i], HIGH); // on allume la led correspondant a la valeur de i
    return int(nombre de led allumée)
  }
}

String openGate() {

  if (isOpen) {
    Serial.println("clapet deja ouvert");
  }
  else {
    for (int pos = 90; pos >= 0; pos--) { // on passe de la position 90 a 0 en décrémentant de 1 pas a chaque tour de la boucle
      motor.write(pos); // on dit au moteur de se mettre a la valeur de pos
      delay(15);// on attend 15 ms pour laisser le temps au moteur de se mettre en position
    }
    isOpen = true;
    Serial.println("ouverture clapet");
  }
  return (isOpen)

}

String closeGate() {
  if (!isOpen) {
    Serial.println("clapet deja ferme");
  }
  else {
    for (int pos = 0; pos <= 90; pos++) { // on passe de la position 0 a 90 en incrémentant de 1 pas a chaque tour de la boucle
      motor.write(pos); // on dit au moteur de se mettre a la valeur de pos
      delay(15); // on attend 15 ms pour laisser le temps au moteur de se mettre en position
    }
    isOpen = false;
    Serial.println("fermeture clapet");
  }
  return (isOpen)

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
