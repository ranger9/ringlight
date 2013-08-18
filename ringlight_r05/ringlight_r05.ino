/********************************************************
** Programmable ringlight for close-up photography     **
** Uses Adafruit Industries Neopixel Ring and library  **
*********************************************************/


#include <Adafruit_NeoPixel.h>

#define PIN 6
#define SWITCH 7  //pin where we put the mode switch
int switchPosOld;  //used for storing switch position

//define red, green and blue values to use
//these are the default main-light values

int R=128;
int G=128;
int B=128;

//these are the default ambient-fill values
int Rr=0;
int Gg=0;
int Bb=0;

//width and position of the main light area
int lightWidth=1;
int lightPos = 0;

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

//ENCODER SETUP
//pins for encoder

int dpInEncoderA=4;
int dpInEncoderB=3;
int dpInEncoderPress=5;

int pulsesPerClick = 1;  //how many pulses do we get each time we click the knob
int encoderValue = 0;   //where we will store the value the encoder adjusts; doesn't have to be long because we reset it
int tempPulse = 0;  //variable for storing pulses, so we can account for multiple pulses
int currentValue = 0;  //current value we read from the encoder


int modeVal[3]={0,0,0};   //array in which we'll store the values; NOT SURE WE EVER USE THIS

int mode = 0;          //initialize mode value; changed by changeMode fn
int maxModes = 2;     //get count of array elements
int modeChange = 1;   //initialize change value; changed by encoder



void setup()
  {
    
      // configure the pins
    _ResetPins();
    
    //value for checking change in switch position
    switchPosOld = 0;
 
    
    //trap for excess value
    if (lightWidth > strip.numPixels())
      {
        lightWidth = strip.numPixels();
      }
      
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
    
  }

void loop()
  {
    
    //get the state of the mode selector switch
    Serial.println(encoderValue);
    
    //reset mode to 0 if switch position changes
    int switchPos = digitalRead(SWITCH);  //position of the mode selector
    if (switchPos != switchPosOld)
    {mode = 0;}
    switchPosOld = switchPos;

    
    //light all the pixels to the ambient value
    for(int i=0; i<strip.numPixels(); i++)
      {
        strip.setPixelColor(i,(strip.Color(Rr,Gg,int(Bb*0.6))));  //makes it a little warmer
      }
    
    //turn on the lights
    controlLight();
    strip.show();
    
    

    
    ReadEncoder();
    
    if ((mode==0) && (switchPos==1))  //position-setting mode
      {
      if (lightPos > 15)
        {
          lightPos = 0;
          encoderValue = 0;
        }
      else if (lightPos < 0)
        {
          lightPos = 15;
          encoderValue = 15;
        }
      else
        {
          lightPos = encoderValue;
        }
      }
      
    else if ((mode==1) && (switchPos==1))  //width-setting mode

      {       
       if (encoderValue >= 16)
       {
        //lightWidth = 16;
        encoderValue = 16;
       }
       else if (encoderValue < 1)
       {
         //lightWidth = 1;
         encoderValue = 1;
       }
       else
       {
         lightWidth = encoderValue;
       }

      }
      
    else if ((mode==2) && (switchPos==1))  //ambient-setting mode

      {      
      if (encoderValue > 255)
       {
        Rr = 255;
        Gg = 255;
        Bb = 255;
        encoderValue = 255;
       }
       else if (encoderValue < 0)
       {
         Rr = 0;
         Gg = 0;
         Bb = 0;
         encoderValue = 0;
       }
       else
       {
         Rr = encoderValue;
         Gg = encoderValue;
         Bb = encoderValue;
       }
      }
      
    else if ((mode==0) && (switchPos==0))  //R setting
    {
      //clean up values
      if (encoderValue > 255)
       {
        encoderValue = 255;
       }
       else if (encoderValue < 0)
       {
         encoderValue = 0;
       }

        R = encoderValue;

    }
    
        else if ((mode==1) && (switchPos==0))  //G setting
    {
      //clean up values
      if (encoderValue > 255)
       {
        encoderValue = 255;
       }
       else if (encoderValue < 0)
       {
         encoderValue = 0;
       }

        G = encoderValue;
    
    }
    
            else if ((mode==2) && (switchPos==0))  //B setting
    {
      //clean up values
      if (encoderValue > 255)
       {
        encoderValue = 255;
       }
       else if (encoderValue < 0)
       {
         encoderValue = 0;
       }

        B = encoderValue;
    
    }
 
  }



// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

