#include <Encoder.h>

// Define the pins connected to the L298N two motor driver 
int enaPin1 = 2;  // Enable pin for Motor 1
int in1Pin1 = 3;  // IN1 pin for Motor 1
int in2Pin1 = 4;  // IN2 pin for Motor 1

int enaPin2 = 7;  // Enable pin for Motor 2
int in1Pin2 = 5;   // IN3 pin for Motor 2
int in2Pin2 = 6;   // IN4 pin for Motor 2
int var;

// Define the pins connected to the encoders
Encoder encoder1(A0, A1);  // Encoder for Motor 1 (A and B pins connected to A0 and A1)
Encoder encoder2(A2, A3);  // Encoder for Motor 2 (A and B pins connected to A2 and A3)
// Defining ultrasonic sensors

const int   RtrigPin = 10;
const int RechoPin = 11;
//const int   LtrigPin = 12;
//const int LechoPin = 13;

long Rduration;
float Rdistance;
//long Lduration;
//float Ldistance;
void setup() {
  //Setting the Ultrasonic sensors
  pinMode(RtrigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(RechoPin, INPUT); // Sets the echoPin as an Input
  //pinMode(LtrigPin, OUTPUT); // Sets the trigPin as an Output
  //pinMode(LechoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
  // Set motor control pins as OUTPUT
  pinMode(enaPin1, OUTPUT);
  pinMode(in1Pin1, OUTPUT);
  pinMode(in2Pin1, OUTPUT);

  pinMode(enaPin2, OUTPUT);
  pinMode(in1Pin2, OUTPUT);
  pinMode(in2Pin2, OUTPUT);

  // Initialize both motors to be stopped (speed = 0)
  digitalWrite(enaPin1, LOW);
  digitalWrite(in1Pin1, LOW);
  digitalWrite(in2Pin1, LOW);

  digitalWrite(enaPin2, LOW);
  digitalWrite(in1Pin2, LOW);
  digitalWrite(in2Pin2, LOW);

  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Read encoder values
  long encoder1Value = encoder1.read();
  long encoder2Value = encoder2.read();

  while(var < 10){
  digitalWrite(RtrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(RtrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(RtrigPin, LOW);
  Rduration = pulseIn(RechoPin, HIGH);
  /*digitalWrite(LtrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(LtrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(LtrigPin, LOW);
  Lduration = pulseIn(echoPin, HIGH); */
  // duration = pulseIn(echoPin, HIGH);
  Rdistance = Rduration * 0.034 / 2;
  //Ldistance = Lduration * 0.034 / 2;
  Serial.print("Right Distance: ");
  Serial.println(Rdistance);
  //Serial.print("Left Distance: ");
  //Serial.println(ldistance);
  // Calculate desired motor speed based on encoder values (you can adjust this logic)
  int motorSpeed1 = map(50, 0, 1000, 50, 1255); // Adjust the mapping as needed
  int motorSpeed2 = map(100, 0, 1000, 50, 1255); // Adjust the mapping as needed
  int RmotorSpeedStop = map(0, 0, 1000, 0,255);
  int LmotorSpeedStop =map(0, 0, 1000, 0, 255);
  if ((Rdistance <=20) /*and(Ldistance <=10)*/ ){
      // Motor 1: Set the motor direction and speed
 
    digitalWrite(in1Pin1, HIGH); // Set the motor direction (forward)
    digitalWrite(in2Pin1, LOW);
    analogWrite(enaPin1, RmotorSpeedStop); // Set the motor speed
    digitalWrite(in1Pin2, HIGH); // Set the motor direction (forward)
    digitalWrite(in2Pin2, LOW);
    analogWrite(enaPin2, LmotorSpeedStop); // Set the motor speed



  }
  else if ((Rdistance >20) /* and(Ldistance > 10) */) {
    
  // Motor 1: Set the motor direction and speed
  if (motorSpeed1 > 0) {
    digitalWrite(in1Pin1, HIGH); // Set the motor direction (forward)
    digitalWrite(in2Pin1, LOW);
    analogWrite(enaPin1, motorSpeed1); // Set the motor speed
  } else {
    // Reverse direction if motorSpeed1 is negative
    digitalWrite(in1Pin1, LOW);
    digitalWrite(in2Pin1, HIGH);
    analogWrite(enaPin1, -motorSpeed1); // Set the motor speed (absolute value)
  }


  // Motor 2: Set the motor direction and speed
  if (motorSpeed2 > 0) {
    digitalWrite(in1Pin2, HIGH); // Set the motor direction (forward)
    digitalWrite(in2Pin2, LOW);
    analogWrite(enaPin2, motorSpeed2); // Set the motor speed
  } else {
    // Reverse direction if motorSpeed2 is negative
    digitalWrite(in1Pin2, LOW);
    digitalWrite(in2Pin2, HIGH);
    analogWrite(enaPin2, -motorSpeed2); // Set the motor speed (absolute value)
  }
  }
  // Print encoder values for debugging
  Serial.print("Encoder 1: ");
  Serial.print(encoder1Value);
  Serial.print("   Encoder 2: ");
  Serial.println(encoder2Value);
  delay(200);
  
  }

  // Add a delay or control logic here as required
  delay(100); // Adjust the delay as needed
}

void moveCircle(){

}
