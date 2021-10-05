#pragma once
#include "common.hpp"

#define CLEAR_CONSOLE() { logger::tools::clear(); }

namespace base
{
	class log
	{
	public:
		std::ofstream  m_Output;
		std::ifstream  m_Input;
	public:
		log() = default;
		~log() = default;

		void initialize();
		void shutdown();

		void Info(const char* format, ...);
		void Error(const char* format, ...);

		void Log(const char* type, const char* format, std::va_list args);

	};

	namespace logger::tools
	{
		static void clear() {
			COORD topLeft = { 0, 0 };
			HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
			CONSOLE_SCREEN_BUFFER_INFO screen;
			DWORD written;

			GetConsoleScreenBufferInfo(console, &screen);
			FillConsoleOutputCharacterA(
				console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
			);
			FillConsoleOutputAttribute(
				console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
				screen.dwSize.X * screen.dwSize.Y, topLeft, &written
			);
			SetConsoleCursorPosition(console, topLeft);
		}
	}

	inline std::unique_ptr<log> g_Logger;
}
