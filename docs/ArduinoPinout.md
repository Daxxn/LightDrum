# Digital

### 1602 LCD Screen

|Pin | Net    | Description          |
| -- | ------ | -------------------- |
| 22 | LCD-D7 | 1602 Data Line 7     |
| 24 | LCD-D6 | 1602 Data Line 6     |
| 26 | LCD-D5 | 1602 Data Line 5     |
| 28 | LCD-D4 | 1602 Data Line 4     |
| 30 | LCD-D3 | 1602 Data Line 3     |
| 32 | LCD-D2 | 1602 Data Line 2     |
| 34 | LCD-D1 | 1602 Data Line 1     |
| 36 | LCD-D0 | 1602 Data Line 0     |
| 38 | LCD-EN | 1602 Enable          |
| 40 | LCD-RW | 1602 Read/Write      |
| 42 | LCD-RS | 1602 Register Select |

### Buttons

|Pin | Net    | Description      |
| -- | ------ | ---------------- |
| 23 | MODE   | Mode Switch      |
| 25 | ACT    | Activate Switch  |
| 27 | M-UP   | Menu Up Switch   |
| 23 | M-Down | Menu Down Switch |
| 41 | HOME   | Home Menu Switch |

### STP16 LED Driver

|Pin | Net     | Description       |
| -- | ------- | ----------------- |
| 39 | LED-SDI | Bar Serial Data   |
| 37 | LED-CLK | Bar Serial Clock  |
| 35 | LED-LE  | Bar Latch Enable  |
| 33 | LED-OE  | Bar Output Enable |

### STP16 Pinout

|Pin | Net  | Description             |
| -- | ---- | ----------------------- |
| 0  | BG-0 | Bar Braph 0             |
| 1  | BG-1 | Bar Braph 1             |
| 2  | BG-2 | Bar Braph 2             |
| 3  | BG-3 | Bar Braph 3             |
| 4  | BG-4 | Bar Braph 4             |
| 5  | BG-5 | Bar Braph 5             |
| 6  | BG-6 | Bar Braph 6             |
| 7  | BG-7 | Bar Braph 7             |
| 8  | BG-8 | Bar Braph 8             |
| 9  | BG-9 | Bar Braph 9             |
| 10 | D-4  | LED Indicator 1 (Right) |
| 11 | D-5  | LED Indicator 2         |
| 12 | D-6  | LED Indicator 3         |
| 13 | D-7  | LED Indicator 4         |
| 14 | D-8  | LED Indicator 5         |
| 15 | D-9  | LED Indicator 6 (Left)  |

### Rotary Encoders

|Pin | Net     | Description      |
| -- | ------- | ---------------- |
| 53 | ENC1-SW | Encoder 1 Switch |
| 51 | ENC1-A  | Encoder 1 Line A |
| 49 | ENC1-B  | Encoder 1 Line B |
| 47 | ENC2-SW | Encoder 2 Switch |
| 45 | ENC2-A  | Encoder 2 Line A |
| 43 | ENC2-B  | Encoder 2 Line B |

### Other Inputs

|Pin | Net     | Description               |
| -- | ------- | ------------------------- |
| 50 | PWR1-SW | Barrel Jack 1 Plug Switch |
| 52 | PWR2-SW | Barrel Jack 2 Plug Switch |
| 31 | HP-SW   | 1/8 Jack Plug Switch      |

### Serial

|  Pin   | Net  | Description     |
| ------ | ---- | --------------- |
| SP2-RX | MIDI | MIDI Input Line |

# PWM

|Pin | Net        | Description     |
| -- | ---------- | --------------- |
| 2  | LED3-G-SIG | Channel 3 Green |
| 4  | LED3-R-SIG | Channel 3 Red   |
| 6  | LED3-B-SIG | Channel 3 Blue  |
| 8  | LED4-G-SIG | Channel 4 Green |
| 10 | LED4-R-SIG | Channel 4 Red   |
| 12 | LED4-B-SIG | Channel 4 Blue  |
| 3  | LED7-G-SIG | Channel 7 Green |
| 5  | LED7-R-SIG | Channel 7 Red   |
| 7  | LED7-B-SIG | Channel 7 Blue  |
| 9  | LED8-G-SIG | Channel 8 Green |
| 11 | LED8-R-SIG | Channel 8 Red   |
| 13 | LED8-B-SIG | Channel 8 Blue  |

**Note:** The rest of the LED Channels are connected through the MAX3715 IO Expanders.

# Analog

### Audio Input

| Pin | Net     | Description                 |
| --- | ------- | --------------------------- |
| A0  | RAW-OUT | Post-Amp Audio Input Signal |

### Current Sense

| Pin | Net           | Description             |
| --- | ------------- | ----------------------- |
| A14 | LED1-CURR-OUT | Channel 1 Current Sense |
| A12 | LED2-CURR-OUT | Channel 2 Current Sense |
| A4  | LED3-CURR-OUT | Channel 3 Current Sense |
| A2  | LED4-CURR-OUT | Channel 4 Current Sense |
| A13 | LED5-CURR-OUT | Channel 5 Current Sense |
| A11 | LED6-CURR-OUT | Channel 6 Current Sense |
| A3  | LED7-CURR-OUT | Channel 7 Current Sense |
| A1  | LED8-CURR-OUT | Channel 8 Current Sense |

### Switch Indicators

| Pin | Net        | Description                    |
| --- | ---------- | ------------------------------ |
| A10 | MODE-IND   | Mode Switch Indicator LED      |
| A7  | ACT-IND    | Activate Switch Indicator LED  |
| A8  | HOME-IND   | Activate Switch Indicator LED  |
| A6  | M-UP-IND   | Menu Up Switch Indicator LED   |
| A9  | M-DOWN-IND | Menu Down Switch Indicator LED |