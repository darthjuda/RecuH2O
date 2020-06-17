// import librairie moteur
// import librairie niveaudeau
// import librairie wifi-shield
#include <Servo.h>

int tc = 0;

// module sonde 
int alimSonde = 2; //l'alimentation de la sonde est définie sur le pin 2
int sonde = A0; //La sonde est définie sur le pin A0

// module moteur
int motor = 11; // Le moteur est défini sur le pin 11
int pos = 0;
Servo myservo;

// module graphbar 
const int ledCount = 10 ; // permet de dire que le graphbar possede 10 leds
int ledPins[] = {
  19, 20, 21, 22, 23, 24, 25, 26, 27, 28 // Les leds sont définies sur les pins 19, 20, 21, 22, 23, 24, 25, 26, 27 et 28
};

//définir les différents niveaux:
float niveaudeau;

void setup() {
  // put your setup code here, to run once:
  pinMode(sonde, INPUT); // La sonde est définie en entrée
  pinMode(motor, OUTPUT); // Le moteur est défini en sortie
  for (int thisLed = 0; thisLed < ledCount; thisLed++){ // permet de sélectionner chaque led une a une 
    pinMode(ledPins[thisLed], OUTPUT); // on définie la led sélectionner comme une sortie
  }
   Serial.begin(9600);
}

/* lire entree sur analog pin 0:
  int sensorValue = analogRead(A0);
  // conversion lecture analogique (qui va par exemple de 0 - 1023) en un voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  // imprimer la valeur en console:
  Serial.println(voltage);
*/

void loop() {
  // put your main code here, to run repeatedly:
 

  }
}

void tempsCharge() {
  // si A0<648
  // 
}

void donneeSonde() {
  // surveille Tc
}

void onOffMoteur() { 
  if (lvl <= 100) {
    for( pos = 0 ; pos <= 90 ; pos ++ 1) {
      myservo.write(pos);
    }
  }
  else (lvl > 100) {
    for( pos = 90 ; pos >= 0 ; pos -- 1) {
      myservo.write(pos);
    }
  }
}

void turnOnTurnOfGraphbar() {
  // allumer la première led lorsque lvl >= 10
  // allumer la deuxième led lorsque lvl >= 20
  // allumer la troisième led lorsque lvl >= 30
  // allumer la quatrième led lorsque lvl >= 40
  // allumer la cinquième led lorsque lvl >= 50
  // allumer la sixième led lorsque lvl >= 60
  // allumer la septième led lorsque lvl >= 70
  // allumer la huitième led lorsque lvl >= 80
  // allumer la neuvième led lorsque lvl >= 90
  // allumer la dixième led lorsque lvl >= 100
}

int recupTc() {
  startTimer(tc) // on démarre le timer
  SerialPrintln("demarrage timer"); // on écrit sur l'écran "demarrage timer"
  do //tant que la condition est valable 
    int val = analogRead(sonde); // on stock la donnée lue sur le pin A0 dans val
    digitalWrite(alimSonde, HIGH); // on alimente la sonde 
    SerialPrintln("+5V sonde"); // on écrit sur l'écran "+5V sonde"
  while (val <= 648);
  stopTimer(tc); //on stop le timer
  SerialPrintln("stop timer"); // on écrit sur l'écran "stop timer"
  digitalWrite(alimSonde, LOW); // on arrete l'alimentation de la sonde 
  SerialPrintln("0V sonde"); // on écrit sur l'écran "0V sonde"
  SerialPrintln(tc) // on écrit la valeur de Tc
  return tc
}
