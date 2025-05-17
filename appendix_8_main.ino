// main
void setup() {
  Serial.begin(9600);

  // motor pin: 10 ~ 13
  pinMode(12, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);

  // sharp distance sensor pin: A0
  irSensor.begin(A0);

  // ultrasonic pin: {trig: 7, echo: 8}


  // RC522 pin: {RST: 48, IRQ: 49(Null), MISO: 50, MOSI: 51, SCK: 52, (N)SS: 53}
  SPI.begin();
  mfrc522.PCD_Init(SS_PIN, RST_PIN);  // initialization MFRC522
  mfrc522.PCD_DumpVersionToSerial();  // show the version (ensure it can work normally)
  while (flag_card == 0) {
    if (card_id_match()) {
      flag_card = 1;
      led12(strip4);  // light up strip4
      led12(strip5);  // light up strip5
    } else {
      flag_card = 0;
    }
  }

  // LED pin: 22, 23, 24, 25, 26
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif
    strip1.begin();
    strip1.show();
    strip1.setBrightness(brightness);
    strip2.begin();
    strip2.show();
    strip2.setBrightness(brightness);
    strip3.begin();
    strip3.show();
    strip3.setBrightness(brightness);
    strip4.begin();  // left light
    strip4.show();
    strip4.setBrightness(brightness);
    strip5.begin();  // right light
    strip5.show();
    strip5.setBrightness(brightness);

  // OLED screen ssd1306 pin: {SDA: 20, SCL: 21}
  while (true) {
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
      Serial.println("SSD1306 connect failed");
    } else {
      display.setTextSize(2);
      display.setTextColor(1);
      display.clearDisplay();  // clear the screen
      display.print("Input the class...");
      display.display();
      delay(1000);
      break;
    }
  }

  // 4*4 Keypad pin: 30 ~ 37
  customKeypad.begin();
  keypadEvent e;
  while (true) {
    customKeypad.tick();
    while (customKeypad.available()) {
      e = customKeypad.read();
      output_str = (char)e.bit.KEY;
      Serial.println(output_str);
      if (e.bit.EVENT == KEY_JUST_RELEASED) {
        screen_output(output_str);
      }
      if (output_flag) {
        display.clearDisplay();
        display.display();
        Serial.println("finish inputting");
        display.setCursor(0, 20);
        display.setTextSize(2);
        display.print("Activate  in 5s...");
        display.display();
        delay(5000);
        display.clearDisplay();
        display.display();
        break;
      }
    }
    if (output_flag) {
      Serial.println("loop break");
      break;
    }
  }

  // line following sensor pin: A1~A5, A6~A10
  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);
  pinMode(sensorPin3, INPUT);
  pinMode(sensorPin4, INPUT);
  pinMode(sensorPin5, INPUT);
}

void loop() {
  if (flag_card) {
    if (get_distance()) {
      stop();
    } else {
      get_linefollowing_value(front_line_values, sensorPin1, sensorPin2, sensorPin3, sensorPin4, sensorPin5);
      Serial.print("line following value: ");
      for (int idx = 0; idx < 5; idx++) {
        Serial.print(front_line_values[idx]);
        Serial.print(" ");
      }
      Serial.println();

      if (front_line_values[2] == 0) {
        if (front_line_values[0] == 0 && front_line_values[1] == 0 && front_line_values[2] == 0 && front_line_values[3] == 0 && front_line_values[4] == 0) {  // all black
          stop();
          display.setCursor(0, 20);
          display.setTextSize(2);
          display.print("Arrive");
          display.display();
          delay(3000);
          flag_card = 0;
          while (flag_card == 0) {
            if (card_id_match()) {
              flag_card = 1;
              turnoff(strip1);
              turnoff(strip2);
              turnoff(strip3);
              turnoff(strip4);
              turnoff(strip5);
              display.clearDisplay();
              display.setCursor(0, 20);
              display.print("Power off in 5s...");
              display.display();
              delay(5000);
              display.clearDisplay();
              display.display();
              while (true) {}

            } else {
              flag_card = 0;
              tone(BUZZER_PIN, 587.30);
              delay(100);
              noTone(BUZZER_PIN);
            }
          }

        } else {
          forward();
        }
      } else {
        if (front_line_values[1] == 0 || front_line_values[3] == 1) {  // the left one touches the black line
          left_turn();
        } else if (front_line_values[1] == 1 || front_line_values[3] == 0) {  // the right one touches the black line
          right_turn();
        } else if (front_line_values[1] == 1 && front_line_values[2] == 1 && front_line_values[3] == 1) {  // all white
          backward();
          delay(1000);
        }
      }
    }
  }
}
