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
const int Xtrack = 60;
const int Ytrack = 60;

//IR Sensor
// Define the digital input pins connected to the sensor outputs
const int sensorPins[] = {2, 3, 4, 5, 6};

//Ultra sonic
const int trigPin = 26;
const int echoPin = 25;
long duration;
float distance;
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
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
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
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  // Read the state of each sensor and print the results
  int sensorValue0 = digitalRead(sensorPins[0]);
  int sensorValue1 = digitalRead(sensorPins[1]);
  int sensorValue2 = digitalRead(sensorPins[2]);
  int sensorValue3 = digitalRead(sensorPins[3]);
  int sensorValue4 = digitalRead(sensorPins[4]);

  
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
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(20);
     if (distance = 0 or distance <33)
  {
    Serial.print(" Pulses: ");
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
      Serial.println();

  Serial.print("Distance: ");
  Serial.println(distance);

  Serial.print("Sensor Values : ");
  Serial.print(sensorValue0);
  Serial.print(" : ");
  Serial.print(sensorValue1);
  Serial.print(" : ");
  Serial.print(sensorValue2);
  Serial.print(" : ");
  Serial.print(sensorValue3);
  Serial.print(" : ");
  Serial.print(sensorValue4);
  //Serial.print(); // Separate each reading with a line break
  Serial.println();

  StopMotors();
  delay(500);
  ReverseDirectionControl();
  delay(700);
  TurnLeftControl();
  delay(700);
  ForwardDirectionControl();


  }
  else{
    ForwardDirectionControl();
  }

    // If one second has passed, print the number of pulses


    }

}
void StartForwardDirection(){
    analogWrite(enB, 100);
    analogWrite(enA, 79);

    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(50);
}
void SmallLeftTurn(){
  analogWrite(enB, 0);
  analogWrite(enA, 60);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH );
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(40);
}
void MidLeftTurn(){
  analogWrite(enB, 0);
  analogWrite(enA, 80);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH );
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(50);
}

void TurnLeftControl()
{
  analogWrite(enB, 0);
  analogWrite(enA, 100);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH );
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(100);

}
void MainFuction(){}//moving to objects
void StartReturnDirection(){}
void SmallRightTurn(){}
void MidRightTurn(){}
// This function lets you control spinning direction of motors
void ForwardDirectionControl() {
  // Set motors to maximum speed
  // For PWM maximum possible values are 0 to 255
    analogWrite(enB, 100);
    analogWrite(enA, 79);

    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(500);

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

void ReverseDirectionControl()
{
  analogWrite(enB, 100);
  analogWrite(enA, 79);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(100);
}
void TurnRightControl()
{
  analogWrite(enB, 50);
  analogWrite(enA, 0);

  digitalWrite(in1, HIGH );
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(100);

}

void StopMotors()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}


