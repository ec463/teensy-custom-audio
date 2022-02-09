#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s2;           //xy=258,259
AudioFilterLadder        ladder1;        //xy=435,236
AudioFilterLadder        ladder2;        //xy=435,302
AudioMixer4              mixer1;         //xy=601,264
AudioOutputI2S           i2s1;           //xy=802,265
AudioConnection          patchCord1(i2s2, 0, ladder1, 0);
AudioConnection          patchCord2(i2s2, 1, ladder2, 0);
AudioConnection          patchCord3(ladder1, 0, mixer1, 0);
AudioConnection          patchCord4(ladder2, 0, mixer1, 1);
AudioConnection          patchCord5(mixer1, 0, i2s1, 0);
AudioConnection          patchCord6(mixer1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=594,403
// GUItool: end automatically generated code

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  AudioMemory(256);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.micGain(20);
}

void loop() {
  // put your main code here, to run repeatedly:

}
