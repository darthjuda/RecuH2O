// Import librairies requises
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>



// à remplacer avec vos identifiants wifi
const char* ssid = "Reseau Wi-Fi de mehdi";
const char* password = "emyTourniquet1988";

// definition de l'adresse 0x27 et creation de l'objet lcd 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);


#define analogPin A0 // on utilise le pin A0 pour mesurer la tension du condensateur
#define dischargePin D5  // on utilise le pin D5 pour décharger le condensateur
#define chargePin_1 D6  // on utilise le pin D6 pour charger le condensateur
#define chargePin_2 D7  // on utilise le pin D7 pour charger le condensateur
//#define chargePin_3 D3  // on utilise le pin D3 pour charger le condensateur
#define resistorValue 10000.0F // on entre la valeur de la résistance que l'on utilise
// le F permet de "caster" la valeur de la résistance en float

int U; //tension actuelle sonde(condensateur)

unsigned long startTime; // variable pour stocker la valeur du timer
unsigned long elapsedTime; // variable pour le temps de chargement

float microFarads; // variable pour les microFarads
float nanoFarads;  // variable pour les nanoFarads
float picoFarads;  // variable pour les picoFarads
float mesureSonde; // variable pour stocker la mesure de la sonde

// boolean pour l'ouverture du clapet %STATECLAPET%
bool isOpen;

// Stores LED state %STATELEDS%
String ledState;

// Stores motor state %STATEMOTOR%
String motorState;

// Stores sonde state %STATESONDE%
String sondeState;

// Stocker la variable pour le niveau en pourcentage
float niveau;

// valeur de la capacitance lorsque la cuve est vide
const float CEmpty = 1.71 * pow(10, -11); // cf calcul capacitance à vide

// valeur de la capacitance lorsque la cuve est pleine
const float CFull = 1.41 * pow(10, -9); // cf calcul capacitance pleine


// creation AsyncWebServer objet sur port 80
AsyncWebServer server(80);

// création de l'objet moteur
Servo motor;

void setup() {
  // Port serie pour debugging
  Serial.begin(115200);

  // Initialize SPIFFS
  if (!SPIFFS.begin()) {
    Serial.println("une erreur s'est produite à l'initialisation du SPIFFS");
    return;
  }

  // Initialize LCD
  lcd.begin();  // initialisation du lcd
  lcd.backlight(); // Allumage du retroeclairage
  lcd.setCursor(0, 0);

  lcd.print("Recu H2O\n");
  lcd.setCursor(0, 1);
  lcd.print("Bienvenue\n");


  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connexion au WiFi..");
  }

  // Print esp8266 Address IP locale
  Serial.println("Addresse IP:");
  Serial.println(WiFi.localIP());

  // attache le servo motor au gpio D4
  motor.attach(D4);

  // Route pour root(racine du site web) / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", String(), false, processor);
    Serial.println("Serveur: -> /");
  });

  // Route pour charger fichiers style.css
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/style.css", "text/css");
    Serial.println("Serveur: -> /styles.css");
  });

  // Route pour ouvrir le clapet
  server.on("/opengate", HTTP_GET, [](AsyncWebServerRequest * request) {
    openGate();
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Route pour fermer le clapet
  server.on("/closegate", HTTP_GET, [](AsyncWebServerRequest * request) {
    closeGate();
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  //  //exemple
  //  // Route pour afficher IP/temperature avec fonction getTemperature()
  //  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest * request) {
  //    request->send_P(200, "text/plain", getTemperature().c_str());
  //  });


  // Start server
  server.begin();
  Serial.println("Serveur: ON");

}




// exemple fonction
//String getPressure() {
//  float pressure = bme.readPressure() / 100.0F;
//  Serial.println(pressure);
//  return String(pressure);
//}

void measureSonde() {

  pinMode(chargePin_1, OUTPUT);
  digitalWrite(chargePin_1, HIGH);  // mise en charge de la sonde

  startTime = millis();  // demarrage du timer

  while (analogRead (analogPin) < 648) {
    // Attendre que le condensateur est atteint 63,2% de sa charge: t = R*C
    delay(0);
  }

  elapsedTime = millis() - startTime;  // Déterminer le temps de chargement

  microFarads = ((float) elapsedTime / 10000) * 1000;
  niveau = ((microFarads * 100) / CFull); //transforme la capacitance en niveau en %
  if (microFarads > CEmpty && microFarads < CFull) {
    sondeState = "OK";
  }
  else {
    sondeState = "Error";
  }

  Serial.print("t1 = ");
  Serial.print(elapsedTime);
  Serial.println(" ms  ");

  digitalWrite(chargePin_1, LOW);
  pinMode(chargePin_1, INPUT);

  pinMode(dischargePin, OUTPUT);
  digitalWrite(dischargePin, LOW);  // Permet au condensateur de se décharger

  while (analogRead(analogPin) > 0) {
    delay(0);
    // Ne rien faire tant que le condensateur n'est pas déchargé
  }

  U = analogRead(analogPin);
  Serial.println(U);

  pinMode(dischargePin, INPUT);  // Empêche la décharge du condensateur

  if (elapsedTime > 10) {         // grande capacité

    Serial.print("C: ");
    Serial.print (microFarads, 1);
    Serial.println (" uF");

    delay(500);
  }
  else {
    pinMode(chargePin_2, OUTPUT);
    digitalWrite(chargePin_2, HIGH);  //  mise en charge de la sonde

    startTime = millis();  // demarrage du timer

    while (analogRead(analogPin) < 648) {
      // Attendre que le condensateur est atteint 63,2% de sa charge: t = R*C
      delay(0);
    }

    elapsedTime = millis() - startTime;
    Serial.print("t2 = ");
    Serial.print(elapsedTime);
    Serial.println(" ms  ");

    nanoFarads = ((float) elapsedTime / 47) * 10;
    niveau = ((nanoFarads * 100) / CFull); //transforme la capacitance en niveau en %
    if (nanoFarads > CEmpty && nanoFarads < CFull) {
      sondeState = "OK";
    }
    else {
      sondeState = "Error";
    }

    digitalWrite(chargePin_2, LOW);
    pinMode(chargePin_2, INPUT);

    pinMode(dischargePin, OUTPUT);
    digitalWrite(dischargePin, LOW);

    while (analogRead(analogPin) > 0) {
      // Ne rien faire tant que le condensateur n'est pas déchargé
      delay(0);
    }

    U = analogRead(analogPin);
    Serial.println(U);

    pinMode(dischargePin, INPUT);

    if (elapsedTime > 10) {
      Serial.print("C: ");
      Serial.print (nanoFarads, 1);
      Serial.println (" nF");

      delay(500);
    }
//    else {
//      pinMode(chargePin_3, OUTPUT);
//      digitalWrite(chargePin_3, HIGH);
//
//      startTime = millis();
//
//      while (analogRead(analogPin) < 648) {
//        //U = analogRead(analogPin);
//        //Serial.println(U);
//      }
//
//      elapsedTime = millis() - startTime;
//
//      Serial.print("t3 = ");
//      Serial.print(elapsedTime);
//      Serial.println(" ms  ");
//
//      picoFarads = ((float) elapsedTime / 1) * 1 - 50.0;   // Capacité moins offset!
//      niveau = ((picoFarads * 100) / CFull); //transforme la capacitance en niveau en %
//      if (picoFarads > CEmpty && picoFarads < CFull) {
//        sondeState = "OK";
//      }
//      else {
//        sondeState = "Error";
//      }
//
//      Serial.print("C: ");
//      Serial.print(picoFarads, 1);
//      Serial.println (" pF");
//
//      yield();
//
//      digitalWrite(chargePin_3, LOW);
//      pinMode(chargePin_3, INPUT);
//
//      pinMode(dischargePin, OUTPUT);
//      digitalWrite(dischargePin, LOW);
//
//      while (analogRead(analogPin) > 0) {
//
//      }
//
//      U = analogRead(analogPin);
//      Serial.println(U);
//
//      pinMode(dischargePin, INPUT);
//
//    }
  }
}



void openGate() {

  if (isOpen) {
    Serial.println("clapet deja ouvert!");
  }
  else {
    for (int pos = 90; pos >= 0; pos--) { // on passe de la position 90 a 0 en décrémentant de 1 pas a chaque tour de la boucle
      motor.write(pos); // on dit au moteur de se mettre a la valeur de pos
      delay(15);// on attend 15 ms pour laisser le temps au moteur de se mettre en position
    }
    isOpen = true;
    Serial.println("ouverture clapet");
  }
}

void closeGate() {

  if (!isOpen) {
    Serial.println("clapet deja ferme!");
  }
  else {
    for (int pos = 0; pos <= 90; pos++) { // on passe de la position 0 a 90 en incrémentant de 1 pas a chaque tour de la boucle
      motor.write(pos); // on dit au moteur de se mettre a la valeur de pos
      delay(15); // on attend 15 ms pour laisser le temps au moteur de se mettre en position
    }
    isOpen = false;
    Serial.println("fermeture clapet");
  }
}




// Remplacement placeholder avec valeur d'etat au travers des fonctions get()
String processor(const String& var) {
  //Serial.println(var);
  if (var == "STATECLAPET") {
    if (isOpen) {
      return "ouvert";
    }
    else {
      return "fermé";
    }
    //Serial.print(isOpen);
  }
  else if (var == "STATESONDE") {
    return sondeState;
  }
  else if (var == "STATEMOTOR") {
    return motorState;
  }
  else if (var == "LEVEL") {
    return String(niveau);
  }
}



void loop() {
  // effectue une mesure toutes les 30 secondes -> const long intervalMesure
  measureSonde();
  delay(5000);

}
