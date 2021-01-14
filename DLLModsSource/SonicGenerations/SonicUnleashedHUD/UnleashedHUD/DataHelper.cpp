#include <memory>
#include <windows.h>

#include "Controllers\Controller.h"

/**
	The game's process. Used in ForceWriteData()
**/
const HANDLE process = GetCurrentProcess();

/**
	Changes permissions of a memory zone, writes on it,
	and then restores the previous permissions.
**/
bool ForceWriteData(void* address, const char* data, size_t size) {
	DWORD old;
	bool result = false;

	result = VirtualProtect(address, size, PAGE_READWRITE, &old);
	WriteProcessMemory(process, address, data, size, nullptr);
	VirtualProtect(address, size, old, &old);
	return result;
}

void WriteButtons(ControllerInfo info) {
	ForceWriteData((void*)0x015E3D80, info.btn, 15);
	ForceWriteData((void*)0x016A6AA4, info.btn, 15);

	ForceWriteData((void*)0x0168C928, info.win, 9);
	ForceWriteData((void*)0x016A6B9C, info.win, 9);

	ForceWriteData((void*)0x016A93CC, info.pam, 6);
	ForceWriteData((void*)0x0168B294, info.pam, 6);
	ForceWriteData((void*)0x0168B3C8, info.pam, 6);
	ForceWriteData((void*)0x0168B780, info.pam, 6);

	ForceWriteData((void*)0x01579524, info.trick, 11);
	ForceWriteData((void*)0x016D84F8, info.trick, 11);

	ForceWriteData((void*)0x01688344, info.how, 8);
	ForceWriteData((void*)0x016886A8, info.how, 8);
	ForceWriteData((void*)0x01692BC4, info.how, 8);

	ForceWriteData((void*)0x0154BCA4, info.bt, 12);
	ForceWriteData((void*)0x0154CF74, info.bt, 12);
	ForceWriteData((void*)0x0168BD44, info.bt, 12);
}

void WriteData(int buttonType, bool fixExtended) {
	ControllerInfo info = GetXncpNames(buttonType, fixExtended);

	WriteButtons(info);

	// WriteUIGameplay
	ForceWriteData((void*)0x0168E328, info.ui, 11);

	ForceWriteData((void*)0x0168F1EC, "ui_gp_signul", 12);			// Used to add Unleashed's Ready GO animation without breaking missions.
	ForceWriteData((void*)0x0155E5D8, "ui_lockon_cursar", 16);		// Used to keep the original Generations lock on cursor in the Time Eater boss battle.
}