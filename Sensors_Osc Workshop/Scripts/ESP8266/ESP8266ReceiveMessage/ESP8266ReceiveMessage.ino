
#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif
#include <WiFiUdp.h>

#include <OSCBoards.h>
#include <OSCBundle.h>
#include <OSCData.h>
#include <OSCMatch.h>
#include <OSCMessage.h>
#include <OSCTiming.h>
#include <SLIPEncodedSerial.h>



/*---------------------------------------------------------------------------------------------

  Open Sound Control (OSC) library for the ESP8266/ESP32

  Example for receiving open sound control (OSC) messages on the ESP8266/ESP32
  Send integers '0' or '1' to the address "/led" to turn on/off the built-in LED of the esp8266.

  This example code is in the public domain.

--------------------------------------------------------------------------------------------- */


char ssid[] = "ccu";          // your network SSID (name)
char pass[] = "Code03084";    // your network password


// A UDP instance to let us send and receive packets over UDP
WiFiUDP Udp;
const IPAddress outIp(172, 131, 21, 111);  // remote IP (not needed for receive)
const unsigned int outPort = 9999;         // remote port (not needed for receive)
const unsigned int localPort = 8888;       // local port to listen for UDP packets (here's where we send the packets)


OSCErrorCode error;
//unsigned float ledState = 0;  // LOW means led is *on*
float ledState = 0;  // LOW means led is *on*


#ifndef BUILTIN_LED
#ifdef LED_BUILTIN
#define BUILTIN_LED LED_BUILTIN
#else
#define BUILTIN_LED 13
#endif
#endif



void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(D2, OUTPUT);
  
  digitalWrite(BUILTIN_LED, ledState);  // turn *on* led

  Serial.begin(115200);
  //SLIPSerial.begin(115200);

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
  OSCMessage msg;

  int size = Udp.parsePacket();

  if (size > 0) {
    while (size--) {
      msg.fill(Udp.read());
    }
    if (!msg.hasError()) {
      ledState = msg.getFloat(0); //For TouchDesigner use the get flot to get the data and then transform it to the right format
      //Serial.println(ledState);

      msg.dispatch("/led", led);
      // figure out why dispatch does not work

    } else {
      error = msg.getError();
      Serial.print("error: ");
      Serial.println(error);
    }
  }

 
}

void led(OSCMessage &msg) {
  int ledStateINT = int(msg.getFloat(0)); //transform to the right format
  digitalWrite(BUILTIN_LED, ledState);
  digitalWrite(D2, ledState);
  Serial.print("/led: ");
  Serial.println(ledStateINT);
}
