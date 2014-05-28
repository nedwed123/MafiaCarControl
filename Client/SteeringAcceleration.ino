/*************************************************************
Motor Shield 1-Channel DC Motor Demo
by Randy Sarafan

For more information see:
http://www.instructables.com/id/Arduino-Motor-Shield-Tutorial/

*************************************************************/
#include <Servo.h>

Servo VishalServo;

void setup() {
  Serial.begin(9600);
  Serial.println("SmartCar");
  //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin  
  
  //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel A pin
  pinMode(8, OUTPUT); //Initiates Brake Channel A pin
  VishalServo.attach(10);
  
  //This is for the led lamp
  //pinMode(6, OUTPUT);
  
  //VishalServo.writeMircoseconds(1500);
  Serial.println("Wait for 1 second");
  delay(1000);
  Serial.println("1=Forward");
  Serial.println("2=Backward");
  Serial.println("3=ForwardLeft");
  Serial.println("4=ForwardRight");
  Serial.println("5=Break");
  Serial.println("6=BackwardLeft");
  Serial.println("7=BackwardRight");
  Serial.println("8=360ClockSpinFlip");
  Serial.println("9=REVERSED360ClockSpinFlip");
  
}

void loop(){
  
  while(Serial.available()==0);
  int val = Serial.read()-'0';
  int i = VishalServo.read();
 
  //backward @ full speed 
  if(val==2){
  digitalWrite(9, HIGH); //Eengage the Brake for Channel A
  digitalWrite(8, HIGH); //Eengage the Brake for Channel B
  
  digitalWrite(12, HIGH); //Establishes backward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 123);   //Spins the motor on Channel A at full speed
  
  digitalWrite(13, LOW); //Establishes backward direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, 123);   //Spins the motor on Channel B at full speed
  
  delay(3000);
  }
  
  //This is for the break
  if(val==5){
  digitalWrite(9, HIGH); //Eengage the Brake for Channel A
  digitalWrite(8, HIGH); //Eengage the Brake for Channel B
  
  delay(1000);
  }
  
  //forward @ full speed 
  if(val==1){
  digitalWrite(9, HIGH); //Eengage the Brake for Channel A
  digitalWrite(8, HIGH); //Eengage the Brake for Channel B
  
  digitalWrite(12, LOW); //Establishes forward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 123);   //Spins the motor on Channel A at half speed
  
  digitalWrite(13, HIGH); //Establishes forward direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, 123);   //Spins the motor on Channel B at half speed
  
  delay(3000);
  }
  
  
  //This is for turning forward Left
  if(val==3){
  digitalWrite(9, HIGH); //Eengage the Brake for Channel A
  digitalWrite(8, HIGH); //Eengage the Brake for Channel B
  
  digitalWrite(12, LOW); //Establishes Forward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 255);   //Spins the motor on Channel A at full speed
     
  }
  //This is for turning forward right
  
  if(val==4){
  digitalWrite(9, HIGH); //Eengage the Brake for Channel A
  digitalWrite(8, HIGH); //Eengage the Brake for Channel B
  
  digitalWrite(13, HIGH); //Establishes Forward direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, 255);   //Spins the motor on Channel B at full speed
  }
  
  //This is for turning backward Left
  if(val==6){
  digitalWrite(9, HIGH); //Eengage the Brake for Channel A
  digitalWrite(8, HIGH); //Eengage the Brake for Channel B
  
  digitalWrite(12, HIGH); //Establishes Backward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 255);   //Spins the motor on Channel A at full speed
  }
  //This is for turning backward Right
  if(val==7){
  digitalWrite(9, HIGH); //Eengage the Brake for Channel A
  digitalWrite(8, HIGH); //Eengage the Brake for Channel B
  
  digitalWrite(13, LOW); //Establishes Backward direction of Channel A
  digitalWrite(8, LOW);   //Disengage the Brake for Channel A
  analogWrite(11, 255);   //Spins the motor on Channel A at full speed
  }
  //clockSpin360flip
  if(val==8){
  digitalWrite(9, HIGH); //Eengage the Brake for Channel A
  digitalWrite(8, HIGH); //Eengage the Brake for Channel B
  
  digitalWrite(13, HIGH); //Establishes Forward direction of Channel b
  digitalWrite(8, LOW);   //Disengage the Brake for Channel b
  analogWrite(11, 255);   //Spins the motor on Channel b at full speed
  
  digitalWrite(12, HIGH); //Establishes backward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 255);   //Spins the motor on Channel A at full speed
  
}
  //ANTICLOCKSPIN360fli
  if(val==9){
  digitalWrite(9, HIGH); //Eengage the Brake for Channel A
  digitalWrite(8, HIGH); //Eengage the Brake for Channel B
  
  digitalWrite(13, LOW); //Establishes Backward direction of Channel b
  digitalWrite(8, LOW);   //Disengage the Brake for Channel b
  analogWrite(11, 255);   //Spins the motor on Channel b at full speed
  
  digitalWrite(12, LOW); //Establishes Forward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 255);   //Spins the motor on Channel A at full speed
  
}

}
Arduino Motor Shield Tutorial
www.instructables.com
