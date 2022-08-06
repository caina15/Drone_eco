#include <Servo.h>

#define PinEcho0 3
#define PinEcho1 4
#define PinEcho2 5
#define PinEcho3 7

int F = 0;
int T = 0;
int X = 0;
int R = 5;
int sen1 = 0;
int sen2 = 0;
int sen3 = 0;
int sen4 = 0;
int anguloF = 0;
int anguloT = 0;
Servo servoF;
Servo servoT;

void setup(){

  DDRD = 00000100; //direção
  servoF.attach (10);
  servoT.attach (11);
  Serial.begin(9600);
}
void loop(){
  
  long echo, cm;
  
  PORTD &= ~(1<<2);
  delayMicroseconds(2);
  PORTD |= (1<<2);
  delayMicroseconds(5);
  PORTD &= ~(1<<2);

  echo = pulseIn(PinEcho0, HIGH);
  cm = microsecondsToCentimeters(echo);
  Serial.print(" // 1 = ");
  Serial.print(cm);
  sen1 = cm;
  //delay(10);

  PORTD &= ~(1<<2);
  delayMicroseconds(2);
  PORTD |= (1<<2);
  delayMicroseconds(5);
  PORTD &= ~(1<<2);

  echo = pulseIn(PinEcho1, HIGH);
  cm = microsecondsToCentimeters(echo);
  Serial.print(" // 2 = ");
  Serial.print(cm);
  sen2 = cm;
  //delay(10);

  delayMicroseconds(2);
  PORTD |= (1<<2);
  delayMicroseconds(5);
  PORTD &= ~(1<<2);

  echo = pulseIn(PinEcho2, HIGH);
  cm = microsecondsToCentimeters(echo);
  Serial.print(" // 3 = ");
  Serial.print(cm);
  sen3 = cm;
  //delay(10);

  delayMicroseconds(2);
  PORTD |= (1<<2);
  delayMicroseconds(5);
  PORTD &= ~(1<<2);

  echo = pulseIn(PinEcho3, HIGH);
  cm = microsecondsToCentimeters(echo);
  Serial.print(" // 4 = ");
  Serial.print(cm);
  sen4 = cm;
  //delay(10);
  
  if (sen1>50 || sen1<5){
    sen1 = sen2;
    Serial.print(" Erro sensor 1, sensor 2 assume!");
  }

  if (sen2>50 || sen2<5){
    sen2 = sen1;
    Serial.print(" Erro sensor 2, sensor 1 assume!");
  }

  if (sen3>50 || sen3<5){
    sen3 = sen4;
    Serial.print(" Erro sensor 3, sensor 4 assume!");
  }

  if (sen4>50 || sen4<5){
    sen4 = sen3;
    Serial.print(" Erro sensor4, sensor 3 assume!");
  }

  F = (sen1 + sen2)/2;
  T = (sen3 + sen4)/2;
  X = abs(T-F);

  if (F<=T){
    Serial.print("  //  ");
    Serial.print(X*R);
    Serial.print("  //  ");
    Serial.print(X);
    Serial.print("  //  ");
    anguloF = map((X*R), 0, 125, 0, 90);
      Serial.print(anguloF);
      Serial.println(" Graus");
      servoF.write(anguloF);
    
  }else{
    Serial.print("  //  ");
    Serial.print("T! ");
    Serial.print(X*R);
    Serial.print("  //  ");
    Serial.print(X);
    Serial.print("  //  ");
    anguloT = map((X*R), 0, 125, 0, 90);
      Serial.print(anguloT);
      Serial.println(" Graus");
      servoT.write(anguloT);
  }
  //delay(10);
}
long microsecondsToCentimeters(long microseconds){
   return microseconds / 29 / 2;
}