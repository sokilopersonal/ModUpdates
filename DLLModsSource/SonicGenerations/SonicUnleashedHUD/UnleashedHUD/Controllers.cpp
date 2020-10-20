#include "pch.h"

#include <memory>
#include "Controllers.h"

bool getXncpNames(int buttonType, char* btn, char* win, char* pam, char* trick, char* how, char* bt)
{
	switch (buttonType) {
		case PS3:
			memcpy(btn, "ui_gp_btn_pside", 15);
			memcpy(win, "ui_psndow", 9);
			memcpy(pam, "ui_psm", 6);
			memcpy(trick, "ui_gp_psick", 11);
			memcpy(how, "ui_howps", 8);
			memcpy(bt, "ui_btn_pside", 12);
			break;
		case SWITCH:
			memcpy(btn, "ui_gp_btn_nswit", 15);
			memcpy(win, "ui_nswdow", 9);
			memcpy(pam, "ui_nsm", 6);
			memcpy(trick, "ui_gp_nswit", 11);
			memcpy(how, "ui_howns", 8);
			memcpy(bt, "ui_btn_nside", 12);
			break;
		case XBOX:
			// No change needed
			return false;
	}
	return true;
}

bool getUiGameplay(int buttonType, bool isFixExtended, char* dest) {
	switch (buttonType) {
		case XBOX:
			if (isFixExtended) 
				memcpy(dest, "ui_gameplaa", 11);
			else 
				return false;
			break;
		case PS3:
			if (isFixExtended) 
				memcpy(dest, "ui_gamepsaa", 11);
			else 
				memcpy(dest, "ui_gamepsay", 11);
			break;
		case SWITCH:
			if (isFixExtended) 
				memcpy(dest, "ui_gamensaa", 11);
			else 
				memcpy(dest, "ui_gamensay", 11);
	}
	return true;
}