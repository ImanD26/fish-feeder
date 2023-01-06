//write dari serial monitor ke LCD
#include <LiquidCrystal.h>
 
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(19, 23, 18, 17, 16, 15);
int motorSpeed; //int untuk mengatur kecepatan & on/off

void setup() {

  lcd.begin(16, 2);

  Serial.begin(115200);
  Serial.println("ESP32_LCD");
}

void loop() {

  if (Serial.available()) {
    motorSpeed=Serial.read();
    Serial.println(motorSpeed);
  }

    if(motorSpeed == 1) //ON
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ON"); 
    }

   if(motorSpeed == 0) //OFF
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("OFF");  
    }
    
    if(motorSpeed > 1 && motorSpeed < 256) //ubah kecepatan motor dengan ubah pwm
    {
      lcd.setCursor(0, 1);
      lcd.print("PWM : ");
      lcd.setCursor(7, 1);
      lcd.print(motorSpeed);
      delay(100);
    }
 
                    
                  
        }
