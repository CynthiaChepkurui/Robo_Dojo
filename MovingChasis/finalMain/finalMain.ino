#include<Arduino.h>

/*
 * Description: Calculate the angular velocity in radians/second of a DC
motor
 * with a built-in encoder (forward = positive; reverse = negative)
 */

// Motor encoder output pulses per 360 degree revolution (measured manually=

#define ENC_COUNT_REV 361


// Encoder output to Arduino Interrupt pin. Tracks the pulse count.
#define ENC_IN_RIGHT_A 3
#define ENC_IN_LEFT_A 2

// Other encoder output to Arduino to keep track of wheel direction
// Tracks the direction of rotation.
#define ENC_IN_RIGHT_B 5
#define ENC_IN_LEFT_B 4
//Trackmapping
 int Track;
 int INXTrack;
 int INYTrack;

const int Xtrack = 60;
const int Ytrack = 60;

//IR Sensor
// Define the digital input pins connected to the sensor outputs
const int sensorPins[] = {30, 31, 33, 32, 34};

//Ultra sonic
const int trigPin1 = 26;
const int echoPin1 = 25;
const int trigPin2 =36;
const int echoPin2 = 38;

int Stage;
long duration1;
float distance1;
long duration2;
float distance2;
int var;
// Motor right connections
int enA = 6;
int in1 = 7;
int in2 = 8;

// Motor left connections
int enB = 11;
int in3 = 9;
int in4 = 10;

// True = Forward; False = Reverse
boolean Direction_right = true;
boolean Direction_left = true;

// Keep track of the number of right and left wheel pulses
volatile long right_wheel_pulse_count = 0;
volatile long left_wheel_pulse_count = 0;

// One-second interval for measurements
int interval = 1000;

// Counters for milliseconds during interval
long previousMillis = 0;
long currentMillis = 0;

// Variable for RPM measurement
float rpm_right = 0;
float rpm_left = 0;

// Variable for angular velocity measurement
float ang_velocity_right = 0;
float ang_velocity_right_deg = 0;

float ang_velocity_left = 0;
float ang_velocity_left_deg = 0;

const float rpm_to_radians = 0.10471975512;
const float rad_to_deg = 57.29578;

void right_wheel_pulse();
void left_wheel_pulse();

void ForwardDirectionControl();
void ReverseDirectionControl();
void TurnRightControl();
void TurnLeftControl();
void StopMotors();

void setup() {

  // Open the serial port at 9600 bps
  Serial.begin(9600);
   //ultrasonic setup
  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin2, INPUT); // Sets the echoPin as an Input
   //IR sensor setup
  pinMode(sensorPins[0], INPUT);
  pinMode(sensorPins[1], INPUT);
  pinMode(sensorPins[2], INPUT);
  pinMode(sensorPins[3], INPUT);
  pinMode(sensorPins[4], INPUT);

    //motorsetup
    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);


  // Turn off motors - Initial state
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);

  // Set pin states of the encoder
  pinMode(ENC_IN_RIGHT_A , INPUT_PULLUP);
  pinMode(ENC_IN_RIGHT_B , INPUT);

  pinMode(ENC_IN_LEFT_A , INPUT_PULLUP);
  pinMode(ENC_IN_LEFT_B , INPUT);

  // Every time the pin goes high, this is a pulse
  attachInterrupt(digitalPinToInterrupt(ENC_IN_RIGHT_A), right_wheel_pulse,
RISING);
  attachInterrupt(digitalPinToInterrupt(ENC_IN_LEFT_A), left_wheel_pulse,
RISING);

}

void loop() {

    // Record the time
    currentMillis = millis();
    while (var < 4){
  
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
   digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  


  
      if (currentMillis - previousMillis > interval) {

      previousMillis = currentMillis;

      // Calculate revolutions per minute for right wheel
      rpm_right = (float)(right_wheel_pulse_count * 60 / ENC_COUNT_REV);
      ang_velocity_right = rpm_right * rpm_to_radians;
      ang_velocity_right_deg = ang_velocity_right * rad_to_deg;

      // Calculate revolutions per minute for left wheel
      rpm_left = (float)(left_wheel_pulse_count * 60 / ENC_COUNT_REV);
      ang_velocity_left = rpm_left * rpm_to_radians;
      ang_velocity_left_deg = ang_velocity_left * rad_to_deg;


      right_wheel_pulse_count = 0;
      left_wheel_pulse_count = 0;
    }
  // duration = pulseIn(echoPin, HIGH);
  distance1 = duration1 * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance1);
  distance2 = duration2 * 0.034 / 2;
  Serial.print("  ");
  Serial.print(distance2);
  //delay(20);
 
 // else if (()or())
    // if (distance1 = 0 or distance1 <10)
  
   /* Serial.print(" Pulses: ");
      Serial.println(right_wheel_pulse_count);
      Serial.print(" Speed: ");
      Serial.print(rpm_right);
      Serial.println(" RPM");
      Serial.print(" Angular Velocity: ");
      Serial.print(rpm_right);
      Serial.print(" rad per second");
      Serial.print("\t");
      Serial.print(ang_velocity_right_deg);
      Serial.println(" deg per second");
      Serial.println();
      Serial.println();
      Serial.println();

      Serial.print(" Pulses: ");
      Serial.println(left_wheel_pulse_count);
      Serial.print(" Speed: ");
      Serial.print(rpm_left);
      Serial.println(" RPM");
      Serial.print(" Angular Velocity: ");
      Serial.print(rpm_left);
      Serial.print(" rad per second");
      Serial.print("\t");
      Serial.print(ang_velocity_left_deg);
      Serial.println(" deg per second");
      Serial.println();
      Serial.println();
      Serial.println();*/
  linefollowing();
  Serial.print("Distance Ultra one: ");
  Serial.println(distance1);
  Serial.print("   Two ");
  Serial.print(distance2);
  
  /*StageOne();
  
  StageTwo();
  delay(500);
  StageThree();
  StageFour();
  StageFive();*/






    // If one second has passed, print the number of pulses


    }
}


void StartForwardDirection(){
    analogWrite(enB, 80);
    analogWrite(enA, 59);

    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    //delay(50);
}
void SmallLeftTurn(){
  analogWrite(enB, 0);
  analogWrite(enA, 60);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH );
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  //delay(40);
}
void MidLeftTurn(){
  analogWrite(enB, 0);
  analogWrite(enA, 80);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH );
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  //delay(50);
}

void TurnLeftControl()
{
  analogWrite(enB, 0);
  analogWrite(enA, 100);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH );
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
 // delay(100);

}
void MainFuction(){}//moving to objects
void StartReturnDirection(){}
void SmallRightTurn(){
  analogWrite(enB, 60);
  analogWrite(enA, 0);

  digitalWrite(in1, HIGH );
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
 // delay(100);
}
void MidRightTurn(){
  analogWrite(enB, 80);
  analogWrite(enA, 0);

  digitalWrite(in1, HIGH );
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  //delay(100);
}
// This function lets you control spinning direction of motors
void ForwardDirectionControl() {
  // Set motors to maximum speed
  // For PWM maximum possible values are 0 to 255
    analogWrite(enB, 85);
    analogWrite(enA, 69);

    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    //delay(500);

}


// Increment the number of pulses of right wheel by 1
void right_wheel_pulse() {

  // Read the value for the encoder for the right wheel
  int valRight = digitalRead(ENC_IN_RIGHT_B);

  if(valRight == LOW) {
    Direction_right = false; // Reverse
  }
  else {
    Direction_right = true; // Forward
  }

  if (Direction_right) {
    right_wheel_pulse_count++;
  }
  else {
    right_wheel_pulse_count--;
  }
}

// Increment the number of pulses of left wheel by 1
void left_wheel_pulse() {
  // Read the value for the encoder for the right wheel
  int valLeft = digitalRead(ENC_IN_LEFT_B);

  if(valLeft == LOW) {
    Direction_left = false; // Reverse
  }
  else {
    Direction_left = true; // Forward
  }

  if (Direction_left) {
    left_wheel_pulse_count++;
  }
  else {
    left_wheel_pulse_count--;
  }
}
void R360T(){
  analogWrite(enB, 250);
  analogWrite(enA, 0);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(400);

}
void ReverseDirectionControl()
{
  analogWrite(enB, 100);
  analogWrite(enA, 79);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  //delay(100);
}
void TurnRightControl()
{
  analogWrite(enB, 100);
  analogWrite(enA, 0);

  digitalWrite(in1, HIGH );
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  //Delay(100);

}

void StopMotors()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void StageOne(){
   if (distance2 > 284 ){
    Stage+=1;
    linefollowing();
    delay(150);}    
  else{
    TurnRightControl();
  }}
void StageTwo(){
  Stage+=1;
  if (distance2 >160){
     linefollowing();
     delay(150);}    
  else{
    TurnLeftControl(); }    
 }
void StageThree(){
   if (distance2 > 120 ) {
    Stage+=1;
    linefollowing();}    
  else{
    TurnRightControl();
  }}
   void StageFour(){
   if (distance2 > 50 ) {
    Stage+=1;
     linefollowing(); }   
  else{
    TurnRightControl(); }}
void StageFive(){
  if (distance2 > 20 ) {
    Stage+=1;
     linefollowing(); }   
  else{
    StopMotors(); }}
void StageSix(){
  if (distance2 > 30 ) {
    Stage+=1;
     linefollowing();}    
  else{
    R360T(); }}


void linefollowing(){
    // Read the state of each sensor and print the results
  int sensorValue0 = digitalRead(sensorPins[0]);
  int sensorValue1 = digitalRead(sensorPins[1]);
  int sensorValue2 = digitalRead(sensorPins[2]);
  int sensorValue3 = digitalRead(sensorPins[3]);
  int sensorValue4 = digitalRead(sensorPins[4]);
 /* Serial.print("Sensor Values : ");
  Serial.print(sensorValue0);
 // Serial.print(" : ");
  //Serial.print(sensorValue1);
  Serial.print(" : ");
  Serial.print(sensorValue2);
  Serial.print(" : ");
  Serial.print(sensorValue3);
  Serial.print(" : ");
  Serial.print(sensorValue4);
  //Serial.print(); // Separate each reading with a line break
  Serial.println();*/

  if ((sensorValue0 == 0) && (sensorValue2 == 0) && (sensorValue3 == 0) && (sensorValue4 == 0) ) {
    // Serial.print("Drive straight.");
    ForwardDirectionControl();
    //if ((currentMillis - 250) ==0){
    //  TurnRightControl();
    
  }
  else if ((sensorValue0==0)&&(sensorValue2== 0) &&(sensorValue3 ==0) && (sensorValue4 == 1)){
    TurnRightControl();

  }
   else if (((sensorValue0==0  && sensorValue2== 0) &&(sensorValue3 ==1) && (sensorValue4 == 1)) or ((sensorValue0==0 &&sensorValue2== 1) &&(sensorValue3 ==1) && (sensorValue4 == 1))){
    MidRightTurn();

  }
  else if ((sensorValue0==0  && sensorValue2== 1) &&(sensorValue3 ==1) && (sensorValue4 == 1)) {
    // Serial.print("Turn Right.");
    SmallRightTurn();
  }
      else if ((sensorValue0==1) &&  (sensorValue2== 0) &&(sensorValue3 ==0) && (sensorValue4 == 0)){
    TurnLeftControl();

  }
    else if (((sensorValue0==1 && sensorValue2== 1) &&(sensorValue3 ==0) && (sensorValue4 == 0)) or ((sensorValue0==1  && sensorValue2== 1) &&(sensorValue3 ==0) && (sensorValue4 == 0))){
    MidLeftTurn();

  }
 
    else if  ((sensorValue0==1  && sensorValue2== 1) &&(sensorValue3 ==1) && (sensorValue4 ==0)) {
    // Serial.print("Turn Left.");
    SmallLeftTurn();
  } 
    else if (((sensorValue0 == 0) && (sensorValue4 == 0)) or ((sensorValue0==0)  && (sensorValue2== 1) &&(sensorValue3 ==1) && (sensorValue4 == 0))) {
    // Serial.print("Drive straight.");
    ForwardDirectionControl();
      }
    
}



