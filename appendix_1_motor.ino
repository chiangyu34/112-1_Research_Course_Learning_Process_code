// motor functions
void forward() {
  digitalWrite(12, HIGH);       // right wheel
  analogWrite(10, speed - 50);  // right wheel
  digitalWrite(13, HIGH);       // left wheel
  analogWrite(11, speed - 50);  // left wheel
}

void backward() {
  digitalWrite(12, LOW);        // left wheel
  analogWrite(10, speed - 50);  // left wheel
  digitalWrite(13, LOW);        // right wheel
  analogWrite(11, speed - 50);  // right wheel
}

void stop() {
  digitalWrite(12, HIGH);
  analogWrite(10, 0);
  digitalWrite(13, HIGH);
  analogWrite(11, 0);
}

void left_turn() {
  digitalWrite(12, LOW);
  analogWrite(10, speed);
  digitalWrite(13, HIGH);
  analogWrite(11, speed);
}

void right_turn() {
  digitalWrite(12, HIGH);
  analogWrite(10, speed);
  digitalWrite(13, LOW);
  analogWrite(11, speed);
}