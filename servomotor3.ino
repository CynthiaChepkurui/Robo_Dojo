#include <Servo.h>

Servo servo1;
Servo servo2;

const int trigPin = 10;
const int echoPin = 11;
long duration;
float distance;
int var1;
int var2;
int var3;
int var4;
int var;

void setup() {
  servo1.attach(9);
  servo2.attach(8);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  Sleep();

  while (var < 10) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    Serial.print("Distance: ");
    Serial.println(distance);
    delay(200);
    if (distance == 0 || distance < 16) {
      Serial.print("Distance: ");
      Serial.println(distance);
      Take();
      delay(300);
      Place();
      delay(300);
    } else if (distance > 16) {
      Serial.print("Distance: ");
      Serial.println(distance);
      Sleep();
      delay(300);
    } else {
      Sleep();
      delay(300);
    }
  }
}

void Take() {
  servo1.write(180);

  for (var1 = 0; var1 < 144; var1++) {
    servo2.write(var1);
    delay(40);
  }

  for (var2 = 180; var2 > 90; var2--) {
    servo1.write(var2);
    delay(40);
  }
}

void Place() {
  delay(100);

  for (var4 = 90; var4 < 180; var4++) {
    servo1.write(var4);
    delay(40);
  }

  for (var3 = 144; var3 > 0; var3--) {
    servo2.write(var3);
    delay(40);
  }
}

void Sleep() {
  // Gradually move servo2 to 0 degrees
  for (int pos = servo2.read(); pos >= 0; pos--) {
    servo2.write(pos);
    delay(10);
  }

  // Gradually move servo1 to 180 degrees
  for (int pos = servo1.read(); pos <= 180; pos++) {
    servo1.write(pos);
    delay(10);
  }
}
