#include <Servo_ESP32.h>

static const int servo1Pin = 19; //printed G19 on the board

Servo_ESP32 servo1;

int servo1Angle =90;
int servo1AngleMin =0;
int servo1AngleMax = 180;

#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
String inData;

char receivedChar;// received value will be stored as CHAR in this variable

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_Servo"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  
    servo1.attach(servo1Pin);

}

void loop() {

  //Robojax.com Servo with ESP32 Bluetooth
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  
  }
  while (SerialBT.available() ) {
    receivedChar =(char)SerialBT.read();
    inData += receivedChar;    
        if (receivedChar == '\n')
        {    
    SerialBT.print("Received:");// write on BT app
    SerialBT.println(inData);// write on BT app   

    Serial.print("Received:");//print on Serial Monitor
    Serial.println(inData); //print on Serial Monitor     
    
    servo1Angle = inData.toInt() ;//convert it to integer  
    
    if(servo1Angle <=servo1AngleMax && servo1Angle >=servo1AngleMin)
    {
      servo1.write(servo1Angle);//move servo to that angle   
    }
           inData = ""; // Clear recieved buffer                    
                  
        }//if (receivedChar


  }// while

        //Serial.println(servo1Angle);
        delay(20);

}
