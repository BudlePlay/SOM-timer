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
enum som_flow {SET_TIME, TIMER, END};

LedControl lc = LedControl(12, 11, 10, 1);

// delay time between faces
unsigned long delaytime = 1000;

const int buttonPin = 6;


som_flow flow = SET_TIME;


int sec = 0;
int start_time = 0;

int counter =0;

void setup()
{
  Serial.begin(115200);
  lc.shutdown(0, false);
  lc.setIntensity(0, 0);
  lc.clearDisplay(0);

  pinMode(buttonPin, INPUT);

}

void set_time()
{
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

void down_time()
{
    sec = millis()/1000 - start_time;

 
  
    Serial.println(sec);

}

void end_time()
{
    Serial.println("END");
}


void loop()
{
  if (flow == SET_TIME)
  {
      set_time();
      int buttonState = digitalRead(buttonPin);

      if (buttonState == 0)
      {
          flow = TIMER;
          start_time = millis()/1000;
      }
  }
  else if (flow == TIMER)
  {
      down_time();
  }
  else if (flow == END)
  {
      end_time();
  }
  
 


  delay(100);
}
