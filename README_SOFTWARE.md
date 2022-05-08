# Software Report
## Guillermo Ao, Hannah Gold, Benjamin Li, Jonathan Ngo


# Overview of Software Modules
- ```sound_seg.ino```
	- The main file that calls other functions. Initializes the Teensy and the connections to microphones and earbuds. Within the file are also functions that implement the On/Off, mute, and volume control.
	- The low frequency filter is implemented using a ladder filter for left and right inputs. Before the packet begins being processed by the other modules, low frequency sound is first eliminated. This processing is done to target the typical frequencies of background noise in a crowded room. The file uses existing libraries in the Teensy GUI to implement this. 
	- The initialization of the device from the GUI implementation is as follows:
		- Instantiate input and output objects representing the two microphones and two earbuds.
			- AudioInputI2S            i2s1;
			- AudioOutputI2S           i2s2;
		- Instantiate an AudioEffectLocalize class called localize1
			- AudioEffectLocalize      localize1;
		- Instantiate the two ladder filters used by implement low-frequency filtering
			- AudioFilterLadder        ladder1;
			- AudioFilterLadder        ladder2;
		- Establish connecting between objects
			- AudioConnection          patchCord1(i2s1, 0, ladder1, 0);
			- AudioConnection          patchCord2(i2s1, 1, ladder2, 0);
			- AudioConnection          patchCord3(ladder1, 0, localize1, 0);
			- AudioConnection          patchCord4(ladder2, 0, localize1, 1);
			- AudioConnection          patchCord5(localize1, 0, i2s2, 0);
			- AudioConnection          patchCord6(localize1, 0, i2s2, 1);
		- Instantiate the Audio Shield:
			- AudioControlSGTL5000     sgtl5000_1;

	- ```effect_localize.cpp```
		- ```AudioEffectLocalize()```: 
			- The sound localization function. Takes a packet of sound data and calculates the correlation coefficient with ```float get_R_val(int16_t *left_samples, int16_t *right_samples, int samples``` and multiplies each value with R squared. It then applies the absolute minimum function.
		- ```xcorr.h```
			- ```float get_R_val(int16_t *left_samples, int16_t *right_samples, int samples)```: The cross correlation function. Determines the cross correlation coefficient between the left and right samples for one packet. The cross correlation coefficient increases the more similar the left and right packets are to each other and approaches zero otherwise. They only become similar if the sound values in the packet mathematically have the similar values at the same index within the packet. Thus sound sources from the 0th azimuth will cause the cross correlation coefficient to increase. 
			- ```void isolate_minimum(int16_t *left_samples, int16_t *right_samples, int samples)```: The isolated minimum function. Determines the absolute minimum value between the left and right of each sample. As sound gets picked up by the left and right microphones, sources emitting from the 0th azimuth (directly in front of the user) contribute equally amplitude. As the source moves from away from the center, a bias towards one microphone occurs. This module is meant to help cut away everything except what comes from the 0th azimuth. 

# Dependency Flowchart

<p align="center">
   <img src="https://github.com/ec463/teensy-custom-audio/blob/master/resources/file_flowchart.drawio.png" alt="flowchart"/>
</p>

Figure 1: Block diagram reflecting the processing functions and the file structure for OverEar. 
# Developer/Build Tool Information
The complete dev/build tool information is as follows
- Teensy 3.5 with Teensy Audio Shield 3.X
- Arduino IDE version ```1.8.13```
- Teensyduino version ```1.56```
- Arduino Correlation Library version ```0.2.1```

# Project Software Stack Installation Guide

The complete installation of the project’s software stack is as follows
- Install the Arduino IDE version ```1.8.13``` from the following website
	- https://www.arduino.cc/en/software
- Install the Teensyduino add-on version ```1.56``` from the following website
	- https://www.pjrc.com/teensy/td_download.html
- Install the Arduino Correlation Library version ```0.2.1``` using the Arduino Library Manager
- Clone the Github repository
	- ```git clone https://github.com/ec463/teensy-custom-audio.git```
- Open the ```sound_seg.ino``` file in the Arduino IDE.
	- Compile and Upload to the Teensy

# Helpful Websites and Resources

https://www.pjrc.com/teensy/gui/ 

This website is useful for visualizing the flow of audio signals in a Teensy due to the Audio System Design Tool. It allows the user to choose options such as an input, output, mixer, effects/filters, and modes of analysis. If one clicks the “Export” button, they are able to generate code based on the block diagram they created. For our project, we use an input of I2S, a modified delay (which contains our algorithm), SGTL5000 control and an I2S output. 

- Module information
	- I2s2- receives 16-bit stereo audio using the I2S pins on the Teensy. This will stream both left and right signals. This same modu;e will be used again when outputting the audio data.
	- Delay- this module is repurposed and modified to be the algorithm that we use for sound localization purposes. This modified module is where the main part of the cross correlation in the algorithm occurs to the left and right audio signals, by using the queue to grab those signals and compare their similarities using the cross correlation coefficient.
	- SGTL5000 control- This control is used in the Teensy 3.X audio shield to control the timing of the overall system. This audio module has no inputs or outputs in the Audio System Design Tool. Separate I2S objects are used to send and receive audio data. I2S master mode objects must be used, because this object depends on Teensy to provide all I2S clocks. This object will control how the SGTL5000 will use the I2S audio streams.
		- Access to various properties of the SGTL5000 used in OverEar are as follows:
			- sgtl5000_1.enable();
				- Powers on the instantiation of SGTL5000 
    		- sgtl5000_1.volume(0.5);
    			- Sets the initial volume of the output post processing
    		- sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
    			- Initializes the input from the two microphones
  			- sgtl5000_1.micGain(40);
  				- Sets the initial gain for the amplitudes of incoming data from the two microphones
    		- sgtl5000_1.dacVolumeRamp();
    			- Enables the volume to increase at an exponential rate over a short period. This mode is better than linear since it avoids sudden and intense changes in volume. 
    		- sgtl5000_1.dacVolumeRampDisable();
    			- Disables the ramp. This property is used when the user decides to mute the device. 