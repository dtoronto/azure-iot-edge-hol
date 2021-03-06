
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. 

// This code provides an MXChip (AZ3166) based solution for sending
// IoT data as part of Module 2 of the hands on lab found at
// https://github.com/toddwhitehead/azure-iot-edge-hol/tree/master/module2

#include "Arduino.h"
#include "Sensor.h"
#include "SystemTime.h"
#include "SystemTickCounter.h"

// Declare the variables for the various sensors on the board
DevI2C *ext_i2c;
HTS221Sensor *ht_sensor;
LPS22HBSensor *lp_sensor;
static RGB_LED rgbLed;


// Declare and initialize the sensor values we will need
float temperature = 50;
char temperatureUnit = 'C';
float humidity = 50;
char humidityUnit = '%';
float pressure = 55;
const char *pressureUnit = "psig";

// Variables to support the serial communication process
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void processSensors()
{
  try
  {
    // Read the current sensor values
    ht_sensor->reset();
    ht_sensor->getTemperature(&temperature);
    ht_sensor->getHumidity(&humidity);
    lp_sensor->getPressure(&pressure);

    //uncomment the line below if you want to convert from C to F
    //temperature = temperature*1.8 + 32;

    //Build the message to display on the OLED screen    
    char buff[128];
    sprintf(buff, "Environment \r\n Temp:%s%c    \r\n Humidity:%s%c  \r\n Atm: %s%s",f2s(temperature, 1),temperatureUnit, f2s(humidity, 1), humidityUnit, f2s(pressure,1), pressureUnit);
    Screen.print(buff);
    
    //output data as humidity,temperature to the serial port
    Serial.print(humidity);
    Serial.print(",");
    Serial.println(temperature);  //println includes linefeed
  }
  catch(int error)
  {
        // Turn the RBG Led to RED to indicate an error
        rgbLed.setColor(255,0,0);
  }
}

// Simple method to check for a command on the serial connection
void serialEvent() {
  // while there is data to read in the buffer, read it
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString.  if it's a newline, bail as that completes the message
    if (inChar == '\n') {
      stringComplete = true;
    }
    else
      inputString += inChar;
  }
}

void setup() {

  // Initialize the LEDs on the MXChip board
  pinMode(LED_WIFI, OUTPUT);
  pinMode(LED_AZURE, OUTPUT);
  pinMode(LED_USER, OUTPUT);
  rgbLed.turnOff();

  // Initialise the temperature and humidity sensor
  ext_i2c = new DevI2C(D14, D15);
  ht_sensor = new HTS221Sensor(*ext_i2c);
  ht_sensor->init(NULL);

  // Initialize the pressure sensor
  lp_sensor= new LPS22HBSensor(*ext_i2c);
  lp_sensor->init(NULL);

   // Adjust the baud rate of the serial connection to match the serial settings on the Pc side
   // Reduce to 9600 if seeing strange behaviour
   Serial.begin(115200);

  }  

void loop() {

    // Do the sensor tasks
    processSensors();

    // Check for an incoming command on the serial connection
    serialEvent();

     if (stringComplete) {
        // turn LED's on or off depending on command
        if(inputString == "OFF")
        {
            digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
            digitalWrite(LED_WIFI, LOW);
            digitalWrite(LED_AZURE, LOW);
            digitalWrite(LED_USER, LOW);
            rgbLed.turnOff();
        }
        if(inputString == "ON")
        {
          digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level);
          digitalWrite(LED_WIFI, HIGH);
          digitalWrite(LED_AZURE, HIGH);
          digitalWrite(LED_USER, HIGH);
          rgbLed.setColor(0,0,255);
        }
        // clear the string:
        inputString = "";
        stringComplete = false;
     }

    delay(2000);
}

