# RGB_Audio_Visualizer

Summary

This project sets out to create a music visualizer using a programmable LED Light Strip.
A music visualizer is essentially a strip of groupings of lights that light up and change color/brightness depending on the beat and tune of the music.

Use Cases
- Night Clubs
- Christmas Trees
- Accessible Audio Experiences

Hardware Design
- Arduino Uno
- Sparkfun Sound Detector
- Jumper Wires
- Breadboard
- Decoupling Capacitor 1000uF/25V
- Push Button Switch
- Trimpot 10k Ohm
- WS2812B Light Strip

Using jumper cables and a breadboard a Sound Detector can be used to convert analog sound into digital input that can be read by the Arduino Uno. 
The same can be said for the trimpot.

![Simple Schematic](https://github.com/helloerickh/RGB_Audio_Visualizer/blob/main/Schematic.jpg)

Source Code

The FastLed library (https://github.com/FastLED/FastLED) is used to control individual LEDs on a light strip.

This code uses the readings (an integer from 0-1023) from the Envelope pin on the Sparkfun
Sound Recorder and maps them to a corresponding HSV Hue value (an integer from 0-255).
This allows music to generate different amplitudes and thus different colors.
A similar process is used to translate the readings from the trimpot device to adjust the HSV
Value value.
There are two animations:
  1. Solid_Animation
    a. Changes the entire LED strip to the calculated HSV color
  2. Middle_Out
    a. Propagates a single HSV color from the middle to the ends of the strip

To cycle between these two animations, a digital input is received from a button component.
This button uses a pullup resistor to transmit a “HIGH” value when unpressed. The pressing of
this button reads “LOW” which allows for the Change_Value() function to increment a variable to
be used as a switch case to select animations.
Originally the program was meant to have different palettes and a shuffle mode to select from
with an additional two buttons. These were not implemented due to time constraints.
This code utilizes the FastLED library to be able to address LEDs and assign them colors.
