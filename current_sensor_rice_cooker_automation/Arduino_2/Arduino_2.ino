int RelayPin = 8;

int loopCounter = 0;

int total = 0;

String message;

void setup()
{  
  Serial.begin(9600);
  
  pinMode(RelayPin, OUTPUT);
  digitalWrite(RelayPin, LOW);
}

void loop()
{
  if (Serial.available()>0) { // Check if there is data available to read
      message = Serial.readStringUntil('%'); // Read the incoming message
      Serial.println(message);

      if(message == "1"){
           digitalWrite(RelayPin, LOW);
           Serial.println("Below");
      }

      else if(message == "2"){
           Serial.println("Above");
           delay(60000);
           digitalWrite(RelayPin, HIGH);
      }

      else if(message == "0"){
          Serial.println("No Readings");
      }
  }
  
}
