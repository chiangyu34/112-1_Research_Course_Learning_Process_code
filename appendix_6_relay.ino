void setup() {
  pinMode(6, INPUT);
  pinMode(7, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  int value = digitalRead(6);
  if(value==HIGH){
    delay(1000);
    digitalWrite(7, LOW);
  }else{
    digitalWrite(7, HIGH);
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);
  }
}
