#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "effect_localize.h"

#include <Bounce.h>
//How to log serial monitor information into a CSV File: https://www.circuitbasics.com/logging-arduino-data-to-files-on-a-computer/
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

void setup() {
  pinMode(0, INPUT_PULLUP);
  Serial.begin(9600);
  AudioMemory(512);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.micGain(40);
}

void loop() {
  if (digitalRead(0) == LOW) {
    sgtl5000_1.volume(0);
    //Serial.println("Button is pressed!");
  }else {
    //Serial.println("Button not pressed...");
    sgtl5000_1.volume(0.5);
  }
  //button0.update(); 
  //if (button0.fallingEdge()) {
   // sgtl5000_1.disable();//turn off the input when the button is pressed (it is hooked up to ground and will be pulled down).
  Serial.println("asdf");//}
  
}
