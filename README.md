# LightDrum

### Have you ever wanted the drum set to be the loudest thing on stage? Well... this won't do that, but it will be extremely visible!

---


This project is a present for my dad first. The idea is to lay strings of LEDs on his drum set and control those strings with audio and MIDI signals.

> Current Revision: REV6
>
> All revisions before REV4 are early prototypes and are for archival. They are not fully functional.

---

[Docs](./Docs/)

## Features

### Output
- 8 Individual LED String Channels
- 1 Amp per Channel rating

## Input
- 1/8" jack audio
- XLR Balanced audio
- MIDI DIN

## PWM channels

The 8 individual RGB channels are controlled with 3 [PCA9634.](https://www.nxp.com/docs/en/data-sheet/PCA9634.pdf) Providing 8-bit PWM steps per channel with overall brightness and multiplexing.

## Power Management

Each channel includes current monitoring with a high-side power override. This is all to avoid shorts and over-current conditions on the high current 12V supply.

## Audio Processing

8 channel band-pass filtering with peak-detection circuitry to perform a basic Fourier Transform.

## User Interface

- 16x2 LCD screen
- Directional Buttons for menu navigation
- Bar Graph for display of audio levels
- 6 LEDs for quick status indication
- 2 Programmable Rotary Encoders