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
    memset(left_samples, -1, samples * sizeof(*left_samples));
    memset(right_samples, -1, samples * sizeof(*right_samples));
  }

  void update_samples(int16_t* audio_block, int channel) {
    if (channel == 0) {
      memcpy(left_samples, audio_block, samples * sizeof(*left_samples));
      for (int i = 0; i < samples; i++) {
        if (left_samples[i] == 0) {
          left_samples[i] = 1;
        }
      }
    } else {
      memcpy(right_samples, audio_block, samples * sizeof(*right_samples));
      for (int i = 0; i < samples; i++) {
        if (right_samples[i] == 0) {
          right_samples[i] = 1;
        }
      }
    }
  }

  // perform cross correlation on left_samples and right_samples
  // returns the R value
  float get_cross_correlation_val(int channel) {
    Correlation C(samples);
    
    for (int i = 0; i < samples; i++){
      Serial.print(left_samples[i]+1);
      Serial.print(" ");
      Serial.println(right_samples[i]+1);
      C.add(left_samples[i] + 1, right_samples[i] + 1);
    }

    C.calculate();

    float r_val = C.getR();

    // prevent r_val from being 0
    if (r_val < 0.01 && r_val > -0.01) {
      r_val += 0.02;
    }

    // locally modify data samples
    for (int i = 0; i < samples; i++) {
      if (channel == 0) {
        left_samples[i] = left_samples[i] * r_val + 1;
      } else {
        right_samples[i] = right_samples[i] * r_val + 1;
      }
    }

    return r_val;
  }

//  void isolate_minimum(int channel) {
//    for (int i = 0; i < samples; i++) {
//      int16_t temp = min(left_samples[i], right_samples[i]);
//      if (channel == 0) {
//        left_samples[i] = temp;
//      } else {
//        right_samples[i] = temp;
//      }
//    }
//  }
  
};

#endif
