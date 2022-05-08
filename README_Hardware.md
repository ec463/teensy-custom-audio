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
<p align="center">
   <img src="https://github.com/ec463/teensy-custom-audio/blob/master/resources/hardware_figures/setup.png" alt="schematic"/>
</p>
Figure 1: Set up and process flow visual

# Setup Procedure
- Push the sound segregation algorithm code to the Teensy microcontroller.
- Plug in earbuds via audiojack.
- Clip the earbuds to the microphones on both left and right side.
- Flip the On/Off switch to the On position to start the OverEar device.

# Bill of materials used for this project:
<p align="center">
   <img src="https://github.com/ec463/teensy-custom-audio/blob/master/resources/hardware_figures/bom.png" alt="schematic"/>
</p>
Table 1: Bill of Materials

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

# Power specifications
Measurement of the Overear device produced an average electrical usage of 65 milliamps at 3.7 volts, for a total power consumption of 242 milliwatts. Accordingly, we settled on a 1800 mAh Lithium-Polymer battery, which connects to the device using terminal screws. This produces 28 hours of battery power. 

# Schematic & Diagrams 
<p align="center">
   <img src="https://github.com/ec463/teensy-custom-audio/blob/master/resources/hardware_figures/fullschematic.png" alt="schematic"/>
</p>
Figure 2: Full schematic
<p align="center">
   <img src="https://github.com/ec463/teensy-custom-audio/blob/master/resources/hardware_figures/pcb.png" alt="schematic"/>
</p>
Figure 3: Custom PCB design digital 
<p align="center">
   <img src="https://github.com/ec463/teensy-custom-audio/blob/master/resources/hardware_figures/realpcb.png" alt="schematic"/>
</p>
Figure 4: Printed circuit board + Teensy soldered together
3D models used for case to contain the electronic components:
<p align="center">
   <img src="https://github.com/ec463/teensy-custom-audio/blob/master/resources/hardware_figures/casetop.png" alt="schematic"/>
</p>
Figure 5: Main Case top cover
Dimensions: 110x60x11 mm (L x W x H)
<p align="center">
   <img src="https://github.com/ec463/teensy-custom-audio/blob/master/resources/hardware_figures/casebottom.png" alt="schematic"/>
</p>
Figure 6: Main case bottom (all electronic components are housed inside except microphones)
Dimensions: 110x60x28 mm (L x W x H)
<p align="center">
   <img src="https://github.com/ec463/teensy-custom-audio/blob/master/resources/hardware_figures/mic.png" alt="schematic"/>
</p>
Figure 7: Microphone case cover
Dimensions: 30x16x13.5 mm (L x W x H)
Two copies are made, one for the left and one for the right microphone.
<p align="center">
   <img src="https://github.com/ec463/teensy-custom-audio/blob/master/resources/hardware_figures/clip.png" alt="schematic"/>
</p>
Figure 8: Belt clip to connect with Main Case
Note: CAD files can be accessed through the Github repository

# System Enclosure 
Assembly process:

1. Solder the Teensy controller to the custom PCB and attach the Audio shield. The order of components from bottom to top is PCB, Teensy, and Audio shield.
2. Solder the wires of the button and volume controller to their respective pins. 
3. Solder wires to the microphone. Then put the wire through the braided cord protector. Once both microphones are shelved then put the cable through the correct hole in the Main case.
    1. Take the microphone wires and solder them to the Teensy pins.
4. Solder 2 short wires to the PCB and push them from inside out of the Main case to solder the switch. 
    1. After the switch is soldered to the PCB then push it inside the hole of the Main case. 
5. Solder the power adapter to the PCB.
6. After all electronic components are soldered to their respective pins, start organizing the elements inside the case. 
    1. The order should be: from bottom to top it is the PCB, Teensy, audio shield, power adapter, and battery pack. To the sides should be a switch and button and       the other side should be the volume controller.
    2. Use a glue gun to immobilize the components inside the Main Case or use super glue for a more effective option.
    3. Use super glue to connect the belt clip to the back of the Main case so the user can wear the device comfortably.
7. Finally cover the Main Case with its cover and case the microphones. After all electronic components have been assembled and the software uploaded to the Teensy, the user should be able to use the OverEar device right away. 

Inside view:
<p align="center">
   <img src="https://github.com/ec463/teensy-custom-audio/blob/master/resources/hardware_figures/inside.png" alt="schematic"/>
</p>
Figure 9: Top view of the inside of device
<p align="center">
   <img src="https://github.com/ec463/teensy-custom-audio/blob/master/resources/hardware_figures/insidescription.png" alt="schematic"/>
</p>
Figure 10: Item description of electronics inside the device

# Assembled system
<p align="center">
   <img src="https://github.com/ec463/teensy-custom-audio/blob/master/resources/hardware_figures/assembled.png" alt="schematic"/>
</p>
Figure 11: Full device overview

Once the device is completely assembled it will contain the following elements inside the yellow case: Teensy controller, Audio shield, PCB, power adapter/charger, battery pack, ON/OFF switch, mute button, volume controller, and wires. Outside the device will be 2 microphones with connection to the Teensy inside. The case has 1 usb port to interface the Teensy, 1 usb port to charge the battery, and 1 audio jack to connect headphones. 

Below are multiple images of the final device at different angles displaying all the elements that can be used:

<p align="center">
   <img src="https://github.com/ec463/teensy-custom-audio/blob/master/resources/hardware_figures/side1.png" alt="schematic"/>
</p>
Figure 12: Side view 1 of the device
<p align="center">
   <img src="https://github.com/ec463/teensy-custom-audio/blob/master/resources/hardware_figures/side2.png" alt="schematic"/>
</p>
Figure 13: Side view 2 of the device
<p align="center">
   <img src="https://github.com/ec463/teensy-custom-audio/blob/master/resources/hardware_figures/side3.png" alt="schematic"/>
</p>
Figure 14: Side view 3 of the device
<p align="center">
   <img src="https://github.com/ec463/teensy-custom-audio/blob/master/resources/hardware_figures/side4.png" alt="schematic"/>
</p>
Figure 15: Side view 4 of the device
<p align="center">
   <img src="https://github.com/ec463/teensy-custom-audio/blob/master/resources/hardware_figures/mics.png" alt="schematic"/>
</p>
Figure 16: Front and Side view of the microphones
Each microphone should be attached to the earbuds or headphones that the user will use when operating with the OverEar device.

