#pragma once
#define XBOX 0
#define PS3 1
#define SWITCH 2

/**
	Gets XNCP names based on controller type. This must be changed when adding new controllers.
	Returns 'true' if the buttons types are different than vanilla (XBOX 360)
**/
bool getXncpNames(int buttonType, char* btn, char* win, char* pam, char* trick, char* how, char* bt);

/**
	Gets the name of the UI Gameplay XNCP based on controller type and fix. This must be changed when adding new controllers.
	Returns 'true' if the buttons types are different than vanilla (XBOX 360)
**/
bool getUiGameplay(int buttonType, bool isFixExtended, char* dest);