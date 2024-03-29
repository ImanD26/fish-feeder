//tes ubah kecepatan motor melalui esp32 bluetooth
#include <Servo_ESP32.h>

static const int servo1Pin = 19;

int motorPin1 = 4; 
int motorPin2 = 2; 
int enablePin = 14; 

Servo_ESP32 servo1;

int motorSpeed; //int untuk mengatur kecepata & on/off

#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
char receivedChar; //char yg diterima oleh esp32 dari bluetooth
String inData; //untuk konversi char masuk ke string lalu ke int

void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  servo1.attach(servo1Pin);
  
  Serial.begin(115200);
  SerialBT.begin("ESP32_Servo360_Motor_Speed"); //Bluetooth device name
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
    
    motorSpeed = inData.toInt() ;//konversi ke integer  
    
    if(motorSpeed == 1) //ON
    {
      servo1.write(0);//move servo to that angle
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);  
    }

   if(motorSpeed == 0) //OFF
    {
      servo1.write(90);//move servo to that angle  
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW); 
    }
    
    if(motorSpeed > 1 && motorSpeed < 256) //ubah kecepatan motor dengan ubah pwm
    {
      analogWrite(enablePin, motorSpeed);
      
    }
 
         inData = ""; // Clear recieved buffer                    
                  
        }

  
  } delay(20);

}
