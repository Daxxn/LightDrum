# Notes and other things

* The Power Barrel Jacks need to be moved in from the edge. Theres only about 2mm from the edge of the board to the enclosure wall. OR try to find a higher current rated power connector.

* [Fixed] Add pullups to the barrel jack switches.

* [Fixed] The ICSP header needs to be moved away from the relays and any other obstructions.

* [Fixed] Still waiting on all the resistor/capacitor values for the filters.

* [Fixed] The rotary encoders need to be moved to the interface board.

* [Fixed] Look into a cable to connect the main and interface boards. The pinheader is realy hard to align and the flex during assembly is too high.

* Check the footprint and pin 1 indicator for the digital POT. Theres something wrong there.

* The brightness POT doesnt have an acceptable range. 10K is too high. The brightness goes from nothing to full only at the very end of travel.

* [Fixed] Move the XLR connector from the outside to the inside.

* [Fixed] add another MIDI connector for output communication.

* [Fixed] Move the RESET line resistor from the interface board to the main board.

* [Fixed] Move the electrolytic cap for the power supply to the top layer.

* [Fixed] Up the priority for the LED indicator power nets.

* [Fixed] Swap out the resonator for a crystal.

* [Good] TRIPLE check the symbol and footprint for the ATMEGA2560

* [Fixed] Waiting on the proper current sense resistors.

* [Fixed] Change the I2C address for Strip controller C. It was copied incorrectly from Fusion 360.