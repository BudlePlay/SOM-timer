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

const int ALL_TIME = 100.0;
int set_time = 0;

int sec = 0;
int start_time = 0;

int lastVR = 0;

byte Apple [8]={B00011000,B00001000,B01110110,B11111111,B11111111,B11111111,B01111010,B00110100};

void setup()
{
  Serial.begin(115200);
  lc.shutdown(0, false);
  lc.setIntensity(0, 0);
  lc.clearDisplay(0);

  pinMode(buttonPin, INPUT);

}

void setup_time()
{
    int val = analogRead(A0);
    set_time = map(val, 0, 1023, -1, ALL_TIME + 1);    // 끝까지 돌리지 않아도 ALLTIME이 되게
    Serial.println(set_time);

    
    val = map(val, 0, 1023, -1, 37) * 2;
    
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
    sec = set_time - (millis()/1000 - start_time);

    float val = (float)sec/ALL_TIME * 64;
   
    Serial.println(val);
    Serial.println(sec);

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
  
//    Serial.println(sec);

    if (sec < 0) 
    {
       flow = END;
       lastVR = analogRead(A0);
    }
}

void end_time()
{
    Serial.println("END");

    int val = analogRead(A0);
    
    if (abs(lastVR - val) > 300)
    {
        flow = SET_TIME;
    }

      for(int i=0;i<8;i++) lc.setRow(0,i,Apple[i]);
      delay(1000);
      lc.clearDisplay(0);

}


void loop()
{
  if (flow == SET_TIME)
  {
      setup_time();
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
