//Libraries.
#include <NewPing.h>

//Variables.
bool Fwd;
int Left = 5;
int Right = 4;
int Forwards = 3;
int Backwards = 2;
int const potPin = A0;
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

long sensors[3]; //Makesalist of the sensor values and stores them in there so it can recall it back
//Start of the program.
void setup() {
  Serial.begin(9600);
  pinMode(Left, OUTPUT); //setting the output of the pins
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
  speed = analogRead(potPin); //reads the values of the pot meter. Sends off a signal of it
  speed = map(speed, 0, 1023, 0, 179);

  //Values for driving
  if (sensors[0] >= 50 ) { //if the distance of the front sensor is higher than 50cm, than set Fwd true. Otherwise its false.
    Fwd = true;
    //Serial.print(Fwd);
  } else {
    Fwd = false;
    //Serial.print(Fwd);
  }
  delay(50);
  if (Fwd == true){ //If Fwd = true then the next line of code will be scrolled through.
    if (sensors[1] < 50){ //Fwd = true, but if left sensor is < 50cm then go right.
      fwdRight();
    } else if (sensors[2] < 50){//If right sensor < 50 then go left.
      fwdLeft();
    } else {//if none of the condidtions for Fwd = true is met keep going forward
      fwd();
    }
  }
    if (Fwd == false) {//If Fwd = false then call this If statement
      if (sensors[1] < 50){//Same as above except backwards
        bwdLeft();
      } else if (sensors[2] < 50){
        bwdRight();
      } else if ((sensors[1] < 50) && (sensors[2] < 50)){//If both sensors get obscured come to a full stop
        stp();
      } else {//If none of the condidtions are met then go back, wait, backleft, wait, backright
        bwd();
        delay(1000);
        bwdLeft();
        delay(500);
        bwdRight();
        delay(50);
      }
    }
  //Serial.println(sensors[2]);
}
//Functions to call back
void fwd() {  //Forwards
  digitalWrite(Forwards, speed);
  digitalWrite(Backwards, LOW);
  digitalWrite(Left, LOW);
  digitalWrite(Right, LOW);
}
void fwdLeft() { //Forward Left
  digitalWrite(Forwards, speed);
  digitalWrite(Backwards, LOW);
  digitalWrite(Left, HIGH);
  digitalWrite(Right, LOW);
}
void fwdRight() { //Forward right
  digitalWrite(Forwards, speed);
  digitalWrite(Backwards, LOW);
  digitalWrite(Left, LOW);
  digitalWrite(Right, HIGH);
}
void bwd() { //Backwards
  digitalWrite(Forwards, LOW);
  digitalWrite(Backwards, speed);
  digitalWrite(Left, LOW);
  digitalWrite(Right, LOW);
}
void bwdLeft() { //Backwards left
  digitalWrite(Forwards, LOW);
  digitalWrite(Backwards, speed);
  digitalWrite(Left, HIGH);
  digitalWrite(Right, LOW);
}
void bwdRight() { //Backwards right
  digitalWrite(Forwards, LOW);
  digitalWrite(Backwards, speed);
  digitalWrite(Left, LOW);
  digitalWrite(Right, HIGH);
}
void stp() { //Full stop
  digitalWrite(Forwards, LOW);
  digitalWrite(Backwards, LOW);
  digitalWrite(Left, LOW);
  digitalWrite(Right, LOW);
}
