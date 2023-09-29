/* Servo motor with Arduino example code. Position and sweep. More info: https://www.makerguides.com/ */

// Include the servo library:
#include <Servo.h>

// Create a new servo object:
Servo servo1;
Servo servo2;

// Define the servo pin:
const int trigPin = 10;
const int echoPin = 11;
long duration;
float distance;
int servo1E ;
int servo2E ;
int var = 0;

int i = 0;

void setup() {
  // Attach the Servo variable to a pin:
  servo1.attach(9);
  servo2.attach(8);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication



  
}

void loop() {
  servo1E=servo1.read();
  servo2E=servo2.read();



  // Print the distance to the serial monitor
while (var < 10){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  // duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(200);
   if (distance =0 or distance <16)
  {
  Serial.print("Distance: ");
  Serial.println(distance);
 
  Take();
  delay(3000);
  Place(); 
  
  delay(3000);
  }

  else if (distance > 16 )
   {
  Serial.print("Distance: ");
  Serial.println(distance);


    Sleep();
    
    delay(3000);
  }
 
 
  
  else {
    Sleep();
    
    delay(3000);
  } 


}
  

    
 

 
  

}

  
  void Take(){
        delay(300);
    servo1.write(180);
    servo2.write(35);
    
    //delay(300); 
    servo1.write(175);
    servo2.write(40);
      //delay(300); 
    servo1.write(165);
    servo2.write(45);
   //   delay(300); 
    servo1.write(160);
    servo2.write(55);
    //  delay(300); 
    servo1.write(155);
    servo2.write(75);
    
    //delay(200);       

    servo1.write(150);
    servo2.write(90); 

    delay(200);
    servo1.write(160);
   
    servo2.write(100);
    servo1.write(140);
    delay(200);
    servo1.write(160);
 
    servo2.write(120);
    servo1.write(130);
    delay(200);



  }
  void Place(){
    delay(100);
    servo1.write(135);
    servo2.write(65);
 
    delay(200); 
    servo1.write(145);
    servo2.write(55);
    
    delay(200);       

    servo1.write(155);
    servo2.write(45); 
 
    delay(200);
    servo1.write(165);
 
    servo2.write(40);
    servo1.write(175);
    delay(200);
    servo1.write(180);
    
    servo2.write(35);
    servo1.write(180);
    delay(200);



  }
  void Sleep() {
    servo2.write(35);
    servo1.write(180);

  }

  