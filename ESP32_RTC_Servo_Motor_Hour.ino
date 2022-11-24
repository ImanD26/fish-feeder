//kode test RTC per jam
#include <Wire.h>
#include <Servo_ESP32.h>

static const int servo1Pin = 19;
Servo_ESP32 servo1;
int servo1Angle;

const int I2C_ADDRESS = 0x68;

const char* days[] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
const char* months[] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus","September", "Oktober", "November", "Desember"};

byte second;
byte minute;
byte hour;
byte weekday;
byte monthday;
byte month;
byte year;
byte i=0;

// waktu untuk memberi makan
byte feedHour = 2;
byte feedMinute = 0;
byte feedSecond = 0;

int motorPin1 = 4; 
int motorPin2 = 2; 
int enablePin = 14; 

void setup(){
  Wire.begin(25,26);
  Serial.begin(9600);
  changeTime();
  servo1.attach(servo1Pin);

  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
  // testing
  Serial.print("Testing System...");
 }
void loop(){ 
  printTime();
  delay(1000);
  
 if (feedHour==hour && feedMinute==minute && feedSecond==second || feedHour+i==hour+i && feedMinute==minute && feedSecond==second) {
      servo1.write(0);//move servo to that angle
      analogWrite(enablePin, 255);
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      delay(1000); 
      i++;
  }
 if(i==23){
  i=0;
 }
 else {
      servo1.write(90);//move servo to that angle  
      analogWrite(enablePin, 0);
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW); 

 }
}
void printTime() {
  char buffer[3];
  const char* AMPM = 0;
  readTime();
  Serial.print(days[weekday-1]);
  Serial.print(" ");
  Serial.print(monthday);
  Serial.print(" ");
  Serial.print(months[month-1]);
  Serial.print(" 20");
  Serial.print(year);
  Serial.print(" ");
  Serial.print(hour);
  Serial.print(":");
  sprintf(buffer, "%02d", minute);
  Serial.print(buffer);
  Serial.print(":");
  sprintf(buffer, "%02d", second);
  Serial.print(buffer);
  Serial.println(AMPM);
  
}
void readTime() {
  
  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write(byte(0));
  Wire.endTransmission();
  Wire.requestFrom(I2C_ADDRESS, 7);
  second = bcdToDec(Wire.read());
  minute = bcdToDec(Wire.read());
  hour = bcdToDec(Wire.read());
  weekday = bcdToDec(Wire.read());
  monthday = bcdToDec(Wire.read());
  month = bcdToDec(Wire.read());
  year = bcdToDec(Wire.read());
  
}
void changeTime() {

  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write(byte(0));
  Wire.write(decToBcd(55)); // second
  Wire.write(decToBcd(59)); // minute
  Wire.write(decToBcd(1)); // hour
  Wire.write(decToBcd(1));  // weekday
  Wire.write(decToBcd(1)); // date
  Wire.write(decToBcd(1));  // month
  Wire.write(decToBcd(22)); // year
  Wire.write(byte(0));
  Wire.endTransmission();
  
}
byte decToBcd(byte val) {
  return ((val/10*16) + (val%10));
}
byte bcdToDec(byte val) {
  return ((val/16*10) + (val%16));
}
