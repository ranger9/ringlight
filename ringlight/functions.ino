
//turn all lights off and blink
void blinkMode()
  {
    for(int j=0; j<mode; j++)
    {
      for(int i=0; i<strip.numPixels(); i++)
        {
          strip.setPixelColor(i,(strip.Color(0,0,0)));
          strip.show();
          strip.setPixelColor(i,(strip.Color(128,0,0)));
          strip.show();
        }
     delay(100);
    }
  }

  
//expandable light at definable location
void controlLight()
  {
    
    int stripMax = strip.numPixels();  //function to get the highest allowed value
    //get the ending position
       
    int endPos = lightPos + lightWidth;
    
    //compensate for end positions greater than number of available pixels
    if (endPos > stripMax)
    {
      endPos = (endPos - stripMax);
    }
    
    //light pixels depending on whether they go past pixel 0 or not
    if (endPos > lightPos)    //case where end position does NOT exceed number of pixels
      {
      for(int i=lightPos; i<(lightPos + lightWidth); i++)
        {
          strip.setPixelColor(i,(strip.Color(R,G,B)));
        }
      }
      else if (lightPos > endPos)
      {
        for (int i=lightPos; i<(stripMax); i++)
         {
           strip.setPixelColor(i,(strip.Color(R,G,B)));
         }
         for (int i=0; i<(endPos+1); i++)
         {
           strip.setPixelColor(i,(strip.Color(R,G,B)));
         }
      }
    }
  


