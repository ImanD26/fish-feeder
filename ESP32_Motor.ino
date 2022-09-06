#include "BluetoothSerial.h"

int in1=26, in2=27;
int enablePin=14;

BluetoothSerial SerialBT;

const int freq=3000;
const int pwmChannel=0;
const int resolution=8;
int dutyCycle=1000;
char inChar;
String inString="";

void setup(){
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  ledcSetup(pwmChannel,freq,resolution);
  ledcAttachPin(enablePin,pwmChannel);

  Serial.begin(115200);
  Serial.print("Testing DC Motor...");
  SerialBT.begin("ESP32_Motor"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");


}


void loop(){
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  
    while(SerialBT.available()){
      inChar=(char)SerialBT.read();
      inString += (char)inChar; 
    
    if(inChar=='\n'){
      Serial.print("Value : ");
      Serial.println(inString.toInt());

      int val=inString.toInt();

      cw(val);

      inString="";
    }
  }
}

void cw(int pwm){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  ledcWrite(pwmChannel, pwm);
  
}

void ccw(int pwm){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  ledcWrite(pwmChannel, pwm);
  
}
