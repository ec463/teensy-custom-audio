#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "effect_localize.h"

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=211.1999969482422,235.1999969482422
AudioEffectLocalize      localize1;       //xy=431.20001220703125,236.1999969482422
AudioOutputI2S           i2s2;           //xy=841.2000122070312,228.1999969482422
AudioConnection          patchCord1(i2s1, 0, localize1, 0);
AudioConnection          patchCord2(i2s1, 1, localize1, 1);
AudioConnection          patchCord3(localize1, 0, i2s2, 0);
AudioConnection          patchCord4(localize1, 0, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=232,347
// GUItool: end automatically generated code

//const int myInput = AUDIO_INPUT_LINEIN;
//const int myInput = AUDIO_INPUT_MIC
void setup() {
  Serial.begin(9600);
  AudioMemory(512);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.micGain(40);
}

void loop() {

}
