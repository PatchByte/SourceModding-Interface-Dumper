#include "cheat.hpp"
#include "Memory.h"

#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <psapi.h>
#include <TlHelp32.h>

namespace base
{



	void Cheat::initialize()
	{
		g_Logger = std::make_unique<log>();
		g_Cheat = std::make_unique<Cheat>();

		g_Logger->initialize();
		g_Cheat->init();

		while (g_Running)
		{
			if (GetKeyState(VK_END))
				g_Running = false;

			{
				#define XCMP(y) (strcmp(input, y) == 0)


				std::string _inputMsg = ""; g_Logger->m_Input >> _inputMsg; const char* input = _inputMsg.c_str();
				if (XCMP("unload"))
				{
					g_Running = false;
				}

				if (XCMP("help"))
				{
					g_Logger->Info("--- HELP ---");
					g_Logger->Info("findPossibleDlls\t:\tCustom Source Engine dll's that support interfaces!");
					g_Logger->Info("analyze\t:\tAnalyze's those dll's that we're found with the \"findPossibleDlls\" command!");
					g_Logger->Info("unload\t:\tUnloads this");
					g_Logger->Info("--- END  ---");
				}

				if (XCMP("findPossibleDlls"))
				{
					CLEAR_CONSOLE();
					HMODULE hMods[1024];
					HANDLE hProcess = GetCurrentProcess();
					DWORD cbNeeded;

					struct SearchResult
					{
						int totalModules = 0;
						int interfaceModules = 0;
					}; SearchResult g_SearchResult;

					g_Logger->Info("Following Modules have interface's!");

					if (K32EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
					{
						int i = 0;
						for (i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
						{
							const char* szModName[MAX_PATH];

							// Get the full path to the module's file.

							if (K32GetModuleFileNameExA(hProcess, hMods[i], (LPSTR)szModName,
								sizeof(szModName) / sizeof(char)))
							{
								g_SearchResult.totalModules++;
								
								if (GetProcAddress(hMods[i], "CreateInterface") != nullptr)
								{
									char* modName = strrchr((char* const)szModName, '\\') + 1;
									g_SearchResult.interfaceModules++;
									g_Logger->Info("%s", modName);
								}

								
								
								memset(szModName, 0, sizeof(szModName));
							}
						}
					}
					g_Logger->Info("--- END ---");
					g_Logger->Info("%i / %i modules are source engine modules!",  g_SearchResult.interfaceModules, g_SearchResult.totalModules);
				}

				if (XCMP("analyze"))
				{
					using DCreateInterface = void*(*)(const char* interfaceName, int* returnCode);

					g_Logger->Info("Please enter the dll's name.");
					std::string _temp2 = ""; g_Logger->m_Input >> _temp2; const char* dllName = _temp2.c_str();

					HMODULE modbase = GetModuleHandleA(dllName);

					if (modbase == 0)
					{
						g_Logger->Error("Module not found :(");
						goto CONTINUE_ERROR;

					}

					DCreateInterface ICreateInterface = (DCreateInterface)(GetProcAddress(modbase, "CreateInterface"));

					if (ICreateInterface == 0)
					{
						g_Logger->Error("CreateInterface not found :(");
						goto CONTINUE_ERROR;
					}

					MemoryHandle ICreateInterface_Handle = MemoryHandle(ICreateInterface);

					g_Logger->Info("--- BEGIN ---");
					g_Logger->Info("CI Address : %p", ICreateInterface);

					MemoryHandle backICreateInterface_Handle = ICreateInterface_Handle.Add(4).Add(1).Rip();

					g_Logger->Info("CI [2] Address : %p", backICreateInterface_Handle.As<void*>());

					// mov esi, [InterfaceMapPtr]
					// 8B 35 DE AD BE EF
					DWORD* InterfaceMapPtrValue = 0;
					{
						DWORD startPtr = (DWORD)backICreateInterface_Handle.As<void*>();
						InterfaceMapPtrValue = Signature("8B 35").ScanWithOL(startPtr - 1, 5).Add(2).As<DWORD*>();
					}

					g_Logger->Info("MAP Address : %p", InterfaceMapPtrValue);
					g_Logger->Info("--- Begin Interfaces ---");
					g_Logger->Info("Name | Construction Address (base+0x00000000)");
					struct MapEntry
					{
					public:
						using constrMethod = void* (*)();
					public:
						constrMethod interfaceConstructor;
						char* interfaceName;
						MapEntry* nextPtr;
					};

					MapEntry* list = *((MapEntry**)*InterfaceMapPtrValue);
					
					

					while (list)
					{
						g_Logger->Info("%s | 0x%p", list->interfaceName, ((DWORD)list->interfaceConstructor-(DWORD)(modbase)));
						list = list->nextPtr;
					}

					_temp2.clear();
				}

			CONTINUE_ERROR:
				{}

				#undef XCMP
			}
		}

		g_Cheat->shutdown();
		g_Logger->shutdown();
		g_Cheat.reset();
		g_Logger.reset();

		FreeLibraryAndExitThread(base::g_mModule, 0);
	}

	void Cheat::init()
	{
	}

	void Cheat::shutdown()
	{
	}

}