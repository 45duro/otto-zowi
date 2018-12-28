#include "LedControl.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 the pins are connected at (DataIn, CLK, LOAD)
 the pins are connected at (12, 10, 11)
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(12,10,11,1);

/* we always wait a bit between updates of the display */
unsigned long delaytime=2000;

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
}


void writeArduinoOnMatrix() {
  /* here is the data for the characters */
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

  

  lc.setColumn(0,0,sonrisa[4]);
  lc.setColumn(0,1,sonrisa[3]);
  lc.setColumn(0,2,sonrisa[2]);
  lc.setColumn(0,3,sonrisa[1]);
  lc.setColumn(0,4,sonrisa[0]);
  delay(delaytime);

    
  lc.setColumn(0,0,sorpresa[4]);
  lc.setColumn(0,1,sorpresa[3]);
  lc.setColumn(0,2,sorpresa[2]);
  lc.setColumn(0,3,sorpresa[1]);
  lc.setColumn(0,4,sorpresa[0]);
  delay(delaytime);


  lc.setColumn(0,0,alegre[4]);
  lc.setColumn(0,1,alegre[3]);
  lc.setColumn(0,2,alegre[2]);
  lc.setColumn(0,3,alegre[1]);
  lc.setColumn(0,4,alegre[0]);
  delay(delaytime);
}

void loop() { 
  writeArduinoOnMatrix();
}
