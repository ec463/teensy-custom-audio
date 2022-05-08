// Performs the sound-segregation effect for the OverEar device through cross-correlation attenuation and amplitude minimization.

#include <Arduino.h>
#include "effect_localize.h"
#include "xcorr.h"

void AudioEffectLocalize::update(void) {
#if defined(__ARM_ARCH_7EM__) // Teensy 3.5
    audio_block_t *blocka, *blockb;
    int16_t *pa, *pb;

    blocka = receiveWritable(0);
    blockb = receiveWritable(1);

    if (!blocka) {
        if (blockb) release(blockb);
        return;
    }
    if (!blockb) {
        release(blocka);
        return;
    }

    pa = (int16_t *)(blocka->data);
    pb = (int16_t *)(blockb->data);

    // uncomment lines 30 - 41 to perform cross-correlation

    // obtain the cross-correlation value
    float r_val = get_R_val(pa, pb, AUDIO_BLOCK_SAMPLES);

    // modify original sound blocks
    for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
        pa[i] = pa[i] * r_val * r_val;
        pb[i] = pb[i] * r_val * r_val;
        // uncomment lines 37 - 41 to debug sound values
        // Serial.print(5000);
        // Serial.print(" ");
        // Serial.print(-5000);
        // Serial.print(" ");
        // Serial.println(pb[i]);
    }

    // uncomment the following line to perform minimum amplitude filtering
    isolate_minimum(pa, pb, AUDIO_BLOCK_SAMPLES);

    transmit(blocka);
    release(blocka);
    release(blockb);

#elif defined(KINETISL)
    audio_block_t *block;

    block = receiveReadOnly(0);
    if (block) release(block);
    block = receiveReadOnly(1);
    if (block) release(block);
#endif
}
