// linefollowing
void get_linefollowing_value(int values[], int s1, int s2, int s3, int s4, int s5) {
  values[0] = digitalRead(s1);
  values[1] = digitalRead(s2);
  values[2] = digitalRead(s3);
  values[3] = digitalRead(s4);
  values[4] = digitalRead(s5);
}