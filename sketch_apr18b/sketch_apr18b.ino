//Robu.in

#include <DFRobot_DHT11.h>
#include<LiquidCrystal.h>
static const uint8_t D4 = 2;
static const uint8_t D5 = 14;
static const uint8_t D6 = 12;
static const uint8_t D7 = 13;
static const uint8_t D8 = 15;
static const uint8_t D3 = 0;
static const uint8_t D2 = 4;
static const uint8_t D0 = 5;
const int rs = D3, en = D8, d4 = D4, d5 = D5, d6 = D6, d7 = D7;

//LiquidCrystal lcd(D3, D8, D4, D5, D6, D7);
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

DFRobot_DHT11 DHT;

int DHT11_PIN = D2;


#define DHTTYPE DHT11   // DHT 11 

#define pwm 9

byte degree[8] = 
              {
                0b00011,
                0b00011,
                0b00000,
                0b00000,
                0b00000,
                0b00000,
                0b00000,
                0b00000
              };
// Initialize DHT sensor for normal 16mhz Arduino

void setup() {

 lcd.createChar(1, degree);
 lcd.clear();
 lcd.print("   Fan Speed  ");
 lcd.setCursor(0,1);
 lcd.print("  Controlling ");
 delay(2000);
 analogWrite(pwm, 255);
 lcd.clear();
 lcd.print("Robu ");
 
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = DHT.humidity;
  // Read temperature as Celsius
  float t = DHT.temperature;
  // Read temperature as Fahrenheit
  float f = DHT.temperature;
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index
  // Must send in t in Fahrenheit!

  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("temperature: "); 
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");

  Serial.println(" *F");

    lcd.setCursor(0,0);
  lcd.print("temp: ");
  lcd.print(t);   // Printing terature on LCD
  lcd.print(" C");
  lcd.setCursor(0,1);
  Serial.print(t);

  if(t <20 )
    { 
      analogWrite(9,0);
      //lcd.print("Fan OFF            ");
      delay(100);
    }
    
   else if(t==26)
    {             
      analogWrite(pwm, 51);
      //lcd.print("Fan Speed: 20%   ");
      delay(100);
    }
    
    else if(t==20)
    {
      analogWrite(pwm, 102);
      //lcd.print("Fan Speed: 40%   ");
      delay(100);
    }
    
    else if(t==28)
    {
      analogWrite(pwm, 153);
      //lcd.print("Fan Speed: 60%   ");
      delay(100);
    }
    
    else if(t==29)
    {
      analogWrite(pwm, 204);
      
      //lcd.print("Fan Speed: 80%    ");
      delay(100);
    }
     else if(t>29)
    {
      analogWrite(pwm, 255);
      //lcd.print("Fan Speed: 100%   ");
      delay(100);
    } 
  delay(1000);
}
