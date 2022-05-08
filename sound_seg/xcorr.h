// Library file for the sound-segregation effect.

#ifndef xcorr_h_
#define xcorr_h_

#include <Correlation.h>

// obtain the R value of the cross-correlation from the left and right audio samples
float get_R_val(int16_t *left_samples, int16_t *right_samples, int samples) {
    Correlation C(samples);

    for (int i = 0; i < samples; i++) {
        C.add(left_samples[i], right_samples[i]);
    }

    C.calculate();

    return C.getR();
}

// set the values of both left and right audio samples to the minimum of the two
void isolate_minimum(int16_t *left_samples, int16_t *right_samples, int samples) {
    for (int i = 0; i < samples; i++) {
        int16_t temp = min(left_samples[i], right_samples[i]);
        left_samples[i] = temp;
        right_samples[i] = temp;
    }
}

#endif
