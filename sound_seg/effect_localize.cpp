/* Audio Library for Teensy 3.X
 * Copyright (c) 2014, Paul Stoffregen, paul@pjrc.com
 *
 * Development of this audio library was funded by PJRC.COM, LLC by sales of
 * Teensy and Audio Adaptor boards.  Please support PJRC's efforts to develop
 * open source software by purchasing Teensy or other PJRC products.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice, development funding notice, and this permission
 * notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <Arduino.h>
#include "effect_localize.h"
#include "xcorr.h"

void AudioEffectLocalize::update(void) {
#if defined(__ARM_ARCH_7EM__) // Teensy 3.5
	audio_block_t *blocka, *blockb;
	int16_t *pa, *pb;
//	uint32_t a12, a34; //, a56, a78;
//	uint32_t b12, b34; //, b56, b78;

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

	// uncomment lines 55 - 64 to perform cross-correlation

	// obtain the cross-correlation value
	float r_val = get_R_val(pa, pb, AUDIO_BLOCK_SAMPLES);

	// modify original sound blocks
	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
	pa[i] = pa[i] * r_val * r_val;
	pb[i] = pb[i] * r_val * r_val;
	// Serial.print(5000);
	// Serial.print(" ");
	// Serial.print(-5000);
	// Serial.print(" ");
	// Serial.println(pb[i]);
	}

	// uncomment following line to perform minimum amplitude filtering
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
