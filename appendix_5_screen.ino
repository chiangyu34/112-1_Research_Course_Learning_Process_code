// screen
void screen_output(char c) {
  if (c == '#') {  // equal to Enter
    for (int i = 1; i <= 3; i++) {
      Serial.println(num_stack[i]);
    }
    output_flag = true;
  } else {
    Serial.print("output_num: ");
    Serial.println(output_num);
    display.setTextSize(4);
    display.setTextColor(1);
    if (output_num == 1) {
      display.setCursor(20, 35);  // set position on the screen
      num_stack[1] = c;           // save the input number
    } else if (output_num == 2) {
      display.setCursor(45, 35);
      num_stack[2] = c;
    } else if (output_num == 3) {
      display.setCursor(70, 35);
      num_stack[3] = c;
    }
    display.print(c);
    display.display();
    output_num++;
    if (output_num > 3) {
      output_num = 1;
      display.clearDisplay();
    }
  }
}