#ifndef bichannel_audio_queue_h_
#define bichannel_audio_queue_h_

#include <Arduino.h>
#include <Correlation.h>

class Bichannel_audio_queue {
private:
  uint8_t samples;
  int16_t* left_samples;
  int16_t* right_samples;
public:
  Bichannel_audio_queue(uint8_t audio_samples) {
    samples = audio_samples;
    left_samples = (int16_t*) malloc(samples * sizeof(*left_samples));
    right_samples = (int16_t*) malloc(samples * sizeof(*right_samples));
    memset(left_samples, 0, samples * sizeof(*left_samples));
    memset(right_samples, 0, samples * sizeof(*right_samples));
  }

  void update_samples(int16_t* audio_block, int channel) {
    if (channel == 0) {
      memcpy(left_samples, audio_block, samples * sizeof(*left_samples));
    } else {
      memcpy(right_samples, audio_block, samples * sizeof(*right_samples));
    }
    for (int i = 0; i < 255; i++) {
      Serial.println(audio_block[i]);
    }
  }

  // perform cross correlation on left_samples and right_samples
  // returns the 
  float getCrossCorrelatationVal() {
    Correlation correlation;
    for (int i = 0; i < 128; i++) {
      correlation.add(left_samples[i], right_samples[i]);
    }

    correlation.calculate();
    float r_val = correlation.getR();

    return r_val;
  }
};

#endif
