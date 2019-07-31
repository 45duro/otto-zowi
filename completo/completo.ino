
#include <Servo.h> 
#include <Oscillator.h>
#include <BatReader.h>
#include <US.h>
#include "LedControl.h"
#include <HCSR04.h>

LedControl lc=LedControl(12,10,11,1);
UltraSonicDistanceSensor distanceSensor(7, 6);  // Initialize sensor that uses digital pins 13 and 12.

//-- Zowi Library
#include <Zowi.h>
Zowi zowi;  //This is Zowi!!
 
//---------------------------------------------------------
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
 RR ==>   -----   ------  <== RL
          -----   ------
*/

  #define PIN_YL 2 //servo[0]
  #define PIN_YR 3 //servo[1]
  #define PIN_RL 4 //servo[2]
  #define PIN_RR 5 //servo[3]
//---------------------------------------------------------



///////////////////////////////////////////////////////////////////
//-- Global Variables -------------------------------------------//
///////////////////////////////////////////////////////////////////


//-- Movement parameters
unsigned long delaytime=2000;
int T=1000;              //Initial duration of movement
int moveId=0;            //Number of movement
int moveSize=15;         //Asociated with the height of some movements

//---------------------------------------------------------
//-- Zowi has 5 modes:
//--    * MODE = 0: Zowi is awaiting  
//--    * MODE = 1: Dancing mode!  
//--    * MODE = 2: Obstacle detector mode  
//--    * MODE = 3: Noise detector mode   
//--    * MODE = 4: ZowiPAD or any Teleoperation mode (listening SerialPort). 
//---------------------------------------------------------
volatile int MODE=0; //State of zowi in the principal state machine. 
byte sonrisa[5]={B01111110,
                   B01000010,
                   B00100100,
                   B00011000,
                   B00000000};
  
  byte sorpresa[5]={B00011000,
                    B00100100,
                    B00100100,
                    B00100100,
                    B00011000};

  byte jodido[5]={B01000010,
                  B00100100,
                  B00011000,
                  B00100100,
                  B01000010};

  byte alegre[5]={B00000000,
                  B01000010,
                  B00100100,
                  B00011000,
                  B00000000};

int randomDance=0;
int randomSteps=0;

bool obstacleDetected = false;

void sonreir(){
  lc.setColumn(0,0,sonrisa[4]);
  lc.setColumn(0,1,sonrisa[3]);
  lc.setColumn(0,2,sonrisa[2]);
  lc.setColumn(0,3,sonrisa[1]);
  lc.setColumn(0,4,sonrisa[0]);
}

void sorprender(){
  lc.setColumn(0,0,sorpresa[4]);
  lc.setColumn(0,1,sorpresa[3]);
  lc.setColumn(0,2,sorpresa[2]);
  lc.setColumn(0,3,sorpresa[1]);
  lc.setColumn(0,4,sorpresa[0]);
}


void alegrar(){
  lc.setColumn(0,0,alegre[4]);
  lc.setColumn(0,1,alegre[3]);
  lc.setColumn(0,2,alegre[2]);
  lc.setColumn(0,3,alegre[1]);
  lc.setColumn(0,4,alegre[0]);
}




///////////////////////////////////////////////////////////////////
//-- Setup ------------------------------------------------------//
///////////////////////////////////////////////////////////////////
void setup(){

  //Serial communication initialization
  Serial.begin(9600);
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);

  
  //Set the servo pins
  zowi.init(PIN_YL,PIN_YR,PIN_RL,PIN_RR,true);
  zowi.home();

  

}



///////////////////////////////////////////////////////////////////
//-- Principal Loop ---------------------------------------------//
///////////////////////////////////////////////////////////////////
void loop() {

    


    zowi.home();
    delay(5000);
    MODE=1;
  

    switch (MODE) {

      //-- MODE 1 - Dance Mode!
      //---------------------------------------------------------
      case 1:
        
        randomDance=random(5,21); //5,20
        if((randomDance>14)&&(randomDance<19)){
            randomSteps=1;
            sonreir();
            T=1600;
        }
        else{
            randomSteps=random(3,6); //3,5
            sorprender();
            T=1000;
        }
        
        

        for (int i=0;i<randomSteps;i++){
           
            move(randomDance);
            alegrar();
        }
        break;


      //-- MODE 2 - Obstacle detector mode
      //---------------------------------------------------------
      case 2:

        if(obstacleDetected){

            

            //Zowi takes two steps back
            for(int i=0;i<3;i++){ 
              zowi.walk(1,1300,-1);
            }

            delay(100);
            obstacleDetector();
            delay(100);


           //If there are no obstacles and no button is pressed, Zowi shows a smile
           if((obstacleDetected==true)){break;}            
           else{
              zowi.putMouth(smile);
              delay(50);
              obstacleDetector();
           } 
            
           
           //If there are no obstacles and no button is pressed, Zowi shows turns left
           for(int i=0; i<3; i++){
              if((obstacleDetected==true)){break;}            
              else{ 
                  zowi.turn(1,1000,1); 
                  obstacleDetector();
              } 
           }
            
            //If there are no obstacles and no button is pressed, Zowi is happy
            if((obstacleDetected==true)){break;}           
            else{
                zowi.home();
                zowi.putMouth(happyOpen);
                zowi.sing(S_happy_short);
                delay(200);
            }     
        

        }else{

            zowi.walk(1,1000,1); //Zowi walk straight
            obstacleDetector();
        }   

        break;


      default:
          MODE=4;
          break;
    }

   

}  

void obstacleDetector(){
   
   
   int distance = distanceSensor.measureDistanceCm();

        if(distance<15){
          obstacleDetected = true;
        }else{
          obstacleDetected = false;
        }
}



void move(int moveId){

  bool manualMode = false;

  switch (moveId) {
    case 0:
      zowi.home();
      break;
    case 1: //M 1 1000 
      zowi.walk(1,T,1);
      break;
    case 2: //M 2 1000 
      zowi.walk(1,T,-1);
      break;
    case 3: //M 3 1000 
      zowi.turn(1,T,1);
      break;
    case 4: //M 4 1000 
      zowi.turn(1,T,-1);
      break;
    case 5: //M 5 1000 30 
      zowi.updown(1,T,moveSize);
      break;
    case 6: //M 6 1000 30
      zowi.moonwalker(1,T,moveSize,1);
      break;
    case 7: //M 7 1000 30
      zowi.moonwalker(1,T,moveSize,-1);
      break;
    case 8: //M 8 1000 30
      zowi.swing(1,T,moveSize);
      break;
    case 9: //M 9 1000 30 
      zowi.crusaito(1,T,moveSize,1);
      break;
    case 10: //M 10 1000 30 
      zowi.crusaito(1,T,moveSize,-1);
      break;
    case 11: //M 11 1000 
      zowi.jump(1,T);
      break;
    case 12: //M 12 1000 30 
      zowi.flapping(1,T,moveSize,1);
      break;
    case 13: //M 13 1000 30
      zowi.flapping(1,T,moveSize,-1);
      break;
    case 14: //M 14 1000 20
      zowi.tiptoeSwing(1,T,moveSize);
      break;
    case 15: //M 15 500 
      zowi.bend(1,T,1);
      break;
    case 16: //M 16 500 
      zowi.bend(1,T,-1);
      break;
    case 17: //M 17 500 
      zowi.shakeLeg(1,T,1);
      break;
    case 18: //M 18 500 
      zowi.shakeLeg(1,T,-1);
      break;
    case 19: //M 19 500 20
      zowi.jitter(1,T,moveSize);
      break;
    case 20: //M 20 500 15
      zowi.ascendingTurn(1,T,moveSize);
      break;
    default:
        manualMode = true;
      break;
  }

       
}


//-- Function to receive gestu
