#include <memory>
#include <windows.h>

#include "detours\include\detours.h"
#include "include\Helpers.h"
#include "Controllers\Controller.h"
#include "include\Common.h"

/**
	The game's process. Used in ForceWriteData()
**/
const HANDLE process = GetCurrentProcess();

/**
	The chosen button prompts. Defaults to XBOX360
**/
int buttonPrompts = XBOX360;

/**
	If it's to fix the extended boost gauge. Defaults to false
**/
bool fixExtended = false;

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

void WriteData(int buttonType) {
	buttonPrompts = buttonType;
	ControllerInfo info = GetXncpNames(buttonType, fixExtended, !Common::IsModIdEnabled("HyperBE32.Score.Generations"));

	WriteButtons(info);

	// WriteUIGameplay
	ForceWriteData((void*)0x0168E328, info.ui, 11);

	ForceWriteData((void*)0x0168F1EC, "ui_gp_signul", 12);			// Used to add Unleashed's Ready GO animation without breaking missions.
	ForceWriteData((void*)0x0155E5D8, "ui_lockon_cursar", 16);		// Used to keep the original Generations lock on cursor in the Time Eater boss battle.
}

int GetButtonPrompts() {
	return buttonPrompts;
}

HOOK(int, __fastcall, CSonicContextSetSkill, 0xDFE980, void* context, void* Edx, uint32_t* a2)
{
	fixExtended = a2[1] & 0x8;

	WRITE_MEMORY(0x109D669, char*, GetXncpNames(GetButtonPrompts(), fixExtended, !Common::IsModIdEnabled("HyperBE32.Score.Generations") || Common::IsCurrentStageBossBattle()).ui);
	return originalCSonicContextSetSkill(context, Edx, a2);
}

HOOK(void, __fastcall, Stage_CHudSonicStageUpdate, 0x1098A50, void* This, void* Edx, float* dt)
{
	// Always clamp boost to 100
	*Common::GetPlayerBoost() = min(*Common::GetPlayerBoost(), 100.0f);

	originalStage_CHudSonicStageUpdate(This, Edx, dt);
}

void HookFunctions() {
	INSTALL_HOOK(CSonicContextSetSkill);
	INSTALL_HOOK(Stage_CHudSonicStageUpdate);
}