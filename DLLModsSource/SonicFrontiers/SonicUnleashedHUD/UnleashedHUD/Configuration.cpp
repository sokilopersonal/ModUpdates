#include "Configuration.h"
float Configuration::intensity = 50;

void Configuration::Read()
{
	INIReader reader(INI_FILE);

	intensity = reader.GetFloat("Graphics", "intensity", intensity);
}
