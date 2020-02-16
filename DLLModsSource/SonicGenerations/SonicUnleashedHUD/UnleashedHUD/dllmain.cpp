// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <memory>
#include <iostream>
#include "SonicGenerationsCodeLoader.h"
#include "inipp.h"
#include <fstream>

int mode = 0;	// Sets the HUD mode. This variable is updated inside the ReadIni() method.

extern "C"
{
	bool ReadIni()
	{
		bool isFixExtended = false;
		bool isPs3Buttons = false;

		inipp::Ini<char> ini;
		std::ifstream is("UnleashedHUD.ini");
		ini.parse(is);

		inipp::extract(ini.sections["HUD"]["fixBoostGaugeUp"], isFixExtended);
		inipp::extract(ini.sections["HUD"]["ps3Buttons"], isPs3Buttons);
		
		mode = isFixExtended * 2 + isPs3Buttons;
		
		is.close();
	}

	/*	
		Changes permissions of a memory zone, writes on it,
		and then restores the previous permissions.
	*/
	bool ForceWriteData(void* address, const char* data, size_t size) {
		DWORD old;
		bool result = false;

		result = VirtualProtect(address, size, PAGE_READWRITE, &old);
		WriteData(address, data, size);
		VirtualProtect(address, size, old, &old);
		return result;
	}

	// Changes general XNCP references to ones that use PlayStation buttons
	void WritePlaystationButtons() {
		const char* btn_ps = "ui_gp_btn_pside";
		const char* win_ps = "ui_psndow";
		const char* pam_ps = "ui_psm";
		const char* trick_ps = "ui_gp_psick";
		const char* how_ps = "ui_howps";
		const char* bt_ps = "ui_btn_pside";

		ForceWriteData((void*)0x015E3D80, btn_ps, 15);
		ForceWriteData((void*)0x016A6AA4, btn_ps, 15);
		
		ForceWriteData((void*)0x0168C928, win_ps, 9);
		ForceWriteData((void*)0x016A6B9C, win_ps, 9);
		
		ForceWriteData((void*)0x016A93CC, pam_ps, 6);
		
		ForceWriteData((void*)0x01579524, trick_ps, 11);
		ForceWriteData((void*)0x016D84F8, trick_ps, 11);
		
		ForceWriteData((void*)0x01688344, how_ps, 8);
		ForceWriteData((void*)0x016886A8, how_ps, 8);
		ForceWriteData((void*)0x01692BC4, how_ps, 8);

		ForceWriteData((void*)0x0154BCA4, bt_ps, 12);
		ForceWriteData((void*)0x0154CF74, bt_ps, 12);
		ForceWriteData((void*)0x0168BD44, bt_ps, 12);
	}

	void WriteUiGameplay(const char* ui) {
		ForceWriteData((void*)0x0168E328, ui, 11);		// Address of the ui_gameplay XNCP
	}

	__declspec(dllexport) void Init(const char* path)
	{
		// Used to fix the extended boost gauge size, aswell as add PlayStation buttom prompts.
		const char* uiname_ext = "ui_gameplaa";
		const char* uiname_ps = "ui_gamepsay";
		const char* uiname_psext = "ui_gamepsaa";
		
		// Used to add Unleashed's Ready GO animation without breaking missions.
		const char* gpsignal = "ui_gp_signul";
		// Used to keep the original Generations lock on cursor in the Time Eater boss battle.
		const char* lockon = "ui_lockon_cursar";
		
		ReadIni();

		switch (mode) {
		case 1:
			WriteUiGameplay(uiname_ps);
			WritePlaystationButtons();
			break;
		case 2:
			WriteUiGameplay(uiname_ext);
			break;
		case 3:
			WriteUiGameplay(uiname_psext);
			WritePlaystationButtons();
			break;
		}

		ForceWriteData((void*)0x0168F1EC, gpsignal, 12);	// Address of the ui_gp_signal XNCP that's used in gameplay, and not in missions
		ForceWriteData((void*)0x0155E5D8, lockon, 16);		// Address of the ui_lockon_cursur XNCP that's used in the Time Eater boss battle
	}

	__declspec(dllexport) ModInfo GensModInfo = { ModLoaderVer, GameVer };
}
