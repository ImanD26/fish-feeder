#include <Wire.h> //tes menggerakan servo dengan rtc
#include <ESP32Servo.h>
#define servoPin 19
Servo servo;
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

byte feedHour = 13; //waktu beri makan
byte feedMinute = 30;
byte feedSecond = 59;


void setup(){
  Wire.begin(25,26);
  Serial.begin(9600);
  changeTime();

  servo.setPeriodHertz(50);
  servo.attach(servoPin, 500, 2400);
  
 }
void loop(){ 
  printTime();
  delay(1000);
  
 if (feedHour==hour && feedMinute==minute && feedSecond==second) {
    servo.write(180);
    delay(2000);
  }
 else {
  servo.write(0);
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

  Wire.beginTransmission(I2C_ADDRESS); //waktu sekarang
  Wire.write(byte(0));
  Wire.write(decToBcd(55)); // second
  Wire.write(decToBcd(30)); // minute
  Wire.write(decToBcd(13)); // hour
  Wire.write(decToBcd(5));  // weekday
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
