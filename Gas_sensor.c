// Gas sensor pins 
#define GAS_SENSOR_PIN A0 
// Float sensor pins 
#define FLOAT_SENSOR_PIN 2 
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
} 
void loop() { 
 // Read gas sensor value 
 int gasValue = analogRead(GAS_SENSOR_PIN); 
 // Check if gas value exceeds threshold 
 if (gasValue > GAS_THRESHOLD) { 
 Serial.println("WARNING: Gas detected in manhole!");  } 
 // Read float sensor value 
 int floatState = digitalRead(FLOAT_SENSOR_PIN); 
 // Check if water level exceeds threshold 
 if (floatState == LOW) { 
 Serial.println("WARNING: Water level in manhole is too high!");  } 
 // Delay for 1 second 
 delay(1000); 
} 
