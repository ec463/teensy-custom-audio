# Teensy Sound Segregation
## Guillermo Ao, Hannah Gold, Benjamin Li, Jonathan Ngo

# Overview
This repository contains the code necessary to run the sound-segregation algorithm on the Teensy 3.5 microcontroller. While this code has been written to be easily adaptable to the modern Teensy microcontrollers, they have not been tested. In general, very few things need to be changed such as pin values for the various electronics.

# EC464 Deliverables Locations
Engineering README
 - ```https://github.com/ec463/teensy-custom-audio/blob/master/README.md```
 Hardware Report
 - ```https://github.com/ec463/teensy-custom-audio/blob/master/README_Hardware.md```
Software Report
 - ```https://github.com/ec463/teensy-custom-audio/blob/master/README_Software.md```
Copy of Previous Reports
 - ```https://github.com/ec463/teensy-custom-audio/blob/master/reports```
Schematic and PCB Designs
 - ```https://github.com/ec463/teensy-custom-audio/blob/master/resources/schematic```
 - ```https://github.com/ec463/teensy-custom-audio/blob/master/resources/pcb```

# Getting Started

You must have the Arduino IDE installed. This code has been tested on Arduino version ```1.8.13```, which can be obtained here https://www.arduino.cc/en/software.

The Teensy add-on for Arduino is needed as well and can be downloaded from https://www.pjrc.com/teensy/td_download.html. This will obtain all the Audio libraries and dependencies that come with the Teensy device.

One more library is needed and should be installed from the Arduino library catalog. This is:
 - ```Correlation``` version  ```0.2.1```

The code can be compiled and run by opening the ```sound_seg.ino``` file in the Arduino IDE after the Teensy has been connected to the computer and uploading it to the device.

# Development
The sound-segregation algorithm can be broken down into three distinct steps: a low-frequency filter, cross-correlation, and amplitude minimizations. The low-frequency filter was provided by the Teensy Audio library and can be found here: https://github.com/PaulStoffregen/Audio. A detailed explanation of what each step does can be found in the User Manual.

The newly written sound-segregation code is housed in the ```effect_localize``` ```.h``` and ```.cpp``` files. These files were written to be compatible with the other Teensy audio effects and thus follow their coding style. Any new effects or modifications should also be made accordingly.

```effect localize.cpp``` uses two library functions to perform sound-segregation. These are ```float get_R_val(int16_t *left_samples, int16_t *right_samples, int samples)```, which obtains the correlation coefficient of an audio sample, and ```void isolate_minimum(int16_t *left_samples, int16_t *right_samples, int samples)```, which equalizes the output of the processed sound.

This codebase is currently being ported to Python so that it can be compatible with Raspberry Pi models as well. A public repository with that code will be linked here in the future.

# Circuit Schematic
<p align="center">
   <img src="https://github.com/ec463/teensy-custom-audio/blob/master/resources/schematic/overear_schematic.png" alt="schematic"/>
</p>

# PCB Layout
<p align="center">
   <img src="https://github.com/ec463/teensy-custom-audio/blob/master/resources/pcb/overear_pcb.png" alt="PCB"/>
</p>
Circuitry needed to build the OverEar device can be found in the User Manual.

# Known Issues
 - At the default sound level, the processed audio is very robotic. Not a huge problem as the volume knob allows the sound level to be increased quite a lot before it reaches an uncomfortable level.

 - Plotting values on the Arduino Serial Monitor and Plotter causes the processed audio to have low clarity. This is a known issue with audio output and Arduino. Comment out any debugging code before use.

 - If only ```0``` is being printed while debugging sound values, that typically means that there is an issue with the microphones connected to the Teensy. Ensure that the microphones are working before code changes.