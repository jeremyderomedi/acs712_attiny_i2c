#include <Arduino.h>
#include <TinyWire.h>
byte I2C_address = 0X01;
byte arrayOfByte[2] = {};
float multiplier = 0.185; // Sensibility in Voltios/Ampers for the 5A model
float moyenne = 0;

void convertIntToByte(int number)
{
  if (number > 1 << 16)
  {
    arrayOfByte[1] = 0xFF;
    arrayOfByte[2] = 0xFF;
  }
  else
  {
    arrayOfByte[0] = (number >> 8) & 0xFF;
    arrayOfByte[1] = number & 0xFF;
  }
}
void onI2CRequest()
{
  /*
   put code here to measure with acs
   */

  int milliAmpsMeasure = round(moyenne * 1000);
  convertIntToByte(milliAmpsMeasure);
  TinyWire.send(arrayOfByte[0]);
  TinyWire.send(arrayOfByte[1]);
}
void setup()
{
  TinyWire.begin(I2C_address);
  TinyWire.onRequest(onI2CRequest);
}
void loop()
{
  float valeur;

  int nbr_lectures = 50;
  for (int i = 0; i < nbr_lectures; i++)
  {
    float SensorRead = analogRead(A0) * (5.0 / 1023.0);
    valeur = (SensorRead - 2.5) / multiplier;
    moyenne = moyenne + float(valeur);
  }
  moyenne = moyenne / float(nbr_lectures);

  Serial.print("Current: ");
}
