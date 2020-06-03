// import librairie moteur
// import librairie niveaudeau
// import librairie wifi-shield

int graphbar = 5;
int motor = 6;

//définir les différents niveaux:
float niveaudeau;

void setup() {
  // put your setup code here, to run once:
  pinMode(graphbar, OUTPUT);
  pinMode(motor, OUTPUT);

  
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
  switch (expression) {
    case /* constant-expression */:
      /* code */
      break;

    default:
      break;
      //permet de choisir entre plusieurs alternative

      // une fonction qui permet de prendre la tension la plus haute ci cela existe
  }
}
