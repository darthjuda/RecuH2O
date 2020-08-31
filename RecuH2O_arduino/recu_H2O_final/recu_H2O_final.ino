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
Servo motor;

//varable pour stocker la requete HTTP
String header;
String adressIP;

// variables auxiliaires pour stocker l'état des sorties
String motorState = "off";
int niveauCuveState = niveauCuve
String sondeState = "off";

// assigner des variables en sorties aux pins GPIO
motor.attach(4);
const int ledPins = {
  14, 15, 16, 17, 18, 19, 20, 21
};

const int sonde = 0;

//current time
unsigned long currentTime = millis();

//previous time
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

////////////////////////////// mesure capacité ////////////////////////////////////////////////////

#define analogPin      0          // on utilise le pin A0 pour mesurer la tension du condensateur
#define chargePin      13         // on utilise le pin 13 pour charger le condensateur - connected to one end of the charging resistor
#define dischargePin   11         // on utilise le pin 11 pour décharger le condensateur
#define resistorValue  10000.0F   // on entre la valeur de la resistance que l'on utilise
// le F permet de mettre la valeur de la resistance en float
unsigned long startTime;
unsigned long elapsedTime;
float microFarads;                // on définit la variable microFarads en float pour garder la precision et faire des calculs
float nanoFarads;
float mesureSonde;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  //initialiser les variables en sorties
  pinMode(46, OUTPUT);
  pinMode(ledPins, OUTPUT);
  pinMode(sonde, OUTPUT);

  // on met les sorties en LOW
  digitalWrite(46, LOW);
  digitalWrite(ledPins, LOW);
  digitalWrite(sonde, LOW);

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

////////////////////////////// graphBar //////////////////////////////////////////////////////////

// initialisation graphBar sortie:
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT);
  }

////////////////////////////// mesure capacité ///////////////////////////////////////////////////

  pinMode(chargePin, OUTPUT);     // on met le pin de chargement de la sonde en sortie
  digitalWrite(chargePin, LOW);

}

////////////////////////////// loop //////////////////////////////////////////////////////////////

void loop() {
 
  WiFiClient client = server.available(); //écouter l'arrivé d'un cient

  if (client){  // si un nouveau client se connecte
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

            // faire qqch si le client envoie qqch de speciale 


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
            }

            // Etat led 
            client.println("<p>Etat du niveau de la cuve: " + niveauCuveState + "</p>");

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

            
            
          }
        }
      }
    }
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
  }

  graphBarDisplay(niveauCuve);

  mesureCapSonde();
  Serial.println(mesureSonde);
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

void graphBarDisplay(int niveau) {
  niveau -= 1; // on enlève 1 a la valeur du niveau
  for (int i = ledCount; i >= niveau; i--) { // pour i allant au nombre de led (10) a la valeur du niveau, on décrémente i de 1
    digitalWrite(ledPins[i], LOW); // on éteind la led correspondant a la valeur de i
  }

  for (int i = 0; i <= niveau; i++) { // pour i allant de 0 a la valeur du niveau, on incrémente i de 1
    digitalWrite(ledPins[i], HIGH); // on allume la led correspondant a la valeur de i
  }
}

float mesureCapSonde() {
  digitalWrite(chargePin, HIGH);  // on charge le condensateur 
  startTime = millis();

  while (analogRead(analogPin) < 648) {  // 647 correspond a  63.2% de 1023, qui correspond a la tension maximum
  }

  elapsedTime = millis() - startTime;
  // on convertit les millisecondes en secondes ( 10^-3 )
  microFarads = ((float)elapsedTime / resistorValue) * 1000;
  //  Serial.print(elapsedTime);       // on ecrit la valeur dans le moniteur serie
  //  Serial.print(" mS    ");         // on ecrit l'unite dans le moniteur serie


  if (microFarads > 1) {
    mesureSonde = microFarads;
    //    Serial.print((long)microFarads);       // on ecrit la valeur dans le moniteur serie
    //    Serial.println(" microFarads");        // on ecrit l'unite dans le moniteur serie
  }
  else
  {
    // si la valeur est plus petite que le microFarads, on la convertit en nanoFarads (10^-9 Farad).
    // c'est une solution de rechange car le Serial.print ne peux pas ecrire de float

    nanoFarads = microFarads * 1000.0; // on multiplie par 1000 pour convertir en nanoFarads (10^-9 Farads)
    mesureSonde = nanoFarads;
    //    Serial.print((long)nanoFarads);         // on ecrit la valeur dans le moniteur serie
    //    Serial.println(" nanoFarads");          // on ecrit l'unite dans le moniteur serie
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
