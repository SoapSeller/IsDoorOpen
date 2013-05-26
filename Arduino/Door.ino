#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <EthernetServer.h>
#include <Dhcp.h>
#include <util.h>
#include <Dns.h>
#include <EthernetClient.h>

byte mac[] = { 0xDE, 0xAD, 0xB4, 0xEF, 0xFE, 0xEA };  
//byte ip[] = { 10.0.0.200 };
byte ip[] = { 10,0,10,100 };

EthernetServer server(23);

int echoPin = 8; 
int trigPin = 7; 
unsigned long pulseTime = 0; // Micro Seconds
unsigned long distance = 0; // Distance (cm)

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); // set init pin 3 as output
  pinMode(echoPin, INPUT); // set echo pin 2 as input
  Ethernet.begin(mac, ip);
  server.begin();
}

void loop() {
  EthernetClient client = server.available();
    
  digitalWrite(trigPin, HIGH);		// send 10 microsecond pulse
  delayMicroseconds(10);				// wait 10 microseconds before turning off
  digitalWrite(trigPin, LOW);			// stop sending the pulse
  pulseTime = pulseIn(echoPin, HIGH); // Look for a return pulse, it should be high    as the pulse goes lowgh-low
  distance = pulseTime/58;			// Distance = pulse time / 58 to convert to    cm.
  char msg[100];
  sprintf(msg, "%d", distance);
  Serial.print("Distance: ");
  Serial.println(msg);
  client.println(msg);
  
  delay(50);
  
  
  
}


