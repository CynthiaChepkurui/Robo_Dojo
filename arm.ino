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
int var1 ;
int var2;
int var3;
int var4;


int var ;

void setup() {
  // Attach the Servo variable to a pin:
  servo1.attach(9);
  servo2.attach(8);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication



  
}

void loop() {
 // servo1E=servo1.read();
  //servo2E=servo2.read();

Sleep();

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
  delay(300);
  Place(); 
  
  delay(300);
  }

  else if (distance > 16 )
   {
  Serial.print("Distance: ");
  Serial.println(distance);


    Sleep();
    
    delay(300);
  }
 
 
  
  else {
    Sleep();
    
    delay(300);
  } 


}
  

    
 

 
  

}

  
  void Take(){
    servo1.write(180);
    
    
    for((var1 = 0);(var1 < 144); var1++ )
    {
      servo2.write(var1);
      delay(40);
    }

    for ((var2 = 180);(var2 > 90); var2--)
    {
      servo1.write(var2);
      delay(40);
    }




  }
  void Place(){
    delay(100);
 

    for((var4=90);(var4<180);var4++){
      servo1.write(var4);
      delay(40);
    } 


    for ((var3=144); (var3>0);var3-- )
    {
      servo2.write(var3);
      delay(40);
    }

 
    
  }
  void Sleep() {
    servo2.write(0);
    servo1.write(180);

  }

  