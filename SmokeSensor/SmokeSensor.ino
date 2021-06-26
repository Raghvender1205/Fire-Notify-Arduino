int LED = D4;
int Buzzer =  D0;
int Smoke_Detector = A0;

void setup() {
  pinMode(LED,OUTPUT);
  pinMode(Buzzer,OUTPUT);
  pinMode(Smoke_Detector,INPUT);  

}

void loop() {
  int threshold = 700;

  int Smoke_level = analogRead(Smoke_Detector);

  if(Smoke_level >= threshold)
  {
    digitalWrite(LED,HIGH);
    tone(Buzzer,1000,200);
    
  }
  else
  {
    digitalWrite(LED,LOW);
    noTone(Buzzer);
  }
  delay(500);

}
