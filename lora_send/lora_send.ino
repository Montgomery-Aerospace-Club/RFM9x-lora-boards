/*
  LoRa Demo 2 Sender
  lora-demo2-send.ino
  Use pushbutton to control LED on receiver
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

// Message counter
byte msgCount = 0;

// Pushbutton variables
int buttonPin = 8;
int sendButtonState;

void setup() {

  // Set pushbutton as input
  pinMode(buttonPin, INPUT_PULLUP);

  Serial.begin(9600);
  while (!Serial)
    ;

  // Setup LoRa module
  LoRa.setPins(csPin, resetPin, irqPin);

  Serial.println("LoRa Sender");

  // Start LoRa module at local frequency
  // 433E6 for Asia
  // 866E6 for Europe
  // 915E6 for North America

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1)
      ;
  }
  delay(1000);
}

void loop() {

  // Get pushbutton state
  sendButtonState = digitalRead(buttonPin);

  // Send packet if button pressed
  if (sendButtonState == LOW) {
    // Send packet
    LoRa.beginPacket();
    LoRa.print("button pressed");
    LoRa.endPacket();
    msgCount++;
    Serial.print("Sending packet: ");
    Serial.println(msgCount);
    delay(500);
  }
}