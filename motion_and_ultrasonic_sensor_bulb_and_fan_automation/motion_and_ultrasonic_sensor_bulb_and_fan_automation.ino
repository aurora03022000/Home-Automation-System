// defines arduino pins numbers
const int trigPin = 12;
const int echoPin = 11;

int RelayPin = 6;
int RelayPin1 = 7;

long duration;
int distance;

int loopOnce = false;

void setup() 
{
  Serial.begin(9600); // Starts the serial communication
  
  pinMode(2, INPUT);// Input from sensor
  
  pinMode(RelayPin, OUTPUT);
  pinMode(RelayPin1, OUTPUT);
  
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}


void loop() {

  if(loopOnce == true){
    int motion =digitalRead(2);

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance= duration*0.034/2;
  
    Serial.println(distance);
    Serial.println(motion);
    
    if(motion || distance <= 100){
      delay(2000);
  
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance= duration*0.034/2;
  
      motion =digitalRead(2);
      
      if(motion || distance <= 100){
          for(;;){
              digitalWrite(trigPin, LOW);
              delayMicroseconds(2);
              digitalWrite(trigPin, HIGH);
              delayMicroseconds(10);
              digitalWrite(trigPin, LOW);
              duration = pulseIn(echoPin, HIGH);
              distance= duration*0.034/2;
          
              motion =digitalRead(2);
  
              if(!motion && distance > 100){
                  delay(3000);
                  break;
              }
              
              digitalWrite(RelayPin, LOW);
              digitalWrite(RelayPin1, LOW);
          }
      }  
    }
  
    else{
        digitalWrite(RelayPin, HIGH);
        digitalWrite(RelayPin1, HIGH);
    }
  }

  loopOnce = true;
}
