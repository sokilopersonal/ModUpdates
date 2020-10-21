#include <fstream>

#include "DataHelper.h"
#include "include\inipp.h"
#include "include\ModLoader.h"

#define INI_FILE "UnleashedHUD.ini"

// Defines if it's to fix the boost bar in extended mode (skill based)
bool isFixExtended = false;

int ReadIni()
{
	int buttons = 0;

	inipp::Ini<char> ini;
	std::ifstream file(INI_FILE);
	ini.parse(file);

	inipp::extract(ini.sections["HUD"]["fixBoostGaugeUp"], isFixExtended);
	inipp::extract(ini.sections["HUD"]["buttons"], buttons);

	file.close();
	return buttons;
}

extern "C" __declspec(dllexport) void Init(const char* path)
{
	int buttonType = ReadIni();
	WriteData(buttonType, isFixExtended);
}

__declspec(dllexport) ModInfo GensModInfo = { ModLoaderVer, GameVer };
