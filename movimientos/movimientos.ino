

//-- Configuration of pins where the servos are attached
/*
         --------------- 
        |               |
        |     O   O     |
        |               |
 YR ==> |               | <== YL
         --------------- 
            ||     ||
            ||     ||
            ||     ||
 RR ==>  ------   ------  <== RL
         ------   ------
*/

  #include <Servo.h>
 
  #define PIN_YL 2 //servo[0]
  #define PIN_YR 3 //servo[1]
  #define PIN_RL 4 //servo[2]
  #define PIN_RR 5 //servo[3]

///////////////////////////////////////////////////////////////////
//-- Global Variables -------------------------------------------//
///////////////////////////////////////////////////////////////////

Servo YL, YR, RL, RR;

/*-- Zowi has 5 modes:
//--    * MODE = 0: Zowi is awaiting  
//--    * MODE = 1: Dancing mode!  
//--    * MODE = 2: Obstacle detector mode  
//--    * MODE = 3: Noise detector mode   
//--    * MODE = 4: ZowiPAD or any Teleoperation mode (listening SerialPort). 
*/

void setup() {

  Serial.begin(9600);
  YL.attach(PIN_YL);
  YR.attach(PIN_YR);
  RL.attach(PIN_RL);
  RR.attach(PIN_RR);
}

int data = 0;
void loop() {

  if(Serial.available()>0){
    data = Serial.parseInt();
    
  }

  YL.write(data);

}
