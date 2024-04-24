/*---------------------------------------------------------------------------------------------

  Open Sound Control (OSC) library for the ESP8266/ESP32

  Example for sending messages from the ESP8266/ESP32 to a remote computer
  The example is sending "hello, osc." to the address "/test".

  This example code is in the public domain.

--------------------------------------------------------------------------------------------- */
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif
#include <WiFiUdp.h>
#include <OSCMessage.h>

//sensor set up

const unsigned int TRIG_PIN = D6;
const unsigned int ECHO_PIN = D7;
const unsigned int BAUD_RATE = 9600;

//OSC communication set up



char ssid[] = "ccu";          // your network SSID (name)
char pass[] = "Code03084";    // your network password


WiFiUDP Udp;                               // A UDP instance to let us send and receive packets over UDP
const IPAddress outIp(172, 31, 21, 139);  // remote IP of your computer
const unsigned int outPort = 8000;         // remote port to receive OSC
const unsigned int localPort = 9000;       // local port to listen for OSC packets (actually not used for sending)

void setup() {
  Serial.begin(115200);

  //sensor set up

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  //OSC set up

  pinMode(LED_BUILTIN, OUTPUT);  // Initialize the LED_BUILTIN pin as an output

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".connecting");
  }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");
#ifdef ESP32
  Serial.println(localPort);
#else
  Serial.println(Udp.localPort());
#endif
}

void loop() {
  Serial.println(WiFi.localIP());

  // read sensor data
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
  } else {
    // Serial.print("distance to nearest object:");
    //Serial.println(distance);
    //Serial.println(" cm");
  }
  delay(100);

  // send osc message

  OSCMessage msg("/ESP_distance");
  msg.add(distance);
  Udp.beginPacket(outIp, outPort);
  msg.send(Udp);
  Udp.endPacket();
  msg.empty();

  //Serial.println("breakpoint");
  digitalWrite(LED_BUILTIN, 1);
  delay(500);
  digitalWrite(LED_BUILTIN, 0);
}
