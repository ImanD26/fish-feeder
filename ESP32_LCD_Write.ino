//write dari serial monitor ke LCD
#include <LiquidCrystal_I2C.h>
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  
int motorSpeed; //int untuk mengatur kecepatan & on/off

void setup() {
  // put your setup code here, to run once:
  lcd.init();                    
  lcd.backlight();

  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
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
