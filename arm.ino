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
  servo1.attach(9);
  servo2.attach(8);



  
}

void loop() {



    
 

  Take();
  delay(300);
  Place();
  delay(300); 


}

  
  void Take(){
        delay(1000);
    servo1.write(180);
    servo2.write(35);
    
    delay(2000); 
    servo1.write(165);
    servo2.write(65);
    
    delay(2000);       

    servo1.write(150);
    servo2.write(90); 

    delay(2000);
    servo1.write(160);
   
    servo2.write(100);
    servo1.write(140);
    delay(2000);
    servo1.write(160);
 
    servo2.write(120);
    servo1.write(130);
    delay(2000);



  }
  void Place(){
    delay(1000);
    servo1.write(135);
    servo2.write(65);
 
    delay(2000); 
    servo1.write(145);
    servo2.write(55);
    
    delay(2000);       

    servo1.write(155);
    servo2.write(45); 
 
    delay(2000);
    servo1.write(165);
 
    servo2.write(40);
    servo1.write(175);
    delay(2000);
    servo1.write(180);
    
    servo2.write(35);
    servo1.write(180);
    delay(2000);



  }

  
