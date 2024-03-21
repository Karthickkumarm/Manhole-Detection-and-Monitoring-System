// Gas sensor pins 
#define GAS_SENSOR_PIN A0 
// Float sensor pins 
#define FLOAT_SENSOR_PIN 2 
// PIR sensor pins 
#define PIR_SENSOR_PIN 3 
// Buzzer pin 
#define BUZZER_PIN 4 
// LCD pins 
#define LCD_RS 5 
#define LCD_EN 6 
#define LCD_D4 7 
#define LCD_D5 8 
#define LCD_D6 9 
#define LCD_D7 10 
// GPS pins 
#define GPS_TX_PIN 11 
#define GPS_RX_PIN 12 
// WiFi module pins 
#define WIFI_TX_PIN 13 
#define WIFI_RX_PIN 14 
// Threshold values 
#define GAS_THRESHOLD 300 // ppm #define WATER_THRESHOLD 100 // mm 
// Initialize LCD 
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7); 
// Initialize WiFi module 
SoftwareSerial wifi(WIFI_RX_PIN, WIFI_TX_PIN); 
void setup() { 
 // Initialize serial communication 
 Serial.begin(9600); 
 // Initialize LCD 
 lcd.begin(16, 2); 
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
 Serial1.println("$PMTK220,1000*1F"); 
// Initialize WiFi module 
 wifi.begin(9600); 
 wifi.println("AT+RST"); 
 delay(1000); 
 wifi.println("AT+CWMODE=1"); 
 delay(1000); 
 wifi.println("AT+CWJAP=\"YOUR_WIFI_SSID\",\"YOUR_WIFI_PASSWORD\"");  delay(1000); 
} 
void loop() { 
 // Read gas sensor value 
 int gasValue = analogRead(GAS_SENSOR_PIN); 
 // Check if gas value exceeds threshold 
 if (gasValue > GAS_THRESHOLD) { 
 lcd.setCursor(0, 0); 
 lcd.print("WARNING: Gas detected"); 
 lcd.setCursor(0, 1); 
 lcd.print("in manhole!"); 
digitalWrite(BUZZ); 
} 
  
