//ENCODER ROUTINES

static void _ResetPins()
{
  // Rotary encoder input lines
  // Configure as input, turn on pullup resistors
  pinMode(dpInEncoderA, INPUT);
  digitalWrite(dpInEncoderA, HIGH);
  pinMode(dpInEncoderB, INPUT);
  digitalWrite(dpInEncoderB, HIGH);
  pinMode(dpInEncoderPress, INPUT);
  digitalWrite(dpInEncoderPress, HIGH);
  pinMode(SWITCH, INPUT);
  digitalWrite(SWITCH, HIGH);
}

void _lowlevel_ReadEncoder(int &rotate, int& press)
{
  rotate = (digitalRead(dpInEncoderB) * 2) + digitalRead(dpInEncoderA);
  press = digitalRead(dpInEncoderPress);
}

void ReadEncoder()

{
  int Position, Press;


  _ResetPins();
  _lowlevel_ReadEncoder(Position, Press);


  int Position2, Press2;
  do
  {
    _lowlevel_ReadEncoder(Position2, Press2);
  } 
  while ((Position2 == Position) && (Press2 == Press));
  if (Position2 != Position) {
    delay (30);    //fine-tune to get best debounce
    if (Position2 != Position)
    {
      // "Forward" is shown by the position going from (0 to 1) or (1 to 3)
      // or (3 to 2) or (2 to 0).  Anything else indicates that the user is
      // turning the device the other way.  Remember: this is Gray code, not
      // binary.

      int isFwd = ((Position == 0) && (Position2 == 1)) ||
        ((Position == 1) && (Position2 == 3)) ||
        ((Position == 3) && (Position2 == 2)) ||
        ((Position == 2) && (Position2 == 0));

      if (isFwd == 1) {
        if ((digitalRead(SWITCH) == 0) || ((digitalRead(SWITCH) == 1) && (mode == 2))) {
          encoderValue = encoderValue + (int(encoderValue * 0.2)) + 1;  //non-linear change
        }
        else
        {
          encoderValue = encoderValue + 1;
        }
      }

      else if (isFwd == 0)
      {
        if ((digitalRead(SWITCH) == 0) || ((digitalRead(SWITCH) == 1) && (mode == 2))) {
          encoderValue = encoderValue - (int(encoderValue * 0.2)) - 1;  //non-linear change
        }
        else {
          encoderValue = encoderValue - 1;
        }
        if ((mode != 0) && (encoderValue < 0)) {
          encoderValue = 0;
        }
      }
    }

    currentValue = (encoderValue/pulsesPerClick);    //account for multiple pulses
    modeVal[mode] = currentValue;

  }
  
  if (Press2 != Press) {
    delay(20 );                                      //crude debounce method
    if (Press2 != Press) {
    if (Press < Press2) {
      mode = mode + modeChange;
      blinkMode();
      if (mode > maxModes) {
        mode = 0;
        
       
      }
      //encoderValue = ((modeVal[mode]) * pulsesPerClick);  //load previous value as starting point
    }}
  }
  Position = Position2;
  Press = Press2;
  
}












