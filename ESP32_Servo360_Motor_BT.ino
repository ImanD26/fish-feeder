#include <Servo_ESP32.h>

static const int servo1Pin = 19;

int motorPin1 = 4; 
int motorPin2 = 2; 
int enablePin = 14; 

Servo_ESP32 servo1;
int servo1Angle;

#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
char receivedChar;
String inData;

void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  servo1.attach(servo1Pin);
  
  Serial.begin(115200);
  SerialBT.begin("ESP32_Servo360_Motor"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");


  }

void loop() {

  if (Serial.available()) {
    SerialBT.write(Serial.read());
  
  }
  while (SerialBT.available() ) {
    receivedChar =(char)SerialBT.read();
    inData += receivedChar;    
        if (receivedChar == '\n')
        {    
    
    servo1Angle = inData.toInt() ;//convert it to integer  
    
    if(servo1Angle == 0)
    {
      servo1.write(0);//move servo to that angle
      analogWrite(enablePin, 255);
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);  
    }

    else if(servo1Angle == 90)
    {
      servo1.write(90);//move servo to that angle  
      analogWrite(enablePin, 0);
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW); 
    }
         inData = ""; // Clear recieved buffer                    
                  
        }

  
  } delay(20);

}
