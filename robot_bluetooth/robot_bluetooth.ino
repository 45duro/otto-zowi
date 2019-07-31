byte motDerA = 4, motDerAt = 5, motIzqA = 6, motIzqAt = 7;
char dato = 0;
void setup() {
  Serial.begin(9600);
  for(byte i = 4; i < 8; i++){
    pinMode(i,OUTPUT);
  }

}

void loop() {
   if(Serial.available()){
      dato=Serial.read();
      Serial.println(dato);
   }

   switch (dato){
    case 'a':
      adelante();
      break;

    case 'b':
      atras();
      break;

    case 'r':
      derecha();
      break;

    case 'l':
      izquierda();
      break;

    case 'g':
      giro360();
      break;

    default:
      parar();
      break;
     
   }


}

void adelante(){
  digitalWrite(motDerA,1);  digitalWrite(motIzqA,1);
  digitalWrite(motDerAt,0); digitalWrite(motIzqAt,0);
}

void atras(){
  digitalWrite(motDerA,0);  digitalWrite(motIzqA,0);
  digitalWrite(motDerAt,1); digitalWrite(motIzqAt,1);
}

void derecha(){
  digitalWrite(motDerA,0);  digitalWrite(motIzqA,1);
  digitalWrite(motDerAt,0); digitalWrite(motIzqAt,0);
}

void izquierda(){   
  digitalWrite(motDerA,1);  digitalWrite(motIzqA,0);
  digitalWrite(motDerAt,0); digitalWrite(motIzqAt,0);
}

void giro360(){
  digitalWrite(motDerA,1);  digitalWrite(motIzqA,0);
  digitalWrite(motDerAt,0); digitalWrite(motIzqAt,1);
}

void parar(){
  digitalWrite(motDerA,0);  digitalWrite(motIzqA,0);
  digitalWrite(motDerAt,0); digitalWrite(motIzqAt,0);
}
