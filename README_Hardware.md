# Hardware Operation Summary
## Guillermo Ao, Hannah Gold, Benjamin Li, Jonathan Ngo

# Normal Conditions 
The dual microphones, worn next to each of the user’s ears, provide bi-channel audio input to the device. These microphones are currently the Adafruit MAX4466 electret microphones, but can be changed in future iterations of the product. The processing unit is composed of a single Teensy 3.5 microcontroller and its accompanying custom PCB. This processor has been set up to perform sound segregation on the input using a low-frequency filter, amplitude minimization, and cross-correlation amplification. Finally, the segregated sound is relayed to the user through the left and right earbuds. Both contain the same sound, making the output mono-channel.

During the normal operation of the device, the device is powered on, the mute button is not pressed, and the volume knob sits at a comfortable level. In this configuration, the user can expect the device to perform the custom sound processing in real time. The sound sources in front of the user will sound distinct and amplified while those from the sides of the user will be attenuated. In normal operation mode, the user can turn the volume knob found on the casing of the device to adjust the gain of the sound output, allowing for louder or softer modes of operation.

The mute button found on the casing of the device can be pressed and held to temporarily pause the operation of the sound segregation algorithm. Until the button is released, the device sits idle. This mode was designed to not only prevent the algorithm from processing the user’s voice, but to also provide a smooth user experience when the user does not wish for the sound processing to occur.

When the battery of the device has run out, the user can simply recharge the battery by plugging in a mini-USB cable to the port on the case. 

# Abnormal Conditions
Abnormal operation may occur if there is no sound output or if the sound output is incoherent. In the following scenario, there may be two likely causes.
First is when the device runs out of battery. To solve this problem the user simply has to plug in a mini-USB cable to the corresponding port on the processing unit. Initializing the device is just turning it on.

Second, the issue could be due to a microphone malfunction, occurring if the user has already ruled out the case where the device’s ON indication is active, meaning the main electronic components are working, but no sound is coming out of the earbuds. The problem then would likely be with the input devices, which are the microphones. In that case, the OverEar device should be brought to a specialist to test out the microphone directly and fix the problem.

# Set Up
The hardware setup requires attaching the Teensy microcontroller to the audio shield through a series of pins, much like any other Arduino shield. The microphones will be connected to the respective ADC pins on the audio shield to receive the input signals and the earbuds will be connected to the 3.5mm jack on the audio shield for output. The audio shield uses the I2S interface to control the ADC and DAC connections. The software includes the self-developed sound-segregation algorithm which is in charge of processing the incoming noise signals. The code for the algorithm will already be pre-loaded onto the Teensy device. The general test will be to speak to the user in 3 different angles: first in front of the user at 0 degree, then at 90 degree offsets (directly left or directly right) and observe the attenuation of the output. The sound processing is almost immediate and will be relayed through the earbuds as live audio. 

# Setup Procedure
- Push the sound segregation algorithm code to the Teensy microcontroller.
- Plug in earbuds via audiojack.
- Clip the earbuds to the microphones on both left and right side.
- Flip the On/Off switch to the On position to start the OverEar device.

# Bill of materials used for this project:

# Equipment Description

- Teensy v3.5 Microcontroller 
  - Used to run the sound-segregation algorithm as well as process the input signals and output them.
- PCB
  - Custom design used to house the various electronic components and ensure a solid connection.
- Teensy Audio Shield
  - Hardware interface to simplify sound I/O connections to the Teensy microcontroller.
- MAX4466 Electret Microphone Amplifier
  - Used to record incoming bi-channel audio and provide pre-processing amplification
- Earbuds/Headphones
  - Used to output processed sound to the user and should have an audio jack to interface with the OverEar device.
- On/Off Switch
  - Used to turn the device on and off.
- Pushbutton Switch
  - Used as the self-mute button to stop audio processing when the user is talking.
- Rotary Encoder
  - Used to adjust the output volume depending on the scenario where the device is used.
- 1800 mAh Li-Po Battery & Adafruit Battery Management System
  - Used to power the device and allow for USB recharging through Mini USB.




