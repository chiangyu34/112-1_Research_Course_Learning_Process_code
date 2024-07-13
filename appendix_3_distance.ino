// distance sensor functions
bool get_distance() {
  float distance1 = irSensor.getDistanceCentimeter();
  float distance2 = ultrasonic.read();
  Serial.print("\nDistance in CM(ir): ");
  Serial.println(distance1);
  Serial.print("\nDistance in cm(ultrasonic): ");
  Serial.print(distance2);
  if (distance1 >= 40 && distance2 >= 20) {
    turnoff(strip3);
    return false;
  } else {
    led16(strip3);
    return true;
  }
}