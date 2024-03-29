//Tes sistem pada 2 waktu siang (12:00), sore (16:00)

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

//waktu untuk memberi makan
byte feedHour1 = 12;
byte feedMinute1 = 0;
byte feedSecond1 = 0;

byte feedHour2 = 16;
byte feedMinute2 = 0;
byte feedSecond2 = 0;

int motorPin1 = 4; 
int motorPin2 = 2; 
int enablePin = 14; 

void setup(){
  Wire.begin(26,25);
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

 //Jika waktu beri makan=RTC sistem aktif
 if (feedHour1==hour && feedMinute1==minute && feedSecond1==second || feedHour2==hour && feedMinute2==minute && feedSecond2==second) {
      servo1.write(0);//move servo to that angle
      analogWrite(enablePin, 255);
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      delay(1000);
      
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

//waktu pada RTC (ganti sesuai waktu asli)
void changeTime() {

  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write(byte(0));
  Wire.write(decToBcd(55)); // second
  Wire.write(decToBcd(59)); // minute
  Wire.write(decToBcd(11)); // hour
  Wire.write(decToBcd(2));  // weekday
  Wire.write(decToBcd(6)); // date
  Wire.write(decToBcd(12));  // month
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
