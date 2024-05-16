/*
 * ScreenControl.h
 *
 *  Created on: May 21, 2023
 *      Author: Daxxn
 */

#ifndef SRC_SCREENCONTROL_H_
#define SRC_SCREENCONTROL_H_

#include "Nextion.h"
#include "NextionDefs.h"
#include "Screen/Page.h"

#define AUDIO_SRC_BTN_XLR "XLR"
#define AUDIO_SRC_BTN_JACK "JACK"
#define AUDIO_SRC_BTN_BOTH "BOTH"

#define PAGE_COUNT 9
#define HOME_PAGE  1
#define NULL_PAGE 255

typedef enum
{
	SPLASH,
	MENU,
	RUN_PAGE,
	CHANNEL_VISUALS,
	CHANNEL_CONFIG,
	SETTINGS,
	AUDIO,
	COLORS,
	PATTERNS
} PageIDs;

typedef enum
{
	RUN_PAGE_BTN,
	CHANNELS_PAGE_BTN,
	CHANNEL_CFG_PAGE_BTN,
	AUDIO_PAGE_BTN,
	PATTERNS_PAGE_BTN,
	COLORS_PAGE_BTN,
	SETTINGS_PAGE_BTN,
} HomePageControls;

/*
 * Screen Controller used for this specific project.
 */
class ScreenControl
{
public:
	ScreenControl() {};
	virtual ~ScreenControl();

	HAL_StatusTypeDef Init(Nextion *nxt, Page *pages);

	void NavigateHorz(int8_t x);
	void NavigateVert(int8_t y);
	void Navigate(int8_t x, int8_t y);

	void ChangePageEvent(uint8_t pageID);
	void TouchEvent(uint8_t pageID, uint8_t compID, uint8_t event);

	void ChangeText(const char* objId, const char* text, uint8_t len);
	void ChangePage(uint8_t pageID);
	void ChangePage_Index(uint8_t index);
	void PageBack();
	void HomePage();

	bool CheckPage(uint8_t pageID);

	void Act();
private:
	Nextion *nxt;
	Page *pages;
	Page *currentPage;
	uint8_t prevPage = NULL_PAGE;
};

#endif /* SRC_SCREENCONTROL_H_ */
