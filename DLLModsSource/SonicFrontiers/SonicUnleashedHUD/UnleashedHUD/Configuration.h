#pragma once

#define INI_FILE "SSGI.ini"

class Configuration
{
public:
	static void Read();

	/// <summary>
	/// Controls the intensity of the effect.
	/// </summary>
	static float intensity;
};

