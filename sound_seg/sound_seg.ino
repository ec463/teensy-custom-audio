// Advanced Microcontroller-based Audio Workshop
//
// http://www.pjrc.com/store/audio_tutorial_kit.html
// https://hackaday.io/project/8292-microcontroller-audio-workshop-had-supercon-2015
// 
// Part 2-4: Using The Microphone


///////////////////////////////////
// copy the Design Tool code here
///////////////////////////////////

#include <Arduino.h>
#include <Audio.h>
#include "effect_localize.h"
#include "bichannel_audio_queue.h"
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

Bichannel_audio_queue *baq = new Bichannel_audio_queue(AUDIO_BLOCK_SAMPLES);

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=113,131
AudioOutputI2S           i2s2;           //xy=246,125
AudioEffectLocalize      localize1(baq, 0);         //xy=392.00000953674316,219.00000762939453
AudioEffectLocalize      localize2(baq, 1);         //xy=392.00000953674316,219.00000762939453
AudioConnection          patchCord1(i2s1, 0, localize1, 0);
AudioConnection          patchCord2(i2s1, 1, localize2, 0);
AudioConnection          patchCord3(localize1, 0, i2s2, 0);
AudioConnection          patchCord4(localize2, 0, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=232,347
// GUItool: end automatically generated code

//const int myInput = AUDIO_INPUT_LINEIN;
//const int myInput = AUDIO_INPUT_MIC
void setup() {
  Serial.begin(9600);
  AudioMemory(256);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.micGain(20);
  localize1.delay(0, 50);
  localize2.delay(0, 50);
  Serial.println(AUDIO_BLOCK_SAMPLES);  
}

void loop() {

}
