 

//This last step finishes the complete tutorial on IoT based Smart Irrigation System. Note that it is important to switch off the motor when the soil moisture has reached the required level after water sprinkle. You can make a more smart system which can contain different control for different crops.

//If you face any issues while doing this project then comment below or reach to our forums for more relevant questions and their answers.

//Find the complete program and demonstration Video for this project below.

//Code

//#include <DHT.h>
#include <ESP8266WiFi.h>
const char *ssid =  "Trojan in";     // Enter your WiFi Name
const char *pass =  "heisenberg"; // Enter your WiFi Password
//#define DHTPIN           // GPIO Pin where the dht11 is connected
//DHT dht(DHTPIN, DHT11);
WiFiClient client;

const int moisturePin = A0;             // moisteure sensor pin
const int motorPin = D0;
unsigned long interval = 10000;
unsigned long previousMillis = 0;
unsigned long interval1 = 1000;
unsigned long previousMillis1 = 0;
float moisturePercentage;              //moisture reading
//float h;                  // humidity reading


void setup()
{
  Serial.begin(9600);
  delay(10);
  pinMode(motorPin, OUTPUT);
  digitalWrite(motorPin, HIGH); // keep motor off initally
//  dht.begin();
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
 

while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");              // print ... till not connected
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

void loop()
{
  unsigned long currentMillis = millis(); // grab current time


  moisturePercentage = ( 100.00 - ( (analogRead(moisturePin) / 1023.00) * 100.00 ) );

  if ((unsigned long)(currentMillis - previousMillis1) >= interval1) {
    Serial.print("Soil Moisture is  = ");
    Serial.print(moisturePercentage);
    Serial.println("%");
    previousMillis1 = millis();
  }

if (moisturePercentage < 10) {
  digitalWrite(motorPin, HIGH);         // tun on motor
}
if (moisturePercentage > 10 && moisturePercentage < 25) {
  digitalWrite(motorPin, HIGH);        //turn on motor pump
}
if (moisturePercentage > 25) {
  digitalWrite(motorPin, LOW);          // turn off mottor
}

}
