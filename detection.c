#include <SoftwareSerial.h> 
SoftwareSerial mySerial(3, 2);//Arduino's (rx,tx) 
int PIRsensor = 6; //PIR Sensor Pin 
int RedLED = 12; // Red LED pin 
int MotionRead, Motion_alert_val,recheckMotion; 
int pir_Status, Motion_sms_count=0, PIR_Motion_Status; 
void setup() 
{ 
 pinMode(PIRsensor, INPUT); 
 pinMode(RedLED, OUTPUT); 
 Serial.begin(9600); 
  
 mySerial.begin(9600); // Sim Baud rate 
 Serial.println("Initializing..."); 
 delay(1000); 
 mySerial.println("AT"); //Once the handshake test is successful, it will back to OK  updateSerial(); 
 digitalWrite(RedLED, LOW); // Red LED off 
} 
void loop() 
{ 
 CheckMotion(); 
 CheckNoMotion(); 
}  
void CheckMotion() 
 { 
 Serial.println("Motion Scan - ON"); 
 Motion_alert_val = ScanMotion(); 
 //D6 Pin becomes HIGH when Motion detected 
 if (Motion_alert_val == HIGH) 
 { 
 MotionAlert(); // Function to send SMS Alerts 
 } 
 } 
 int ScanMotion() 
 { 
 MotionRead = digitalRead(PIRsensor); // reads the Gas sensor D0 Pin  return MotionRead; // returns temperature value in degree celsius  } 
// Function to send SMS Alerts 
void MotionAlert() 
 { 
 digitalWrite(RedLED, HIGH); // Red LED on 
 delay(9000); 
  
 while (Motion_sms_count < 2) //Number of SMS Alerts to be sent  { 
 mySerial.println("AT+CMGF=1"); // Configuring TEXT mode 
 updateSerial(); 
 mySerial.println("AT+CMGS=\"+919597220383\"");//change ZZ with country code  and xxxxxxxxxxx with phone number to sms 
 updateSerial(); 
 mySerial.print("Alert Alert!! "); //text content 
 updateSerial(); 
 mySerial.write(26); 
  
 mySerial.println("AT+CMGF=1"); // Configuring TEXT mode 
 updateSerial(); 
 mySerial.println("AT+CMGS=\"+919597220383\"");//change ZZ with country code  and xxxxxxxxxxx with phone number to sms 
 updateSerial(); 
 mySerial.print("Alert Alert!! "); //text content 
 updateSerial(); 
 mySerial.write(26); 
  
 Motion_sms_count++; 
 } 
PIR_Motion_Status = 1; 
 Serial.println("DMS Lat 12° 55' 22.4940'' N DMS Long 80° 7' 38.8452'' E");  delay(100); 
 }  
void CheckNoMotion() 
 { 
 if (PIR_Motion_Status == 1) 
 { 
 recheckMotion = ScanMotion(); 
 if (recheckMotion == LOW) //D0 Pin becomes HIGH when No Gas  { 
 Serial.println("No Motion Detected"); 
 Motion_sms_count = 0; //Reset count for next alert triggers 
 PIR_Motion_Status = 0; 
 } 
 } 
 
void updateSerial() 
 { 
 delay(500); 
 while (Serial.available())  
 { 
 mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port 
  }
  while(mySerial.available())  
 { 
 Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port  } 
 } 
 }
  
