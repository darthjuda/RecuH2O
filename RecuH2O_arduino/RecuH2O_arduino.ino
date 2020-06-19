// import librairie moteur
// import librairie niveaudeau
// import librairie wifi-shield
#include <Servo.h>


// variables globales
unsigned long tc = 0;
int lvl = 0;
bool tcIsOn = false;
const int r = 220000;
float cu;


// module sonde
int alimSonde = 2; //l'alimentation de la sonde est définie sur le pin 2
int sonde = A0; //La sonde est définie sur le pin A0

// module moteur
Servo motor;
int pos = 0;


// module graphbar
const int ledCount = 10 ; // permet de dire que le graphbar possede 10 leds
int ledPins[] = {
  19, 20, 21, 22, 23, 24, 25, 26, 27, 28 // Les leds sont définies sur les pins 19, 20, 21, 22, 23, 24, 25, 26, 27 et 28
};

//définir les différents niveaux:


void setup() {
  // put your setup code here, to run once:
  pinMode(sonde, INPUT); // La sonde est définie en entrée
  motor.attach(11);
  for (int thisLed = 0; thisLed < ledCount; thisLed++) { // permet de sélectionner chaque led une a une
    pinMode(ledPins[thisLed], OUTPUT); // on définie la led sélectionner comme une sortie
  }
  Serial.begin(9600);
}

void loop() {
  
}

void onOffMoteur() {
  if (lvl <= 100) {
    for ( pos = 0 ; pos <= 90 ; pos++) {
      motor.write(pos);
    }
  }
  else {
    for ( pos = 90 ; pos >= 0 ; pos--) {
      motor.write(pos);
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
  // on démarre le timer et on allume la sonde
  tcIsOn = true;
  startTimer();
  Serial.print("demarrage timer"); // on écrit sur l'écran "demarrage timer"
  digitalWrite(alimSonde, HIGH);
  Serial.print("allumage sonde");

  // lecture de sonde jusqu'a sonde == 648
  int val = 0;
  do {
   val = analogRead(sonde);
   Serial.print(val);
   
  } while (val <= 648);

  //on stop le timer et on eteint la sonde
  tcIsOn = false;
  startTimer();
  Serial.print("stop timer"); // on écrit sur l'écran "stop timer"
  digitalWrite(alimSonde, LOW); // on arrete l'alimentation de la sonde
  Serial.print("extinction sonde"); // on écrit sur l'écran "0V sonde"
  Serial.print(tc); // on écrit la valeur de Tc

  return tc;
}

unsigned long startTimer() {
  if (tcIsOn) {
    tc = millis();
  }
  else {
    Serial.print(tc);
    return tc;
  }
}
