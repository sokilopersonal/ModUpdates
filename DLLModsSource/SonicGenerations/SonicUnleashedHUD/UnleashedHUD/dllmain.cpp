// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <memory>
#include <iostream>
#include "SonicGenerationsCodeLoader.h"
#include "inipp.h"
#include <fstream>

extern "C"
{
	bool isFixExtended()
	{
		bool fixExtended = false;
		inipp::Ini<char> ini;
		std::ifstream is("UnleashedHUD.ini");
		ini.parse(is);

		inipp::extract(ini.sections["HUD"]["fixBoostGaugeUp"], fixExtended);
		is.close();
		return fixExtended;
	}

	bool ForceWriteData(void* address, const char* data, size_t size) {
		DWORD old;
		bool result = false;

		result = VirtualProtect(address, size, PAGE_READWRITE, &old);
		WriteData(address, data, size);
		VirtualProtect(address, size, old, &old);
		return result;
	}

	__declspec(dllexport) void Init(const char* path)
	{
		const char* uiname = "ui_gameplaa";
		const char* gpsignal = "ui_gp_signul";
		const char* lockon = "ui_lockon_cursar";
		
		if(isFixExtended()) ForceWriteData((void*)0x0168E328, uiname, 11);	// Address of the ui_gameplay XNCP
		ForceWriteData((void*)0x0168F1EC, gpsignal, 12);					// Address of the ui_gp_signal XNCP that's used in gameplay, and not in missions
		ForceWriteData((void*)0x0155E5D8, lockon, 16);						// Address of the ui_lockon_cursur XNCP that's used in the Time Eater boss battle
	}

	__declspec(dllexport) ModInfo GensModInfo = { ModLoaderVer, GameVer };
}
