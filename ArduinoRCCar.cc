//Libraries.
#include <NewPing.h>

//Variables.
bool Fwd;
int Left = 5;
int Right = 4;
int Forwards = 3;
int Backwards = 2;
int potPin = A0;
int speed = 0;
#define SONAR_NUM 3
#define TRIGGER_PIN1 11 //Front 
#define ECHO_PIN1 12
#define TRIGGER_PIN2 7 //Left
#define ECHO_PIN2 8
#define TRIGGER_PIN3  9 //Right
#define ECHO_PIN3 10
#define MAX_DISTANCE 200

//Name of the objects.
NewPing sonar[SONAR_NUM] = {
  NewPing(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE),
  NewPing(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE),
  NewPing(TRIGGER_PIN3, ECHO_PIN3, MAX_DISTANCE)
};

long sensors[3];
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
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through each sensor and display results.
    delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    sensors[i] = sonar[i].ping_cm(); 
  }

  //Value of the potentiometer
  speed = analogRead(potPin);
  speed = map(speed, 0, 1023, 0, 179);

  //Values for driving
  if (sensors[0] > 20 ) {
    Fwd = true;
    //Serial.print(Fwd);
  } else {
    Fwd = false;
    //Serial.print(Fwd);
  }
  delay(50);
 if ((Fwd == true) && (sensors[1] > sensors[2])) {
    fwdLeft();
  } else if ((Fwd == true) && (sensors[2] > sensors[1])){
    fwdRight();
  }
  delay(50);
  if (Fwd == false) {
    bwd();
  }
  Serial.println(sensors[2]);
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
void bwd() {
  digitalWrite(Forwards, LOW);
  digitalWrite(Backwards, HIGH);
  digitalWrite(Left, LOW);
  digitalWrite(Right, LOW);
}

