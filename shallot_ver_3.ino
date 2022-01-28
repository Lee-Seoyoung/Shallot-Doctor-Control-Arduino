#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

const int relayPin = 6; //릴레이
const int tempPin = A1; //온도센서

LiquidCrystal_I2C lcd(0x27,16,2);
DHT my_sensor(tempPin, DHT22);

const float setTempC = 38.0;
const float setTempC2 = 42.0;

byte degree[] = {0b00100,
                 0b01001,
                 0b01001,
                 0b00110,
                 0b00000,
                 0b00000,
                 0b00000,
                 0b00000
                }; //˚문자 만듦.


void setup() {

  lcd.init();// initialize the lcd 
  lcd.init();// Print a message to the LCD.
  lcd.backlight();
  
  lcd.begin(16, 2);
  lcd.print("Temp. :");
  lcd.setCursor(0,1);
  lcd.print("Fan ");
  lcd.createChar(0, degree);

  pinMode(relayPin, OUTPUT);
  pinMode(tempPin, INPUT);

  Serial.begin(9600);
  
  my_sensor.begin();

}

void loop() {

float temp = my_sensor.readTemperature();
float humi = my_sensor.readHumidity();
  
  Serial.print("현재 온도 : ");
  Serial.print(temp);
  Serial.print(" / ");

  Serial.print("현재 습도 : ");
  Serial.println(humi);


if( temp < setTempC) {

 digitalWrite(relayPin,HIGH);

lcd.setCursor(8,0);
lcd.print(temp);
lcd.write((byte)0);
lcd.write('C'); //현재 온도 LCD에 출력

lcd.setCursor(0,1);
lcd.print("                  ");

 lcd.setCursor(0,1);
  lcd.print("Fan ");
  lcd.createChar(0, degree);
   lcd.setCursor(4,1);
   lcd.print("ON");

}

else if(temp > setTempC2 ) {
  
digitalWrite(relayPin,LOW);
  
lcd.setCursor(8,0);
lcd.print(temp);
lcd.write((byte)0);
lcd.write('C'); //현재 온도 LCD에 출력


lcd.setCursor(0,1);
lcd.print("                  ");
lcd.setCursor(0,1);
lcd.print("Fan ");
lcd.createChar(0, degree);
lcd.setCursor(4,1);
lcd.print("OFF");
  
  
}

delay (18000);
}
