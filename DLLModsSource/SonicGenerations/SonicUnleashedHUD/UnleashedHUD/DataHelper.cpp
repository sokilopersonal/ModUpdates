#include "pch.h"

#include <memory>
#include "Controllers.h"
#include "MemAccess.h"

/**
	Changes permissions of a memory zone, writes on it,
	and then restores the previous permissions.
**/
bool ForceWriteData(void* address, const char* data, size_t size) {
	DWORD old;
	bool result = false;

	result = VirtualProtect(address, size, PAGE_READWRITE, &old);
	WriteData(address, data, size);
	VirtualProtect(address, size, old, &old);
	return result;
}

void WriteButtons(int buttonType) {
	char btn[15];
	char win[9];
	char pam[6];
	char trick[11];
	char how[8];
	char bt[12];

	if (getXncpNames(buttonType, btn, win, pam, trick, how, bt)) {
		ForceWriteData((void*)0x015E3D80, btn, 15);
		ForceWriteData((void*)0x016A6AA4, btn, 15);

		ForceWriteData((void*)0x0168C928, win, 9);
		ForceWriteData((void*)0x016A6B9C, win, 9);

		ForceWriteData((void*)0x016A93CC, pam, 6);

		ForceWriteData((void*)0x01579524, trick, 11);
		ForceWriteData((void*)0x016D84F8, trick, 11);

		ForceWriteData((void*)0x01688344, how, 8);
		ForceWriteData((void*)0x016886A8, how, 8);
		ForceWriteData((void*)0x01692BC4, how, 8);

		ForceWriteData((void*)0x0154BCA4, bt, 12);
		ForceWriteData((void*)0x0154CF74, bt, 12);
		ForceWriteData((void*)0x0168BD44, bt, 12);
	}
}

void WriteUi(int buttonType, bool fixExtended) {
	// Used to add Unleashed's Ready GO animation without breaking missions.
	const char* gpsignal = "ui_gp_signul";
	// Used to keep the original Generations lock on cursor in the Time Eater boss battle.
	const char* lockon = "ui_lockon_cursar";

	ForceWriteData((void*)0x0168F1EC, gpsignal, 12);	// Address of the ui_gp_signal XNCP that's used in gameplay, and not in missions
	ForceWriteData((void*)0x0155E5D8, lockon, 16);		// Address of the ui_lockon_cursur XNCP that's used in the Time Eater boss battle

	char ui[11];
	if (getUiGameplay(buttonType, fixExtended, ui)) {
		ForceWriteData((void*)0x0168E328, ui, 11);
	}
}