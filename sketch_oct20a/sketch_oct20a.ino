#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
SoftwareSerial esp8266(2,3); //Pin 2 & 3 of Arduino as RX and TX. Connect TX and RX of ESP8266 respectively.
#define DEBUG true


void setup()
  {
    const int moisturePin = A0;             // moisteure sensor pin
    const int motorPin = D0;
    unsigned long interval = 10000;
    unsigned long previousMillis = 0;
    unsigned long interval1 = 1000;
	unsigned long previousMillis1 = 0;
	float moisturePercentage;
	
	pinMode(motorPin, OUTPUT);
	pinMode(moisturePin, INPUT);
	digitalWrite(motorPin, LOW);

    Serial.begin(9600);
    esp8266.begin(115200); //Baud rate for communicating with ESP8266. Your's might be different.
    esp8266Serial("AT+RST\r\n", 5000, DEBUG); // Reset the ESP8266
    esp8266Serial("AT+CWMODE=1\r\n", 5000, DEBUG); //Set station mode Operation
    //"SSID" is network name, "Password" is the password of network
    esp8266Serial("AT+CWJAP=\"SSID\",\"Password\"\r\n", 5000, DEBUG);//Enter your WiFi network's SSID and Password.
                                   
    while(!esp8266.find("OK")) 
    {
      }
    esp8266Serial("AT+CIFSR\r\n", 5000, DEBUG);//You will get the IP Address of the ESP8266 from this command. 
    esp8266Serial("AT+CIPMUX=1\r\n", 5000, DEBUG);
    esp8266Serial("AT+CIPSERVER=1,80\r\n", 5000, DEBUG);
  }

void loop()
  {
    if (esp8266.available())
      {
        if (esp8266.find("+IPD,"))
          {
            String msg;
            esp8266.find("?");
            msg = esp8266.readStringUntil(' ');
            String command1 = msg.substring(0, 3);
            String command2 = msg.substring(4);
                        
            if (DEBUG) 
              {
                Serial.println(command1);//Must print "Irr"
                Serial.println(command2);//Must print "ON" or "OFF"
              }
            delay(100);

              if (command2 == "ON") 
                    {
                       unsigned long currentMillis = millis(); // grab current time


  						moisturePercentage = ( 100.00 - ( (analogRead(moisturePin) / 1023.00) * 100.00 ) );

  						if ((unsigned long)(currentMillis - previousMillis1) >= interval1) {
    						Serial.print("Soil Moisture is  = ");
   							Serial.print(moisturePercentage);
    						Serial.println("%");
    						previousMillis1 = millis();
 						 }

						if (moisturePercentage <= 25) {
  							digitalWrite(motorPin, HIGH);         // tun on motor
						}
						if (moisturePercentage > 25) {
  							digitalWrite(motorPin, LOW);          // turn off mottor
						}
			  }
                   else 
                     {
                       digitalWrite(motorPin, LOW);
                     }
          }
      }
  }
   
String esp8266Serial(String command, const int timeout, boolean debug)
  {
    String response = "";
    esp8266.print(command);
    long int time = millis();
    while ( (time + timeout) > millis())
      {
        while (esp8266.available())
          {
            char c = esp8266.read();
            response += c;
          }
      }
    if (debug)
      {
        Serial.print(response);
      }
    return response;
  }
