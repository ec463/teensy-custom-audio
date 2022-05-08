// Performs the sound-segregation effect for the OverEar device through cross-correlation attenuation and amplitude minimization.

#ifndef effect_localize_h_
#define effect_localize_h_
#include "Arduino.h"
#include "AudioStream.h"
#include "utility/dspinst.h"

class AudioEffectLocalize : public AudioStream
{
public:
	AudioEffectLocalize() : AudioStream(2, inputQueueArray) { }
	virtual void update(void);
private:
	audio_block_t *inputQueueArray[2];
};

#endif