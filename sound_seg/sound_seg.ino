#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "effect_localize.h"

#include <Bounce.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=211.1999969482422,235.1999969482422
AudioEffectLocalize      localize1;       //xy=431.20001220703125,236.1999969482422
AudioFilterLadder        ladder1;
AudioFilterLadder        ladder2;
AudioOutputI2S           i2s2;           //xy=841.2000122070312,228.1999969482422
AudioConnection          patchCord1(i2s1, 0, ladder1, 0);
AudioConnection          patchCord2(i2s1, 1, ladder2, 0);
AudioConnection          patchCord3(ladder1, 0, localize1, 0);
AudioConnection          patchCord4(ladder2, 0, localize1, 1);
AudioConnection          patchCord5(localize1, 0, i2s2, 0);
AudioConnection          patchCord6(localize1, 0, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=232,347
// GUItool: end automatically generated code

//const int myInput = AUDIO_INPUT_LINEIN;
//const int myInput = AUDIO_INPUT_MIC

//Bounce objects to read pushbuttons
Bounce button0 = Bounce(0, 15);

#define CLK 37
#define DT  38

int counter = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir ="";
unsigned long lastButtonPress = 0;

void setup() {
  pinMode(0, INPUT_PULLUP);
  Serial.begin(9600);
  AudioMemory(512);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.micGain(40);
  sgtl5000_1.dacVolumeRamp();
  sgtl5000_1.dacVolumeRampDisable();

  //localize1.delay(0, 125);

  pinMode(CLK,INPUT);
  pinMode(DT,INPUT);
  //pinMode(SW, INPUT_PULLUP);
  lastStateCLK = digitalRead(CLK);  
}

void loop() {
  if (digitalRead(0) == LOW) {
    sgtl5000_1.dacVolumeRampDisable();
    sgtl5000_1.volume(0);
    Serial.println("Button is pressed!");
  }else {
    Serial.println("Button not pressed...");
    sgtl5000_1.dacVolumeRamp();
    sgtl5000_1.volume(0.5);
  }
  button0.update(); 
  if (button0.fallingEdge()) {
    sgtl5000_1.disable();//turn off the input when the button is pressed (it is hooked up to ground and will be pulled down).
  }
 // do nothing

    // Read the current state of CLK
  currentStateCLK = digitalRead(CLK);
  //Serial.print(currentStateCLK);
  //Serial.print(digitalRead(DT));
  // If last and current state of CLK are different, then pulse occurred
  // React to only 1 state change to avoid double count
  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){

    // If the DT state is different than the CLK state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(DT) != currentStateCLK) {
      counter --;
      currentDir ="CCW";
    } else {
      // Encoder is rotating CW so increment
      counter ++;
      currentDir ="CW";
    }
    //Serial.print(digitalRead(DT));
    //Serial.print("Direction: ");
    //Serial.print(currentDir);
    //Serial.print(" | Counter: ");
    //Serial.println(counter);
  }

  // Remember last CLK state
  lastStateCLK = currentStateCLK;
  
  //Serial.print("analog is: ");
  float atten = counter/1024.0;
  sgtl5000_1.volume(atten);
  Serial.println(atten);

  // Read the button state
 // int btnState = digitalRead(SW);

  //If we detect LOW signal, button is pressed
  //if (btnState == LOW) {
    //if 50ms have passed since last LOW pulse, it means that the
    //button has been pressed, released and pressed again
   // if (millis() - lastButtonPress > 50) {
    //  Serial.println("Button pressed!");
   // }

    // Remember last button press event
   // lastButtonPress = millis();
  //}

  // Put in a slight delay to help debounce the reading
  delay(1);
}
