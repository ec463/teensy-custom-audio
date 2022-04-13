#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "effect_localize.h"

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

// volume knob
#define CLK 37
#define DT  38

// mute switch
#define MUTE_PIN 0

// volume knob
int counter = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir ="";
unsigned long lastButtonPress = 0;

// mute switch
bool mute_flag = false;

void setup() {
  pinMode(MUTE_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  AudioMemory(512);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.micGain(40);
  sgtl5000_1.dacVolumeRamp();
  sgtl5000_1.dacVolumeRampDisable();

  pinMode(CLK,INPUT);
  pinMode(DT,INPUT);
  lastStateCLK = digitalRead(CLK);  
}

void loop() {

  // check if mute is on
  if (digitalRead(MUTE_PIN) == LOW) {
    mute_flag = true;
    sgtl5000_1.dacVolumeRampDisable();
    sgtl5000_1.volume(0);
    // Serial.println("Button is pressed!");
  } else {
    mute_flag = false;
    // Serial.println("Button not pressed...");
    sgtl5000_1.dacVolumeRamp();
    sgtl5000_1.volume(0.5);
  }

  // Read the current state of CLK
  currentStateCLK = digitalRead(CLK);
  
  // If last and current state of CLK are different, then pulse occurred
  // React to only 1 state change to avoid double count
  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){

    // If the DT state is different than the CLK state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(DT) != currentStateCLK) {
      if (counter > 0) {
        counter = counter - 1;
      }
      currentDir ="CCW";
      // Serial.println(counter/13.0);
      // Serial.println("CCW");
    } else {
      // Encoder is rotating CW so increment
      if (counter < 13){
        counter = counter + 1;
      }
      currentDir ="CW";
      // Serial.println(counter/13.0);
      // Serial.println("CW");
    }
  }

  // Remember last CLK state
  lastStateCLK = currentStateCLK;

  // only change volume if not muted
  if (!mute_flag) {
    float atten = counter/13.0;
    sgtl5000_1.volume(atten);
  }

  // Put in a slight delay to help debounce the reading
  delay(1);
}
