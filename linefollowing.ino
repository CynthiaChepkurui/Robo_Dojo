/*
    This is the run code for the line follower.

    For instructions, please click the link below.
    for more clarification
    https://brisbaneinvestment.club/line-follower-robot-build-a-line-follower-for-less-than-20/

*/

// Motor A - Left Motor
#define MCenA 13
#define MCin1 11
#define MCin2 12

// Motor B - Right Motor
#define MCenB 8
#define MCin3 9
#define MCin4 10

// Set inital speed for Motors
int motorSpeedA = 0;
int motorSpeedB = 0;

// Initialise light sensors

int in1 = 3;
int in2 = 4;
int in3 = 5;
int in4 = 6;
int in5 = 7;

int s1 = 0;
int s2 = 0;
int s3 = 0;
int s4 = 0;
int s5 = 0;

void setup() {
  // Open serial connection to display values in Monitor if connected
  Serial.begin(9600);
  Serial.println("Light sensor test");

  // Initialize the Arduino ports for the Motor Controller
  pinMode(MCenA, OUTPUT);
  pinMode(MCenB, OUTPUT);
  pinMode(MCin1, OUTPUT);
  pinMode(MCin2, OUTPUT);
  pinMode(MCin3, OUTPUT);
  pinMode(MCin4, OUTPUT);

  // Initialise sensor inputs:
  pinMode(in1,INPUT);
  pinMode(in2,INPUT);
  pinMode(in3,INPUT);
  pinMode(in4,INPUT);
  pinMode(in5,INPUT);
  
}
void loop() {

  // Read each light sensor
  s1 = digitalRead(in1);
  s2 = digitalRead(in2);
  s3 = digitalRead(in3);
  s4 = digitalRead(in4);
  s5 = digitalRead(in5);

  Serial.print("Sensors");
  Serial.print("\t");
  Serial.print(s1);
  Serial.print("\t");
  Serial.print(s2);
  Serial.print("\t");
  Serial.print(s3);
  Serial.print("\t");
  Serial.print(s4);
  Serial.print("\t");
  Serial.print(s5);
  Serial.print("\t");

  // Depending on Joystick values, drive the vehicle.
  
  // Y-axis used for forward and backward control. (0 = UP, 512 = MID, 1023 = DOWN)

  // Set Motor A forward by default
  digitalWrite(MCin1, LOW);
  digitalWrite(MCin2, HIGH);
  // Set Motor B forward by default
  digitalWrite(MCin3, LOW);
  digitalWrite(MCin4, HIGH);

  // END OF MANUAL INPUT FROM JOYSTICK
  
  // START OF AUTONOMOUS CODE

  if ((s2 == 1) && (s4 == 1)) {
    // Serial.print("Drive straight.");
    DriveStraight();
  }
  else if ((s2 == 0) && (s4 == 1)) {
    // Serial.print("Turn Right.");
    TurnRight();
  }
  else if ((s2 == 1) && (s4 == 0)) {
    // Serial.print("Turn Left.");
    TurnLeft();
  }
  else if ((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0)) {
    // Serial.print("Drive straight.");
    DriveStraight();
  }
  else {
    // Serial.print("STOP.");
    Stop();
  }

  delay(10);

  motorSpeedA = 0;
  motorSpeedB = 0;
  
  // Send motor speeds to motor
  analogWrite(MCenA, motorSpeedA); // Send PWM signal to motor A
  analogWrite(MCenB, motorSpeedB); // Send PWM signal to motor B

  delay(10);
  
}

void DriveStraight() {
  Serial.print("Drive straight (IN LOOP.)");

  // Set motor speeds
  motorSpeedA = 150;
  motorSpeedB = 150;

  // Print motor speed to montor.
  Serial.print("Motor Speeds.");
  Serial.print("\t");
  Serial.print(motorSpeedA);
  Serial.print("\t");
  Serial.println(motorSpeedB);

  // Send motor speeds to motor
  analogWrite(MCenA, motorSpeedA); // Send PWM signal to motor A
  analogWrite(MCenB, motorSpeedB); // Send PWM signal to motor B
}

void TurnRight() {
  Serial.print("Turn Right (IN LOOP.)");

  // Set motor speeds
  motorSpeedA = 0;
  motorSpeedB = 150;

  // Print motor speed to montor.
  Serial.print("Motor Speeds.");
  Serial.print("\t");
  Serial.print(motorSpeedA);
  Serial.print("\t");
  Serial.println(motorSpeedB);

  // Send motor speeds to motor
  analogWrite(MCenA, motorSpeedA); // Send PWM signal to motor A
  analogWrite(MCenB, motorSpeedB); // Send PWM signal to motor B
}

void TurnLeft() {
  Serial.print("Turn Left (IN LOOP.)");

  // Set motor speeds
  motorSpeedA = 150;
  motorSpeedB = 0;

  // Print motor speed to montor.
  Serial.print("Motor Speeds.");
  Serial.print("\t");
  Serial.print(motorSpeedA);
  Serial.print("\t");
  Serial.println(motorSpeedB);

  // Send motor speeds to motor
  analogWrite(MCenA, motorSpeedA); // Send PWM signal to motor A
  analogWrite(MCenB, motorSpeedB); // Send PWM signal to motor B
}

void Stop() {
  Serial.print("Stop (IN LOOP.)");
  
  // Set motor speeds
  motorSpeedA = 0;
  motorSpeedB = 0;

  // Print motor speed to montor.
  Serial.print("Motor Speeds.");
  Serial.print("\t");
  Serial.print(motorSpeedA);
  Serial.print("\t");
  Serial.println(motorSpeedB);
  
  // Send motor speeds to motor
  analogWrite(MCenA, motorSpeedA); // Send PWM signal to motor A
  analogWrite(MCenB, motorSpeedB); // Send PWM signal to motor B
}