const unsigned int TRIG_PIN = 8;
const unsigned int ECHO_PIN = 12;
const unsigned int BAUD_RATE = 9600;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(BAUD_RATE);
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);


  const unsigned long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration / 29 / 2;
  if (duration == 0) {
    //Serial.println(300);
    //Serial.println("Warning: no pulse from sensor");
    Serial.println("NaN");
  }
  else {
    // Serial.print("distance to nearest object:");
    Serial.println(distance);
    //Serial.println(" cm");
  }
  delay(100);
}
