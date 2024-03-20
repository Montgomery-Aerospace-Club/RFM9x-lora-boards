/*
  LoRa Demo 2 Receiver
  lora-demo2-receive.ino
  Receive LoRa signal to control LED
  Requires LoRa Library by Sandeep Mistry - https://github.com/sandeepmistry/arduino-LoRa
  
  DroneBot Workshop 2023
  https://dronebotworkshop.com
*/

// Include required libraries
#include <SPI.h>
#include <LoRa.h>

// Define the pins used by the LoRa module
const int csPin = 4;     // LoRa radio chip select
const int resetPin = 2;  // LoRa radio reset
const int irqPin = 3;    // Must be a hardware interrupt pin

// LED connection
const int ledPin = 5;

// Receive message variables
String contents = "";
String buttonPress = "button pressed";
bool rcvButtonState;


void setup() {

  // Set LED as output
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
  while (!Serial)
    ;

  // Setup LoRa module
  LoRa.setPins(csPin, resetPin, irqPin);

  Serial.println("LoRa Receiver");

  // Start LoRa module at local frequency
  // 433E6 for Asia
  // 866E6 for Europe
  // 915E6 for North America

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1)
      ;
  }
}

void loop() {

  // Try to parse packet
  int packetSize = LoRa.parsePacket();

  // Received a packet
  if (packetSize) {

    Serial.print("Received packet '");

    // Read packet
    while (LoRa.available()) {
      contents += (char)LoRa.read();
    }

    // Print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
    Serial.println(contents);

    // Toggle button state
    if (contents.equals(buttonPress)) {
      rcvButtonState = !rcvButtonState;
    }

    // Drive LED
    if (rcvButtonState == true) {
      digitalWrite(ledPin, HIGH);
      Serial.println("led on");
    } else {
      digitalWrite(ledPin, LOW);
      Serial.println("led off");
    }

    // Clear contents
    contents = "";
  }
}