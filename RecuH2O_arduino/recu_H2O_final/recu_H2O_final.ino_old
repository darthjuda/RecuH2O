////////////////////////////// Servo Motor ///////////////////////////////////////////////////////

#include <Servo.h>
Servo motor;

////////////////////////////// graphBar //////////////////////////////////////////////////////////

//permet de dire que le graphbar possede 10 led
const int ledCount = 10;

// les leds sont definies sur les pins ci dessous:
int ledPins[] = {
  14, 15, 16, 17, 18, 19, 20, 21, 22, 23
};

////////////////////////////// niveau /////////////////////////////////////////////////////////////

int niveauCuve = 10;
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
  Serial.begin(9600);

////////////////////////////// Servo Motor ///////////////////////////////////////////////////////

  motor.attach(46);

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
