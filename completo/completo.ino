
#include <Servo.h> 
#include <Oscillator.h>
#include <BatReader.h>
#include <US.h>



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


int randomDance=0;
int randomSteps=0;

bool obstacleDetected = false;


///////////////////////////////////////////////////////////////////
//-- Setup ------------------------------------------------------//
///////////////////////////////////////////////////////////////////
void setup(){

  //Serial communication initialization
  Serial.begin(9600);  

  
  //Set the servo pins
  zowi.init(PIN_YL,PIN_YR,PIN_RL,PIN_RR,true);
  zowi.home();


  zowi.putMouth(culito);


}



///////////////////////////////////////////////////////////////////
//-- Principal Loop ---------------------------------------------//
///////////////////////////////////////////////////////////////////
void loop() {




    zowi.home();
    delay(20000);
    MODE=1;
    delay(100); //Wait for all buttons 
    zowi.sing(S_buttonPushed);
    delay(200); //Wait for all buttons 

  
    zowi.putMouth(MODE);
 
    delay(5000);
    zowi.putMouth(happyOpen);

 

    switch (MODE) {

      //-- MODE 1 - Dance Mode!
      //---------------------------------------------------------
      case 1:
        
        randomDance=random(5,21); //5,20
        if((randomDance>14)&&(randomDance<19)){
            randomSteps=1;
            T=1600;
        }
        else{
            randomSteps=random(3,6); //3,5
            T=1000;
        }
        
        zowi.putMouth(random(10,21));

        for (int i=0;i<randomSteps;i++){
            move(randomDance);
            
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

   int distance = zowi.getDistance();

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
