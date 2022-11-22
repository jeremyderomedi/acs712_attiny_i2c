#include <Arduino.h>

#include <Wire.h>

void setup()
{
    Wire.begin();       // join i2c bus (address optional for master)
    Serial.begin(9600); // start serial for output
}

void loop()
{
    Wire.requestFrom(0X01, 2); // request 2 bytes from peripheral device #0x01

    while (Wire.available())
    {                         // peripheral may send less than requested
        char c = Wire.read(); // receive a byte as character
        Serial.print(c);      // print the character
    }

    delay(500);
}