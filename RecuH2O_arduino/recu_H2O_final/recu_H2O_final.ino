#include <Servo.h>
#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "Reseau Wi-Fi de mehdi"
#define STAPSK  "emyTourniquet1988"
#endif

// pointeur vers les infos ssid et password
const char *ssid = STASSID;
const char *password = STAPSK;

//création de l'objet server de type WiFiServer en écoute sur le port 80
WiFiServer server(80);
<<<<<<< HEAD

// création de l'objet moteur
Servo motor;

//variable pour stocker la requete HTTP
String header;
=======
Servo motor;

//varable pour stocker la requete HTTP
String header;
String adressIP;
>>>>>>> d69f64bd42bd7eb5d4ad085e881a0d2734c948aa

// variables auxiliaires pour stocker l'état des sorties
int niveauCuve = 8; // mesureCapSonde()
String niveauCuveState = String(niveauCuve);
String motorState = "off";
<<<<<<< HEAD
String sondeState = "off";

// temps actuel pour la gestion du serveur web
=======
int niveauCuveState = niveauCuve
String sondeState = "off";

// assigner des variables en sorties aux pins GPIO
motor.attach(4);
const int ledPins = {
  14, 15, 16, 17, 18, 19, 20, 21
};

const int sonde = 0;

//current time
>>>>>>> d69f64bd42bd7eb5d4ad085e881a0d2734c948aa
unsigned long currentTime = millis();

//previous time pour la gestion du serveur web
unsigned long previousTime = 0;

// on definit timeoutTime en millisecondes
const long timeoutTime = 2000;
////////////////////////////// graphBar //////////////////////////////////////////////////////////

//permet de dire que le graphbar possede 10 led
const int ledCount = 8;

// les leds sont definies sur les pins ci dessous:
int ledPins[] = {
  14, 15, 16, 17, 18, 19, 20, 21
};

////////////////////////////// niveau /////////////////////////////////////////////////////////////

int niveauCuve = 8;
bool isOpen;
const int maxLvl = ledCount;

//permet de dire que le graphbar possede 8 led
const int ledCount = 8;

// les leds sont definies sur les pins ci dessous:
int ledPins[] = {
  D0, D1, D2, D3, D5, D6, D7, D8
};

// boolean pour ouverture clapet
bool isOpen;

// constante niveau max
const int maxLvl = ledCount;

<<<<<<< HEAD
#define analogPin      A0          // on utilise le pin A0 pour mesurer la tension du condensateur
#define chargePin      10         // on utilise le pin S2(11) pour charger le condensateur 
#define dischargePin   9         // on utilise le pin S3 (13) pour décharger le condensateur
#define resistorValue  10000.0F   // on entre la valeur de la resistance que l'on utilise // le F permet de mettre la valeur de la resistance en float
<<<<<<< HEAD

=======
=======
#define analogPin      0          // on utilise le pin A0 pour mesurer la tension du condensateur
#define chargePin      13         // on utilise le pin 13 pour charger le condensateur - connected to one end of the charging resistor
#define dischargePin   11         // on utilise le pin 11 pour décharger le condensateur
#define resistorValue  10000.0F   // on entre la valeur de la resistance que l'on utilise
// le F permet de mettre la valeur de la resistance en float
>>>>>>> 4466348cbd14aa207250ed717be99784c095f13d
>>>>>>> d69f64bd42bd7eb5d4ad085e881a0d2734c948aa
unsigned long startTime;
unsigned long elapsedTime;
float microFarads;                // on définit la variable microFarads en float pour garder la precision et faire des calculs
float nanoFarads;
float mesureSonde;

<<<<<<< HEAD

=======
>>>>>>> d69f64bd42bd7eb5d4ad085e881a0d2734c948aa
void setup() {
  // demarage liaison serie 115200 Bauds
  Serial.begin(115200);

<<<<<<< HEAD
  // attache le servo motor au gpio D10
  motor.attach(D10);


  //initialiser les leds en sortie
  for (int i = 0; i <= ledCount; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  //initialiser les pins leds a LOW
=======
<<<<<<< HEAD
  // attache le servo motor au gpio D10
  motor.attach(D10);
  

  //initialiser les variables en sorties
  
  for (int i = 0; i <= ledCount; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  
  pinMode(sonde, OUTPUT);

  // on met les sorties en LOW
  
>>>>>>> d69f64bd42bd7eb5d4ad085e881a0d2734c948aa
  for (int i = 0; i <= ledCount; i++) {
    digitalWrite(ledPins[i], LOW);
  }

<<<<<<< HEAD
  // on met le pin de chargement de la sonde en sortie
  pinMode(chargePin, OUTPUT);    
  // on met le pin de chargement de la sonde en LOW
  digitalWrite(chargePin, LOW);
=======
=======
  //initialiser les variables en sorties
  pinMode(46, OUTPUT);
  pinMode(ledPins, OUTPUT);
  pinMode(sonde, OUTPUT);

  // on met les sorties en LOW
  digitalWrite(46, LOW);
  digitalWrite(ledPins, LOW);
>>>>>>> 4466348cbd14aa207250ed717be99784c095f13d
  digitalWrite(sonde, LOW);
>>>>>>> d69f64bd42bd7eb5d4ad085e881a0d2734c948aa

  // connexion au réseau Wi-Fi avec le SSID et le mot de passe
  Serial.print("Tentative de connexion: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    deay(500);
    Serial.print(".");
  }

  //afficher les adresses IP locales et démarrer le serveur web
  Serial.println("");
  Serial.println("WiFi connecté.");
  Serial.println("Adresse IP: ");
  adressIP = WiFi.localIP();
  Serial.println(adressIP);
  server.begin();

<<<<<<< HEAD
=======
////////////////////////////// graphBar //////////////////////////////////////////////////////////

// initialisation graphBar sortie:
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT);
  }

////////////////////////////// mesure capacité ///////////////////////////////////////////////////

  pinMode(chargePin, OUTPUT);     // on met le pin de chargement de la sonde en sortie
  digitalWrite(chargePin, LOW);

>>>>>>> d69f64bd42bd7eb5d4ad085e881a0d2734c948aa
}

void loop() {
<<<<<<< HEAD
  // affichage du graphBar
  graphBarDisplay(niveauCuve);

  // control auto du clapet en fonction du niveau 
=======
<<<<<<< HEAD

  graphBarDisplay(niveauCuve);

>>>>>>> d69f64bd42bd7eb5d4ad085e881a0d2734c948aa
  switch (niveauCuve) {
    case 0 ...7:
      if (motorState == "on") {
        Serial.println("clapet deja ouvert");
      } else {
        closeGate();
        Serial.println(isOpen);
      }
      break;

    case maxLvl:
      if (motorState == "off") {
        Serial.println("clapet deja fermé");
      } else {
        openGate();
        Serial.println(isOpen);
      }
      break;
  }
<<<<<<< HEAD

  // gestion des connexions clients
  //écouter l'arrivé d'une connexion client
  WiFiClient client = server.available(); 
  
  if (client) { // si un nouveau client se connecte
=======

=======
 
>>>>>>> 4466348cbd14aa207250ed717be99784c095f13d
  WiFiClient client = server.available(); //écouter l'arrivé d'un cient

  if (client){  // si un nouveau client se connecte
>>>>>>> d69f64bd42bd7eb5d4ad085e881a0d2734c948aa
    Serial.println("Nouveau client. "); // on écrit un message sur le port série
    String currentLine = ""; // faire une chaine de caractere pour contenir les données du client entrant
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // faire une boucle tant que le client est connecté
      currentTime = millis();
      if(client.available()){ // s'il y a des bits a lire provenant du client
        char c = client.read(); // on lit un paquet
        Serial.write(c); //on l'ecrit sur le moniteur serie
        header += c; //on ajoute les bits que l'on vient de lire a la variable (String) 'header'
        if (c== '\n'){ //  si le bit est une nouvelle ligne de caractere
          // si la ligne courante est vide, on a 2 caractere de retour a la ligne un a cote de l'autre
          // c'est la fin de la requete HTTP du client, on envoi la reponse:
          if (CurrentLine.length() == 0 {
            // les en-tetes HTTP commencent toujours avec un code reponse (ex: HTTP/1.1 200 OK)
            // et un type de contenue comme ca le client sait quelle type de donnée arrive
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("connection: close");
            client.println();

<<<<<<< HEAD

=======
<<<<<<< HEAD
>>>>>>> d69f64bd42bd7eb5d4ad085e881a0d2734c948aa
            // faire qqch si le client envoie qqch de speciale
            // Allumer ou eteindre le moteur manuellement
            if (header.indexOf("GET /motor/on") >= 0) {
              Serial.println("GPIO1 on");
              motorState = "on";
              openGate();
            } else if (header.indexOf("GET /motor/off") >= 0) {
              Serial.println("GPIO1 off");
              motorState = "off";
              closeGate();
            }
<<<<<<< HEAD
=======

=======
            // faire qqch si le client envoie qqch de speciale 
>>>>>>> 4466348cbd14aa207250ed717be99784c095f13d
>>>>>>> d69f64bd42bd7eb5d4ad085e881a0d2734c948aa


            // Affichage page web en HTML et CSS 
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // code CSS pour le design de la page web
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #0394fc; border: 2px solid black; border-radius: 5px; color: black; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}");
            client.println(".buttonCuveVert {background-color: #12c412; border: 2px solid black; border-radius: 5px; color: black;");
            client.println(".buttonCuveOrange {background-color: #ff7b00; border: 2px solid black; border-radius: 5px; color: black;");
            client.println(".buttonCuveRouge {background-color: #ff0000; border: 2px solid black; border-radius: 5px; color: black;</style></head>");

            // En tete page web 
            client.println("<body><h1> Recu H20 </h1>");

<<<<<<< HEAD
=======
<<<<<<< HEAD
            // Affichage des variables d'etats


>>>>>>> d69f64bd42bd7eb5d4ad085e881a0d2734c948aa
            // Etat moteur
            client.println("<p>Etat du clapet: " + motorState + "</p>");
            // si etat clapet(moteur) = off affiché on sur le bouton
            if (motorState == "off") {
              //client.println("<p><a href=\"/addresseCONTROLPINMOTOR"><button class=\"button\">ON</button></a></p>");
              client.println("<p><a href=\"/motor/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              //client.println("<p><a href=\"addresse CONTROL PIN MOTOR"><button class="button button2\">OFF</button></a></p>");
              client.println("<p><a href=\"/motor/off\"><button class=\"button button2\">OFF</button></a></p>");
<<<<<<< HEAD
=======
=======
            // Affichage des variables d'etats 
            /*
             * // variables auxiliaires pour stocker l'état des sorties
                  String motorState = "off";
                  String ledPinsState = "off";
                  String sondeState = "off";
            */
            // Etat moteur
            client.println("<p>Etat du clapet: " + motorState + "</p>");
            // si etat clapet(moteur) = off affiché on sur le bouton
            if (motorState=="off") {
              client.println("<p><a href=\"addresse CONTROL PIN MOTOR"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"addresse CONTROL PIN MOTOR"><button class=\"button button2\">OFF</button></a></p>");
>>>>>>> 4466348cbd14aa207250ed717be99784c095f13d
>>>>>>> d69f64bd42bd7eb5d4ad085e881a0d2734c948aa
            }

            // Etat led 
            client.println("<p>Etat du niveau de la cuve: " + niveauCuveState + "</p>");
<<<<<<< HEAD

            // le switch permet d'afficher un bouton d'une certaine couleur sur la page web en fonction du niveau de la cuve
=======
<<<<<<< HEAD

>>>>>>> d69f64bd42bd7eb5d4ad085e881a0d2734c948aa
            switch (niveauCuve) {
              case 0 ...3:
                client.println("<p><button class=\"button buttonCuveVert\"><\button></p>");
                break;
=======
>>>>>>> 4466348cbd14aa207250ed717be99784c095f13d

<<<<<<< HEAD
              case 4 ...6:
                client.println("<p><button class=\"button buttonCuveOrange\"><\button></p>");
                break;

              case 7 ...8:
                client.println("<p><button class=\"button buttonCuveRouge\"><\button></p>");
                break;
            }

            // Etat Sonde
=======
           // le switch permet d'afficher un bouton d'une certaine couleur sur la page web en fonction du niveau de la cuve
              switch (niveauCuve){
                case 0 ...3:
                  client.println("<p><button class=\"button buttonCuveVert\"><\button></p>");
                break;

                case 4 ...6:
                   client.println("<p><button class=\"button buttonCuveOrange\"><\button></p>");
                break;

                case 7 ...8:
                  client.println("<p><button class=\"button buttonCuveRouge\"><\button></p>");
                break;

                default:
                  
              }
            // Etat sonde
<<<<<<< HEAD
            // TODO: afficher l'etat de la sonde en web

>>>>>>> d69f64bd42bd7eb5d4ad085e881a0d2734c948aa
            client.println("<p>Etat Sonde: " + sondeState + "</p>");
            if (sondeState == "off") {
              client.println("<p><a href=\"/\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/\"><button class=\"button button2\">OFF</button></a></p>");
            }
=======
>>>>>>> 4466348cbd14aa207250ed717be99784c095f13d

<<<<<<< HEAD
=======
            
            
>>>>>>> d69f64bd42bd7eb5d4ad085e881a0d2734c948aa
          }
        }
      }
    }
<<<<<<< HEAD

=======
<<<<<<< HEAD
>>>>>>> d69f64bd42bd7eb5d4ad085e881a0d2734c948aa
    // Libere la variable header
    header = "";
    // Termine la connection avec le client
    client.stop();
    Serial.println("Client déconnecté.");
    Serial.println("");
  }
<<<<<<< HEAD
  
}

// affichage du niveau sur les led constituant le graph bar
void graphBarDisplay(int niveau) {
  niveau -= 1; // on enlève 1 a la valeur du niveau
  for (int i = ledCount; i >= niveau; i--) { // pour i allant au nombre de led (8) a la valeur du niveau, on décrémente i de 1
    digitalWrite(ledPins[i], LOW); // on éteind la led correspondant a la valeur de i
  }

  for (int i = 0; i <= niveau; i++) { // pour i allant de 0 a la valeur du niveau, on incrémente i de 1
    digitalWrite(ledPins[i], HIGH); // on allume la led correspondant a la valeur de i
=======

=======
    }

  switch (niveauCuve) {
    case 0 ...9:
      openGate();
      Serial.println(isOpen);
      break;

    case maxLvl:
      closeGate();
      Serial.println(isOpen);
      break;
>>>>>>> d69f64bd42bd7eb5d4ad085e881a0d2734c948aa
  }

  graphBarDisplay(niveauCuve);

  mesureCapSonde();
  Serial.println(mesureSonde);
>>>>>>> 4466348cbd14aa207250ed717be99784c095f13d
}

// gestion du clapet
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

<<<<<<< HEAD
// mesure de la capacitance de la sonde
=======
void graphBarDisplay(int niveau) {
  niveau -= 1; // on enlève 1 a la valeur du niveau
  for (int i = ledCount; i >= niveau; i--) { // pour i allant au nombre de led (8) a la valeur du niveau, on décrémente i de 1
    digitalWrite(ledPins[i], LOW); // on éteind la led correspondant a la valeur de i
  }

  for (int i = 0; i <= niveau; i++) { // pour i allant de 0 a la valeur du niveau, on incrémente i de 1
    digitalWrite(ledPins[i], HIGH); // on allume la led correspondant a la valeur de i
  }
}

>>>>>>> d69f64bd42bd7eb5d4ad085e881a0d2734c948aa
float mesureCapSonde() {
  digitalWrite(chargePin, HIGH);  // on charge le condensateur 
  startTime = millis();

  while (analogRead(analogPin) < 648) {  // 647 correspond a  63.2% de 1023, qui correspond a la tension maximum
  }

  elapsedTime = millis() - startTime;
  // on convertit les millisecondes en secondes ( 10^-3 )
  microFarads = ((float)elapsedTime / resistorValue) * 1000;
<<<<<<< HEAD
  Serial.print(elapsedTime);       // on ecrit la valeur dans le moniteur serie
  Serial.print(" mS    ");         // on ecrit l'unite dans le moniteur serie
  //  Serial.print(elapsedTime);       // on ecrit la valeur dans le moniteur serie
  //  Serial.print(" mS    ");         // on ecrit l'unite dans le moniteur serie
=======
<<<<<<< HEAD
  Serial.print(elapsedTime);       // on ecrit la valeur dans le moniteur serie
  Serial.print(" mS    ");         // on ecrit l'unite dans le moniteur serie
=======
  //  Serial.print(elapsedTime);       // on ecrit la valeur dans le moniteur serie
  //  Serial.print(" mS    ");         // on ecrit l'unite dans le moniteur serie
>>>>>>> 4466348cbd14aa207250ed717be99784c095f13d
>>>>>>> d69f64bd42bd7eb5d4ad085e881a0d2734c948aa


  if (microFarads > 1) {
    mesureSonde = microFarads;
<<<<<<< HEAD
    Serial.print((long)microFarads);       // on ecrit la valeur dans le moniteur serie
    Serial.println(" microFarads");        // on ecrit l'unite dans le moniteur serie
    //    Serial.print((long)microFarads);       // on ecrit la valeur dans le moniteur serie
    //    Serial.println(" microFarads");        // on ecrit l'unite dans le moniteur serie
=======
<<<<<<< HEAD
    Serial.print((long)microFarads);       // on ecrit la valeur dans le moniteur serie
    Serial.println(" microFarads");        // on ecrit l'unite dans le moniteur serie
=======
    //    Serial.print((long)microFarads);       // on ecrit la valeur dans le moniteur serie
    //    Serial.println(" microFarads");        // on ecrit l'unite dans le moniteur serie
>>>>>>> 4466348cbd14aa207250ed717be99784c095f13d
>>>>>>> d69f64bd42bd7eb5d4ad085e881a0d2734c948aa
  }
  else
  {
    // si la valeur est plus petite que le microFarads, on la convertit en nanoFarads (10^-9 Farad).
    // c'est une solution de rechange car le Serial.print ne peux pas ecrire de float

    nanoFarads = microFarads * 1000.0; // on multiplie par 1000 pour convertir en nanoFarads (10^-9 Farads)
    mesureSonde = nanoFarads;
<<<<<<< HEAD
    Serial.print((long)nanoFarads);         // on ecrit la valeur dans le moniteur serie
    Serial.println(" nanoFarads");          // on ecrit l'unite dans le moniteur serie
    //    Serial.print((long)nanoFarads);         // on ecrit la valeur dans le moniteur serie
    //    Serial.println(" nanoFarads");          // on ecrit l'unite dans le moniteur serie
=======
<<<<<<< HEAD
    Serial.print((long)nanoFarads);         // on ecrit la valeur dans le moniteur serie
    Serial.println(" nanoFarads");          // on ecrit l'unite dans le moniteur serie
=======
    //    Serial.print((long)nanoFarads);         // on ecrit la valeur dans le moniteur serie
    //    Serial.println(" nanoFarads");          // on ecrit l'unite dans le moniteur serie
>>>>>>> 4466348cbd14aa207250ed717be99784c095f13d
>>>>>>> d69f64bd42bd7eb5d4ad085e881a0d2734c948aa
  }

  /* dicharge the capacitor  */
  digitalWrite(chargePin, LOW);             // on stoppe l'alimentation du condensateur
  pinMode(dischargePin, OUTPUT);            // on met le pin de dechargement en sortie
  digitalWrite(dischargePin, LOW);          // on alimente le pin de dechargement 
  while (analogRead(analogPin) > 0) {       // tant que la valeur lue sur le pin A0 est superieur a 0
  }

  pinMode(dischargePin, INPUT);            // on met la broche de dechargement en entree

  return mesureSonde;
}

// traduction de la capacitance en % du niveau de cuve
