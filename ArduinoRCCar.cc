/*
  PWS praktische opdracht. Autonome auto code van Yasin Tas uit 5Ha.
*/
//Libraries.
#include <NewPing.h>

//Variables.
int Fwd = false;
int Left = 5;
int Right = 4;
int Forwards = 3;
int Backwards = 2;
int potPin = A0;
int speed = 0;
#define TRIGGER_PIN1 11 //Front 
#define ECHO_PIN1 12
#define TRIGGER_PIN2 7 //Left
#define ECHO_PIN2 8
#define TRIGGER_PIN3  9 //Right
#define ECHO_PIN3 10
#define MAX_DISTANCE 200
#define MAX_DISTANCEF 1000

//Name of the objects.
NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCEF);//Front
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE);//Left
NewPing sonar3(TRIGGER_PIN3, ECHO_PIN3, MAX_DISTANCE);//Right

//Start of the program.
void setup() {
  Serial.begin(9600);
  pinMode(Left, OUTPUT);
  pinMode(Right, OUTPUT);
  pinMode(Forwards, OUTPUT);
  pinMode(Backwards, OUTPUT);
}

//During the program.
void loop() {
  //Value of the potentiometer
  speed = analogRead(potPin);
  speed = map(speed, 0, 1023, 0, 179);
  Serial.print(speed);

  //Sensor
  unsigned int distanceF = sonar1.ping_cm();//Front
  unsigned int distanceL = sonar2.ping_cm();//Left
  unsigned int distanceR = sonar3.ping_cm();//Right
  Serial.print(distanceF);
  Serial.print(distanceL);
  Serial.print(distanceR);
  Serial.print("cm");
  delay(50);

  //Values for driving
  int Fwd;
  if (distanceF > 50 ) {
    Fwd = true;
    Serial.print("true");
  } else {
    Fwd = false;
    Serial.print("false");
    Stp();
  }
  delay(50);
  if ((distanceF == true) && (distanceL > distanceR)) {
    fwdLeft();
  } else if ((distanceF == true) && (distanceR > distanceL)){
    fwdRight();
  }
  delay(50);
}
void fwdLeft() {
  digitalWrite(Forwards, HIGH);
  digitalWrite(Backwards, LOW);
  digitalWrite(Left, HIGH);
  digitalWrite(Right, LOW);
}
void fwdRight() {
  digitalWrite(Forwards, HIGH);
  digitalWrite(Backwards, LOW);
  digitalWrite(Left, LOW);
  digitalWrite(Right, HIGH);
}
void Stp() {
  digitalWrite(Forwards, LOW);
  digitalWrite(Backwards, LOW);
  digitalWrite(Left, LOW);
  digitalWrite(Right, LOW);
}
