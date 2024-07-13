// motor
void forward();
void backward();
void stop();
void left_turn();
void right_turn();

// sharp GP2Y0A02YK0F distance sensor
#include <GP2Y0A02YK0F.h>  // need to include(zip)
GP2Y0A02YK0F irSensor;

// ultrasonic
#include <Ultrasonic.h>  // need to include
Ultrasonic ultrasonic(7, 8);
bool get_distance();

// buzzer
#define BUZZER_PIN 4

// RFID rc522
#include <SPI.h>
#include <Wire.h>
#include <MFRC522.h>  // need to include
#define RST_PIN 48
#define SS_PIN 53
MFRC522 mfrc522;
char *reference;
byte uid1[4] = { 0xE0, 0xC7, 0xF7, 0x59 };
byte uid2[4] = { 0x80, 0x66, 0xFC, 0x59 };
byte uid3[4] = { 0xE0, 0x9F, 0xFF, 0x59 };
byte uid4[4] = { 0x60, 0x12, 0x00, 0x5A };
bool card_id_match();
void print_byte_array(byte *buffer, byte bufferSize);
int flag_card = 0;  // global variable

// LED
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif
#define LED_PIN1 22
#define LED_COUNT1 12
#define LED_PIN2 23
#define LED_COUNT2 12
#define LED_PIN3 24
#define LED_COUNT3 16
#define LED_PIN4 25
#define LED_COUNT4 8
#define LED_PIN5 26
#define LED_COUNT5 8
void led8(Adafruit_NeoPixel &strip);
void led12(Adafruit_NeoPixel &strip);
void led16(Adafruit_NeoPixel &strip);
void turnoff(Adafruit_NeoPixel &strip);

unsigned long startTime_led8_4 = millis();  // led8
unsigned long startTime_led8_5 = millis();
int light_up_Quantity_led8_4 = 0;
int light_up_Quantity_led8_5 = 0;
const long interval_led8 = 125;

unsigned long startTime_led16 = millis();  // led16
const long interval_led16 = 500;
bool status_led16 = false;
int brightness = 100;
Adafruit_NeoPixel strip1(LED_COUNT1, LED_PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(LED_COUNT2, LED_PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3(LED_COUNT3, LED_PIN3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4(LED_COUNT4, LED_PIN4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip5(LED_COUNT5, LED_PIN5, NEO_GRB + NEO_KHZ800);

// OLED screen ssd1306
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
char num_stack[4];  // memorize the input number
int output_num = 1;
void screen_output(char c);

// 4*4 Keypad
#include <Adafruit_Keypad.h>
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
byte rowPins[ROWS] = { 30, 31, 32, 33 };
byte colPins[COLS] = { 34, 35, 36, 37 };
Adafruit_Keypad customKeypad = Adafruit_Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
bool output_flag = false;  // finish inputting or not
char output_str;           // the input character

// trct5000 line following sensor
const int sensorPin1 = A1;
const int sensorPin2 = A2;
const int sensorPin3 = A3;
const int sensorPin4 = A4;
const int sensorPin5 = A5;
int speed = 200;
int front_line_values[5];
void get_linefollowing_value(int values[], int s1, int s2, int s3, int s4, int s5);