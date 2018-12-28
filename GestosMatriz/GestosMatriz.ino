#include <Servo.h>
#include "Otto.h"
#include "US.h"
#include "Oscillator.h"
#include "LedControl.h"


LedControl lc=LedControl(12,10,11,1);
double gesto;

Otto robot_otto;
int delaytime = 100;

double math_random_int(int a,int b) {
  if (a > b) {
    int c = a;
    a = b;
    b = c;
  }
  return (double)random(a,b+1);
}


struct GESTOS{

  byte limite = 4;
  
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

  


  void escribir(byte tabla[]){

    for(byte i = limite; i >= 0; i--){

      lc.setColumn(0,limite-i,tabla[i]);
      
    }

  }
  
} Boca;










void setup()
{
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
  
  robot_otto.init(2,3,4,5,false,A6,13,8,9);
  randomSeed(analogRead(0));
  robot_otto.sing(S_connection);
  robot_otto.home();
  robot_otto.playGesture(OttoSuperHappy);
  delay(1000);

}


void loop()
{

  
  Boca.escribir(Boca.sorpresa);
    
    /*
    if ((robot_otto.getDistance() < 10)) {
      gesto = math_random_int(1, 6);
      if ((gesto == 1)) {
        robot_otto.playGesture(OttoAngry);
      
      }
      if ((gesto == 2)) {
        robot_otto.playGesture(OttoSad);

      }
      if ((gesto == 3)) {
        robot_otto.playGesture(OttoFart);

      }
      if ((gesto == 4)) {
        robot_otto.playGesture(OttoLove);

      }
      if ((gesto == 5)) {
        robot_otto.playGesture(OttoVictory);

      }

    } else {
      robot_otto.home();

    }
    */

}



/*
  lc.setColumn(0,0,sorpresa[4]);
  lc.setColumn(0,1,sorpresa[3]);
  lc.setColumn(0,2,sorpresa[2]);
  lc.setColumn(0,3,sorpresa[1]);
  lc.setColumn(0,4,sorpresa[0]);
  


  lc.setColumn(0,0,alegre[4]);
  lc.setColumn(0,1,alegre[3]);
  lc.setColumn(0,2,alegre[2]);
  lc.setColumn(0,3,alegre[1]);
  lc.setColumn(0,4,alegre[0]);
  
*/
