/*
PIR HCSR501 
modified on 5 Feb 2019
by Saeed Hosseini @ ElectroPeak
https://electropeak.com/learn/guides/
*/
int ledPin = 13;                // LED 
int pirPin = 12;                 // PIR Out pin 
int pirStat = 0;                   // PIR status
void setup() {
 pinMode(ledPin, OUTPUT);     
 pinMode(pirPin, INPUT);     
 Serial.begin(9600);
}
void loop(){
 pirStat = digitalRead(pirPin); 
 if (pirStat == HIGH) {            // if motion detected
   digitalWrite(ledPin, HIGH);  // turn LED ON
   Serial.println(1);
 } 
 else {
   digitalWrite(ledPin, LOW); // turn LED OFF if we have no motion
   Serial.println(0);
 }
 delay(20);
} 
