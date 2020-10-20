#include "pch.h"

#include <fstream>
#include "inipp.h"
#include "ModLoader.h"
#include "Controllers.h"
#include "DataHelper.h"

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
	WriteButtons(buttonType);
	WriteUi(buttonType, isFixExtended);
}

__declspec(dllexport) ModInfo GensModInfo = { ModLoaderVer, GameVer };
