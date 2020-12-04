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

const int ledPinR = D1;
const int ledPinR2 = D2;

int etatLed = LOW;

unsigned long previousMillis = 0;

const long interval = 1000;



#define analogPin A0 // on utilise le pin A0 pour mesurer la tension du condensateur
#define chargePin 9  // on utilise le pin S2(9) pour charger le condensateur
#define dischargePin 10  // on utilise le pin S3(10) pour décharger le condensateur
#define resistorValue 10000.0F // on entre la valeur de la résistance que l'on utilise
// le F permet de mettre la valeur de la résistance en float

unsigned long startTime; // variable pour stocker la valeur du timer
unsigned long elapsedTime; // variable pour le temps de chargement
float microFarads; // variable pour les microFarads
float nanoFarads; // variable pour les nanoFarads
float mesureSonde; // variable pour stocker la mesure de la sonde

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

// Stocker la variable pour le niveau en pourcentage
float level;

// valeur de la capacitance lorsque la cuve est vide Ɛ
const float capEmpty = 38.82 * 10 * -3; // 38.82 est en picofarad donc on multiplie par 10^-3 pour le convertir en nanofarad

// valeur de la capacitance lorsque la cuve est pleine
const float capFull = 3.11; // la valeur est en nano farad

//valeur de la capacitance à l'instant ou l'on mesure
float capInstant; // on définit capInstant en nombre décimal

// creation AsyncWebServer objet sur port 80
AsyncWebServer server(80);

// création de l'objet moteur
Servo motor;

// exemple fonction
//String getPressure() {
//  float pressure = bme.readPressure() / 100.0F;
//  Serial.println(pressure);
//  return String(pressure);
//}

void measureSonde() {

  unsigned long millisActuel = millis();
  const long intervalMesure = 30000;

  if (millisActuel - previousMillis >= intervalMesure) {
    previousMillis = millisActuel;

    digitalWrite(chargePin, HIGH);  // on charge le condensateur
    startTime = millis(); // on démarre le timer

    while (analogRead(analogPin) < 648) {  // 647 correspond a  63.2% de 1023, qui correspond a la tension maximum
    } // tant que le nombre de bits lu sur A0 n'est pas égal à 647, on ne fait rien

    elapsedTime = millis() - startTime;

    // décharger le condensateur
    digitalWrite(chargePin, LOW);             // on stoppe l'alimentation du condensateur
    pinMode(dischargePin, OUTPUT);            // on met le pin de dechargement en sortie
    digitalWrite(dischargePin, LOW);          // on alimente le pin de dechargement
    while (analogRead(analogPin) > 0) {       // tant que la valeur lue sur le pin A0 est superieur a 0
    }

    pinMode(dischargePin, INPUT);            // on met la broche de dechargement en entree

    microFarads = ((float)elapsedTime / resistorValue) * 1000; // on convertit les millisecondes en secondes (10^-3)

    Serial.print(elapsedTime);       // on ecrit la valeur dans le moniteur serie
    Serial.print(" mS    ");         // on ecrit l'unite dans le moniteur serie

    if (microFarads > 1) {
      mesureSonde = microFarads;
      Serial.print((long)microFarads);       // on ecrit la valeur dans le moniteur serie
      Serial.println(" microFarads");  // on ecrit l'unite dans le moniteur serie
    }
    else {
      // si la valeur est plus petite que le microFarads, on la convertit en nanoFarads (10^-9 Farad).
      // c'est une solution de rechange car le Serial.print ne peux pas ecrire de float

      nanoFarads = microFarads * 1000.0; // on multiplie par 1000 pour convertir en nanoFarads (10^-9 Farads)
      mesureSonde = nanoFarads;
      Serial.print((long)nanoFarads);         // on ecrit la valeur dans le moniteur serie
      Serial.println(" nanoFarads");          // on ecrit l'unite dans le moniteur serie
    }

    capInstant = mesureSonde;

    niveau = ((capInstant * 100) / capFull);    //transforme la capacitance en niveau en %
    niveau = int(niveau) + 1;
    
    

// ATTENTION niveau est un INT il faudra faire un arrondie a l'entier superieur
    niveau = (niveau * 6) / 100;               // on transforme le niveau en % en niveau compris entre 0 et 6


  /*
  vérifier état sonde:
  si capvide < Capinstant < capfull -> sondestate = "ok"
  sinon sondestate = "error"
  appeler displayLed(niveau, sondeState)
  */

    if (( capInstant > capEmpty) && (capInstant < capFull)) {
      sondeState = "ok";
      Serial.print(sondeState);
    }
    else {
      sondeState = "error";
      Serial.print(sondeState);
    }

    displayLed(niveau, sondeState);
  }

}

void displayLed(int niveau, String sondeState) {

  /*
      si sondeState == "ok" -> afficher les en fonction du parametre niveau
      sinon (sondeState == "erreur" -> faire clignoter les deux led rouge ensemble sans la fonction delay
  */
  if (sondeState == "ok") {
    niveau -= 1; // on enlève 1 a la valeur du niveau
    for (int i = ledCount; i >= niveau; i--) { // pour i allant au nombre de led (6) a la valeur du niveau, on décrémente i de 1
      digitalWrite(ledPins[i], LOW); // on éteind la led correspondant a la valeur de i
    }

    for (int i = 0; i <= niveau; i++) { // pour i allant de 0 a la valeur du niveau, on incrémente i de 1
      digitalWrite(ledPins[i], HIGH); // on allume la led correspondant a la valeur de i
    }
  }

  else {
    pinMode(ledPinR, OUTPUT);
    pinMode(ledPinR2, OUTPUT);
    unsigned long millisActuel = millis();

    if (millisActuel - previousMillis >= interval) {
      previousMillis = millisActuel;

      if (etatLed == LOW) {
        etatLed = HIGH;
      }
      else {
        etatLed = LOW;
      }

      digitalWrite(ledPinR, etatLed);
      digitalWrite(ledPinR2, etatLed);
    }
  }
}

void openGate() {

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
}

void closeGate() {

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
}




// Remplacement placeholder avec valeur d'etat au travers des fonctions get()
String processor(const String& var) {
  Serial.println(var);
  if (var == "STATECLAPET") {
    if (isOpen) {
      return "ouvert";
    }
    else {
      return "fermé";
    }
    Serial.print(isOpen);
  }
  else if (var == "STATESONDE") {
    return sondeState;
  }
  else if (var == "STATEMOTOR") {
    return motorState;
  }
  else if (var == "STATELEDS") {
    return ledState;
  }
  else if (var == "LEVEL") {
    return ;
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

  // attache le servo motor au gpio D8
  motor.attach(15);

  // Route pour root(racine du site web) / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Route pour charger fichiers style.css
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/style.css", "text/css");
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

}


void loop() {
  // effectue une mesure toutes les 30 secondes -> const long intervalMesure
  measureSonde()

}
