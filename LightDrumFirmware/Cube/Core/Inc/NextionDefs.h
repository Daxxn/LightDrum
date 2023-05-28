/*
 * NextionDefs.h
 *
 *  Created on: Feb 12, 2023
 *      Author: Daxxn
 */

#ifndef INC_NEXTIONDEFS_H_
#define INC_NEXTIONDEFS_H_

#define BAUD_RATE					9600
#define ASCII_NUMBERS				0x30
#define UART_TIMEOUT 				100
#define DISABLE_TOUCH 				0

#define NEXTION_BUFFER 				16
#define NEXTION_REC_SIZE 			32

// Nextion Defines
#define NXT_END 					"ÿÿÿ"
#define NXT_END_VAL					0xFF

// Nextion Colors
#define NEX_PAGE_BACKGROUND 		28802
#define NEX_SUBSECTION_BACKGROUND	35206
#define NEX_TEXT 					63422
#define NEX_BUTTON_NORMAL 			35008
#define NEX_BUTTON_BORDER 			26688
#define NEX_BUTTON_CLICK 			49408
#define NEX_PROGRESSBAR_NORMAL 		43426
#define NEX_PROGRESSBAR_HIGHLIGHT	56323
#define NEX_GRAPH_BACKGROUND 		22625
#define NEX_GRAPH_GRID 				41763
#define NEX_GRAPH_TRACE 			08404
#define NEX_SLIDER_LOW 				35008
#define NEX_SLIDER_CENTER 			56323
#define NEX_SLIDER_HIGH 			49408
#define NEX_SLIDER_HIGHLIGHT 		63304

// Nextion Reveive Messages
#define NEX_RET_CMD_FINISHED           		0x01
#define NEX_RET_EVENT_LAUNCHED              0x88
#define NEX_RET_EVENT_UPGRADED              0x89
#define NEX_RET_EVENT_TOUCH_HEAD            0x65
#define NEX_RET_CURRENT_PAGE_ID_HEAD        0x66
#define NEX_RET_EVENT_POSITION_HEAD      	0x67
#define NEX_RET_EVENT_SLEEP_POSITION_HEAD   0x68
#define NEX_RET_EVENT_MOVE_HEAD             0x69
#define NEX_RET_STRING_HEAD                 0x70
#define NEX_RET_NUMBER_HEAD                 0x71
#define NEX_RET_PRINT_HEAD                  0x99
#define NEX_RET_INVALID_CMD                 0x00
#define NEX_RET_INVALID_COMPONENT_ID        0x02
#define NEX_RET_INVALID_PAGE_ID             0x03
#define NEX_RET_INVALID_PICTURE_ID          0x04
#define NEX_RET_INVALID_FONT_ID             0x05
#define NEX_RET_INVALID_BAUD                0x11
#define NEX_RET_INVALID_VARIABLE            0x1A
#define NEX_RET_INVALID_OPERATION           0x1B

// Enums
typedef enum
{
	NXT_TEXT 			= 116,
	NXT_SCROLLTEXT 		= 55,
	NXT_NUMBER 			= 54,
	NXT_XFLOAT 			= 59,
	NXT_BUTTON 			= 98,
	NXT_PROGRESS_BAR 	= 106,
	NXT_IMAGE 			= 112,
	NXT_CROP 			= 113,
	NXT_HOT_SPOT 		= 109,
	NXT_GAUGE 			= 122,
	NXT_PAGE 			= 121,
	NXT_WAVEFORM 		= 0,
	NXT_SLIDER 			= 1,
	NXT_DUAL_BUTTON 	= 53,
	NXT_CHECKBOX 		= 56,
	NXT_RADIO_BUTTON 	= 57,
	NXT_QR_CODE 		= 58
} ControlTypeCode;

#endif /* INC_NEXTIONDEFS_H_ */
