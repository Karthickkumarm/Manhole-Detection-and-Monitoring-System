#define GAS_SENSOR_PIN A0 
// Float sensor pins 
#define FLOAT_SENSOR_PIN 2 
// PIR sensor pin 
#define PIR_SENSOR_PIN 3 
// Buzzer pin 
#define BUZZER_PIN 4 
#define GPS_RX_PIN 5 
#define GPS_TX_PIN 6 
// LCD pins 
#include <LiquidCrystal.h> 
#define LCD_RS 7 
#define LCD_EN 8 
#define LCD_D4 9 
#define LCD_D5 10 
#define LCD_D6 11 
#define LCD_D7 12 
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7); 
// Threshold values 
#define GAS_THRESHOLD 300 // ppm 
#define WATER_THRESHOLD 100 // mm 
void setup() { 
 // Initialize serial communication 
 Serial.begin(9600); 
 // Set gas sensor pin as input 
 pinMode(GAS_SENSOR_PIN, INPUT); 
 // Set float sensor pin as input 
 pinMode(FLOAT_SENSOR_PIN, INPUT_PULLUP); 
 // Set PIR sensor pin as input 
 pinMode(PIR_SENSOR_PIN, INPUT); 
 // Set buzzer pin as output 
 pinMode(BUZZER_PIN, OUTPUT); 
 // Initialize GPS module 
 Serial1.begin(9600); 
 delay(1000); 
 Serial1.print("$PMTK220,100*2F\r\n"); // Set NMEA output to 10Hz  delay(1000); 
 // Initialize LCD 
 lcd.begin(16, 2); 
} 
void loop() { 
 // Read gas sensor value 
 int gasValue = analogRead(GAS_SENSOR_PIN); 
 // Check if gas value exceeds threshold 
 if (gasValue > GAS_THRESHOLD) { 
 lcd.clear(); 
 lcd.print("WARNING: Gas detected!"); 
 Serial.println("WARNING: Gas detected in manhole!");  digitalWrite(BUZZER_PIN, HIGH); 
 delay(1000); 
 digitalWrite(BUZZER_PIN, LOW); 
 } 
 // Read float sensor value 
 int floatState = digitalRead(FLOAT_SENSOR_PIN); 
 // Check if water level exceeds threshold 
 if (floatState == LOW) { 
 lcd.clear(); 
 lcd.print("WARNING: Water level high!"); 
 Serial.println("WARNING: Water level in manhole is too high!");  digitalWrite(BUZZER_PIN, HIGH); 
 delay(1000); 
 digitalWrite(BUZZER_PIN, LOW); 
 } 
 // Read PIR sensor value 
 int pirState = digitalRead(PIR_SENSOR_PIN); 
 // Check if motion detected 
 if (pirState == HIGH) { 
 lcd.clear(); 
 lcd.print("ALERT: Motion detected!"); 
 Serial.println("ALERT: Motion detected in manhole!");  digitalWrite(BUZZER_PIN, HIGH); 
 delay(1000); 
 digitalWrite(BUZZER_PIN, LOW); 
 } 
 // Read GPS data 
 while (Serial1.available()) { 
 Serial.write(Serial1.read()); 
 } 
 // Delay for 1 second 
 delay(1000); 
} 
