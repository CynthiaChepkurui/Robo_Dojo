/* Servo motor with Arduino example code. Position and sweep. More info: https://www.makerguides.com/ */

// Include the servo library:
#include <Servo.h>

// Create a new servo object:
Servo servo1;
Servo servo2;
// Define the servo pin:

int i = 0;

void setup() {
  // Attach the Servo variable to a pin:
  servo1.attach(8);
  servo2.attach(7);
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  
}

void loop() {
    servo1.write(0);
    digitalWrite(13,HIGH);
    digitalWrite(12,HIGH);  
    delay(200);
    digitalWrite(13,LOW);
    digitalWrite(12,LOW);    
    delay(2000);        

    servo2.write(180); 
    digitalWrite(11,HIGH);
    digitalWrite(10,HIGH);  
    delay(200);
    digitalWrite(11,LOW);
    digitalWrite(10,LOW);    
    delay(2000); 

    
 

  Take();
  delay(300);
  Place();
  delay(300); 
}

void moveUp1(){
     for (i = 0; i < 45; i++) { 

    digitalWrite(13,HIGH);
    servo1.write(i);    
    delay(10);
    digitalWrite(13,LOW);
     }  
}
void moveUp2(){
     for (i = 45; i < 90; i++) { 

    digitalWrite(13,HIGH);
    servo1.write(i);    
    delay(10);
    digitalWrite(13,LOW);
     }                    

  }
void moveUp3(){
     for (i = 90; i < 135; i++) { 

    digitalWrite(13,HIGH);
    servo1.write(i);    
    delay(10);
    digitalWrite(13,LOW);
     }
}
void moveDown(){
     for (i = 45; i>0 ; i--) { 

    digitalWrite(12,HIGH);
    servo1.write(i);    
    delay(10);
    digitalWrite(12,LOW); 
     }                     

  }
    void moveForward(){
     for (i = 180; i < 135; i++) { 

    digitalWrite(11,HIGH);
    servo2.write(i);    
    delay(10);
    digitalWrite(11,LOW);                      
  }
  }
    void moveBackwards (){
     for (i = 45; i>0 ; i--) { 

    digitalWrite(10,HIGH);
    servo2.write(i);    
    delay(10);
    digitalWrite(10,LOW);                      
  }
  }
  void Take(){
    moveUp1();
    moveForward();
    moveUp2();
    moveUp3();
    moveForward();
    moveDown();
    moveDown();
  }
  void Place(){
    moveBackwards();
    moveBackwards();
    moveDown();
    moveBackwards();

  }

  
