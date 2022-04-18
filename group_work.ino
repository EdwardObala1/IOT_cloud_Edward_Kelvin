//IoT Cloud Access Group Assignment

#include <DFRobot_DHT11.h>
#include <LiquidCrystal.h>
DFRobot_DHT11 DHT;

#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

char ssid[] = "CANALBOX-0308";   // your network SSID (name) 
char pass[] = "1904358430";   // your network password
WiFiClient  client;


unsigned long myChannelId = 1706463;
const char * myWriteAPIKey = "MHNS3UPZF0UHGDNW";
const char * myReadAPIKey = "3RN9CW6HUTFX684V";

static const uint8_t D4 = 2;
static const uint8_t D5 = 14;
static const uint8_t D6 = 12;
static const uint8_t D7 = 13;
static const uint8_t D8 = 15;
static const uint8_t D3 = 0;
static const uint8_t D2 = 4;
static const uint8_t D0 = 5;

int fan = D0;
int DHT11_PIN = D2;
const int rs = D3, en = D8, d4 = D4, d5 = D5, d6 = D6, d7 = D7;

//LiquidCrystal lcd(D3, D8, D4, D5, D6, D7);
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup(){

  // Initialise Serial Monitor & LCD screen
  lcd.begin(16,2);
  Serial.begin(115200);
  pinMode(fan, OUTPUT);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client); // Initialize ThingSpeak
}


void loop(){
  //Clear LCD screen
  lcd.clear();

  // Connect or reconnect to WiFi

  if(WiFi.status() != WL_CONNECTED){

    Serial.print("Attempting to connect to SSID: ");

    Serial.println("NunuaBundles");

    while(WiFi.status() != WL_CONNECTED){

      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network

      Serial.print(".");

      delay(5000);     

    } 

    Serial.println("\nConnected.");

  }
  
  
  // Read value from DHT pin
  DHT.read(DHT11_PIN);

  // Save values as variables
  float temp = DHT.temperature;
  float hum = DHT.humidity;
 

  //Top Row of LCD Screen
  lcd.setCursor(0,0);
  // Print humidity results
  lcd.print("Humidity = ");
  lcd.print(hum);
  
  Serial.print("Humidity = ");
  Serial.println(hum);

  // Bottom Row of LCD screen
  lcd.setCursor(0,1); //set the cursor to column 0 and line 1
  // Print temperature results
  lcd.print("Temp = ");
  lcd.print(temp);
  
  Serial.print("Temp = ");
  Serial.println(temp);
  // Fan_Control
  Serial.println("FAN");
  Serial.println(fan);
  Serial.println(temp);

  analogWrite(fan, LOW);


  if (temp >= 27) {
    Serial.println("FAN On");

    analogWrite(fan, HIGH);
  }
  else if (temp < 27) {
    Serial.println("FAN Off");

    analogWrite(fan, LOW);
  }

  
  // set the fields with the values
  ThingSpeak.setField(1, temp);
  ThingSpeak.setField(2, hum);
  
  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelId, myWriteAPIKey);
  
  //read data that was previously added
  long dist = ThingSpeak.readLongField(myChannelId, 1, myReadAPIKey);
  
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }

  delay(1000);
}
