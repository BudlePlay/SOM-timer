/*
  Created by Rui Santos

  All the resources for this project:
  https://randomnerdtutorials.com/
*/

#include "LedControl.h"
#include "binary.h"

/*
  DIN connects to pin 12
  CLK connects to pin 11
  CS connects to pin 10
*/
LedControl lc = LedControl(12, 11, 10, 1);

// delay time between faces
unsigned long delaytime = 1000;

int Cat[8] = {B10001000, B11111000, B10101000, B01110001, B00100001, B01111001, B01111101, B10111110 };
byte Apple [8] = {B00011000, B00001000, B01110110, B11111111, B11111111, B11111111, B01111010, B00110100};

const int buttonPin = 6;

int buttonState = 0;         // variable for reading the pushbutton status


void setup() 
{
  Serial.begin(115200);
  lc.shutdown(0, false);
  lc.setIntensity(0, 0);
  lc.clearDisplay(0);
  
  pinMode(buttonPin, INPUT);

}



void loop()
{

    buttonState = digitalRead(buttonPin);
    Serial.println(buttonState);

  int val = analogRead(A0);
  val = map(val, 0, 1023, -1, 17) * 4;

  //  Serial.println(val);
  for (int r = 0; r < 8; r++) 
  {
    for (int c = 0; c < 8; c++) 
    {


      if (r * 8 + c > val) 
      {
        lc.setLed(0, r, c, LOW);
      }
      else 
      {
        lc.setLed(0, r, c, HIGH);
      } 
    }
  }


}
