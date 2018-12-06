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
  Serial.begin(9600); // setting the serial monitor
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
  if (sensors[0] > 50 ) { //if the distance of the front sensor is higher than 50cm, than set Fwd true. Otherwise its false.
    Fwd = true;
    //Serial.print(Fwd);
  } else {
    Fwd = false;
    //Serial.print(Fwd);
  }
 if ((Fwd == true) && (sensors[1] > sensors[2])) { //if Fwd = true then AND left is bigger than right, then call the function. 
    fwdLeft();
  } else if ((Fwd == true) && (sensors[2] > sensors[1])){
    fwdRight();
  }
  if (Fwd == false) { //if Fwd = false, then stop driving and wait 1000ms drive back.
    stp();
    delay(1000);
    bwd();
  }
  //Serial.println(sensors[2]); 
}
//Functions to call back
void fwdLeft() {
  digitalWrite(Forwards, speed);
  digitalWrite(Backwards, LOW);
  digitalWrite(Left, HIGH);
  digitalWrite(Right, LOW);
}
void fwdRight() {
  digitalWrite(Forwards, speed);
  digitalWrite(Backwards, LOW);
  digitalWrite(Left, LOW);
  digitalWrite(Right, HIGH);
}
void stp() {
  digitalWrite(Forwards, LOW);
  digitalWrite(Backwards, LOW);
  digitalWrite(Left, LOW);
  digitalWrite(Right, LOW);
}
void bwd() {
  digitalWrite(Forwards, LOW);
  digitalWrite(Backwards, speed);
  digitalWrite(Left, LOW);
  digitalWrite(Right, LOW);
}
