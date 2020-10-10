#include <SoftwareSerial.h>
SoftwareSerial BLUET(10, 11); //10 TX, 11 RX.

int E = 2;
int V = 3;
int P = 5;
int T = 8;

int BT = 0;

int estadoE = 0;
int estadoP = 0;
int estadoV = 0;
int estadoT = 0;

const int sensorPin = A0;
int value;
float millivolts;
float celsius;

void setup()
{
  BLUET.begin(9600);
  Serial.begin(9600);

  pinMode(E, OUTPUT);
  pinMode(P, OUTPUT);
  pinMode(V, OUTPUT);
  pinMode(T, OUTPUT);
}

void loop()
{
  Temp();

  if (BLUET.available()) {
    BT = BLUET.read();
  }

  switch (BT) {
    case '0':
      estadoE = 0;
      break;

    case '1':
      estadoE = 1;
      break;

    case '2':
      estadoP = 0;
      break;

    case '3':
      estadoP = 1;
      break;

    case '4':
      estadoV = 0;
      break;

    case '5':
      estadoV = 1;
      break;

  }
  if (estadoE == 0 && estadoP == 0 && estadoV == 0) {
    Cero();
  }
  if (estadoE == 1 && estadoP == 0 && estadoV == 0) {
    Uno();
  }
  if (estadoE == 0 && estadoP == 1 && estadoV == 0) {
    Dos();
  }
  if (estadoE == 1 && estadoP == 1 && estadoV == 0) {
    Tres();
  }
  if (estadoE == 0 && estadoP == 0 && estadoV == 1) {
    Cuatro();
  }
  if (estadoE == 1 && estadoP == 0 && estadoV == 1) {
    Cinco();
  }
  if (estadoE == 0 && estadoP == 1 && estadoV == 1) {
    Seis();
  }
  if (estadoE == 1 && estadoP == 1 && estadoV == 1) {
    Siete();
  }
}

void Temp() {
  value = analogRead(sensorPin);
  millivolts = (value / 1023.0) * 5000;
  celsius = millivolts / 10;
  if (celsius >= 40.0) {
    estadoT = 0;
    digitalWrite(T, LOW);
  } else {
    estadoT = 1;
    digitalWrite(T, HIGH);
  }
}



void Pulsos() {
  digitalWrite(E, HIGH);
  delay(500);
  digitalWrite(E, LOW);
  delay(500);
}

void Cero() {
  digitalWrite(E, LOW);
  digitalWrite(P, LOW);
  digitalWrite(V, LOW);
}

void Uno() {
  digitalWrite(P, LOW);
  digitalWrite(V, LOW);
  Pulsos();
}

void Dos() {
  digitalWrite(E, LOW);
  digitalWrite(P, HIGH);
  digitalWrite(V, LOW);
}

void Tres() {
  digitalWrite(P, HIGH);
  digitalWrite(V, LOW);
  Pulsos();
}

void Cuatro() {
  digitalWrite(E, LOW);
  digitalWrite(P, LOW);
  digitalWrite(V, HIGH);
}

void Cinco() {
  digitalWrite(P, LOW);
  digitalWrite(V, HIGH);
  Pulsos();
}

void Seis() {
  digitalWrite(E, LOW);
  digitalWrite(P, HIGH);
  digitalWrite(V, HIGH);
}

void Siete() {
  digitalWrite(P, HIGH);
  digitalWrite(V, HIGH);
  Pulsos();
}
