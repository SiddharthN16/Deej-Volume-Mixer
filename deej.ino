const int NUM_SLIDERS = 3;
const int analogInputs[NUM_SLIDERS] = {A0, A1, A2};

int analogSliderValues[NUM_SLIDERS];
bool masterState, chromeState, discordState;

void setup()
{
  Serial.begin(9600);
  for (int i = 0; i < NUM_SLIDERS; i++)
  {
    pinMode(analogInputs[i], INPUT);
  }
  for (int i = 5; i <= 7; i++)
  {
    pinMode(i, OUTPUT);
  }
}

void loop()
{
  int masterBTN = digitalRead(2);
  int chromeBTN = digitalRead(3);
  int discordBTN = digitalRead(4);
  masterState = buttonState(masterBTN, masterState, 5);
  chromeState = buttonState(chromeBTN, chromeState, 6);
  discordState = buttonState(discordBTN, discordState, 7);
  updateSliderValues(masterState, chromeState, discordState);
  sendSliderValues(); // Actually send data (all the time)
  // printSliderValues(); // For debug
  delay(10);
}

bool buttonState(int btn, bool state, int led)
{
  if (btn == LOW)
  {
    delay(200);
    state = (state) ? false : true;
    digitalWrite(led, (state) ? HIGH : LOW);
  }
  return state;
}

void updateSliderValues(bool masterState, bool chromeState, bool discordState)
{
  if (masterState || chromeState || discordState)
  {
    if (masterState)
      setSliderValues(0, analogRead(analogInputs[1]), analogRead(analogInputs[2]));

    else if (chromeState)
      setSliderValues(analogRead(analogInputs[0]), 0, analogRead(analogInputs[2]));

    else if (discordState)
      setSliderValues(analogRead(analogInputs[0]), analogRead(analogInputs[1]), 0);
  }
  else
  {
    setSliderValues(analogRead(analogInputs[0]), analogRead(analogInputs[1]), analogRead(analogInputs[2]));
  }
}

void setSliderValues(int slider1, int slider2, int slider3)
{
  analogSliderValues[0] = slider1;
  analogSliderValues[1] = slider2;
  analogSliderValues[2] = slider3;
}

void sendSliderValues()
{
  String builtString = String("");

  for (int i = 0; i < NUM_SLIDERS; i++)
  {
    builtString += String((int)analogSliderValues[i]);

    if (i < NUM_SLIDERS - 1)
    {
      builtString += String("|");
    }
  }

  Serial.println(builtString);
}

// void printSliderValues()
// {
//   for (int i = 0; i < NUM_SLIDERS; i++)
//   {
//     String printedString = String("Slider #") + String(i + 1) + String(": ") + String(analogSliderValues[i]) + String(" mV");
//     Serial.write(printedString.c_str());

//     if (i < NUM_SLIDERS - 1)
//     {
//       Serial.write(" | ");
//     }
//     else
//     {
//       Serial.write("\n");
//     }
//   }
// }