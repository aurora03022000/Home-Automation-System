#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>

// WiFi credentials
const char* ssid = "Galaxy A01 Core9067";
const char* password = "samsung01";

// ThingSpeak channel details
unsigned long channelId = 2054224;
const char* apiKey = "BNR3SM6WI0Z25UQ1";

// Initialize WiFi client and ThingSpeak client
WiFiClient client;

String receivedValue;

void setup() {
  Serial.begin(115200);

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Con nected to WiFi!");

  // Initialize ThingSpeak client
  ThingSpeak.begin(client);
}

void loop() {

  if (Serial.available()) {
      receivedValue = Serial.readStringUntil('%');

      Serial.println("Recieved Value : " + receivedValue);

      int totalPowerIndex = receivedValue.indexOf(',');
      String totalPower = receivedValue.substring(0, totalPowerIndex);
      
      String removeTotalPower = removeWord(receivedValue, totalPower);
      String removeFirstCharacter = removeTotalPower.substring(1);
      int powerIndex = removeFirstCharacter.indexOf(',');
      String power = removeFirstCharacter.substring(0, powerIndex);
      
      String removePower = removeWord(removeFirstCharacter, power);
      String removeFirstCharacter1 = removePower.substring(1);
      int apparentPowerIndex = removeFirstCharacter1.indexOf(',');
      String apparentPower = removeFirstCharacter1.substring(0, apparentPowerIndex);

      String removeApparentPower = removeWord(removeFirstCharacter1, apparentPower);
      String irms = removeApparentPower.substring(1);
      

      Serial.println("Total Power : " + totalPower);
      Serial.println("Power : " + power);
      Serial.println("Apparent Power : " + apparentPower);
      Serial.println("Irms : " + irms);


       // set the fields with the values
      ThingSpeak.setField(1, totalPower);
      ThingSpeak.setField(2, power);
      ThingSpeak.setField(3, apparentPower);
      ThingSpeak.setField(4, irms);

      
      // write to the ThingSpeak channel
      int response = ThingSpeak.writeFields(channelId, apiKey);
  
      if(response == 200){
        Serial.println("Channel update successful.");
      }
      else{
        Serial.println("Problem updating channel. HTTP error code " + String(response));
      }

      delay(3000);

      // Wait 15 seconds before sending the next set of values
  }
 
}


String removeWord(String str, String word) {
  int index = str.indexOf(word);
  if (index == -1) return str;
  int len = word.length();
  return str.substring(0, index) + str.substring(index+len);
}
