/*
 * NextionDefs.h
 *
 *  Created on: Feb 12, 2023
 *      Author: Daxxn
 */

#ifndef INC_NEXTIONDEFS_H_
#define INC_NEXTIONDEFS_H_

#define ASCII_NUMBERS 0x30

#define UART_TIMEOUT 100

#define NEXTION_BUFFER 16
#define NEXTION_REC_SIZE 8

// Nextion Defines
#define NXT_END "ÿÿÿ"

#define NXT_TEXT         116
#define NXT_SCROLLTEXT   55
#define NXT_NUMBER       54
#define NXT_XFLOAT       59
#define NXT_BUTTON       98
#define NXT_PROGRESS_BAR 106
#define NXT_IMAGE        112
#define NXT_CROP         113
#define NXT_HOT_SPOT     109
#define NXT_GAUGE        122
#define NXT_PAGE         121
#define NXT_WAVEFORM     0
#define NXT_SLIDER       1
#define NXT_DUAL_BUTTON  53
#define NXT_CHECKBOX     56
#define NXT_RADIO_BUTTON 57
#define NXT_QR_CODE      58

// Nextion Reveive Messages
#define NEX_RET_CMD_FINISHED                 (0x01)
#define NEX_RET_EVENT_LAUNCHED               (0x88)
#define NEX_RET_EVENT_UPGRADED               (0x89)
#define NEX_RET_EVENT_TOUCH_HEAD             (0x65)
#define NEX_RET_EVENT_POSITION_HEAD          (0x67)
#define NEX_RET_EVENT_SLEEP_POSITION_HEAD    (0x68)
#define NEX_RET_CURRENT_PAGE_ID_HEAD         (0x66)
#define NEX_RET_STRING_HEAD                  (0x70)
#define NEX_RET_NUMBER_HEAD                  (0x71)
#define NEX_RET_INVALID_CMD                  (0x00)
#define NEX_RET_INVALID_COMPONENT_ID         (0x02)
#define NEX_RET_INVALID_PAGE_ID              (0x03)
#define NEX_RET_INVALID_PICTURE_ID           (0x04)
#define NEX_RET_INVALID_FONT_ID              (0x05)
#define NEX_RET_INVALID_BAUD                 (0x11)
#define NEX_RET_INVALID_VARIABLE             (0x1A)
#define NEX_RET_INVALID_OPERATION            (0x1B)


#endif /* INC_NEXTIONDEFS_H_ */
