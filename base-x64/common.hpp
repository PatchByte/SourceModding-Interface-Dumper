#pragma once

#pragma warning(disable : 4996)

#include <Windows.h>
#include <iostream>

#include <vadefs.h>
#include <cstdarg>
#include <vector>

#include <fstream>


namespace base
{
	inline HMODULE g_mModule = 0;
	inline bool g_Running = true;
}