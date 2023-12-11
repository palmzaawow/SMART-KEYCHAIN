// Adafruit IO Publish Example
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"
#include "WiFi.h"
/************************ Example Starts Here *******************************/

// this int will hold the current count for our sketch
int count = 0;
#define TEST_SSID "pra too"

#define PIN_BTN 4 
// set up the 'counter' feed
AdafruitIO_Feed *counter = io.feed("led");

void setup() {

  // start the serial connection
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIN_BTN,INPUT);
  
  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {
 
  if ( digitalRead(PIN_BTN) == 1 ){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
      
  int ui = listNetworks();
  
    if(ui == 1){
      io.run();
      count = 1;
      counter->save(count);
      digitalWrite(LED_BUILTIN, LOW);
    }
    else{
      digitalWrite(LED_BUILTIN, HIGH);
      delay(250);
      digitalWrite(LED_BUILTIN, LOW);
      delay(250);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(250);
      digitalWrite(LED_BUILTIN, LOW);
    }
   

 
 }


  
 
}

int listNetworks() {
  // scan for nearby networks:
  Serial.println("** Scan Networks **");
  int numSsid = WiFi.scanNetworks();
  if (numSsid == -1) {
    Serial.println("Couldn't get a wifi connection");
    while (true);
  }

  // print the list of networks seen:


  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
  
      
     if( WiFi.SSID(thisNet) == TEST_SSID && WiFi.RSSI(thisNet) > -131 ){
      Serial.println("ON");
      digitalWrite(LED_BUILTIN, HIGH);
      return 1;
      break;
    }
    else{
      Serial.println("OFF");
      return 0;
    }
    
     
  }

}
