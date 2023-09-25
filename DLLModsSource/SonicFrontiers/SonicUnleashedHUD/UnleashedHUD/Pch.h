#pragma once

#define WIN32_LEAN_AND_MEAN

// Detours
#include <Windows.h>
#include "detours\include\detours.h"

// Standard library
#include <cstdint>
#include <cstdio>
#include <string>
#include <filesystem>

// Dependencies
#include "include\Helpers.h"
#include "include\INIReader.h"
#include "Configuration.h"
#include "DllMain.h"
#include "Main.h"