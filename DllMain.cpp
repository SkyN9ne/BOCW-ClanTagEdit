//#include "pch.h" // Uncomment if you want to use Pre-Compiled Headers 
#include "stdio.h"
#include <windows.h>
#include <TlHelp32.h>
#include <psapi.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#pragma warning(disable : 4996)

using namespace std;


typedef const char* (__fastcall* tLiveStats_SetClanTag)(__int64 client, const char* clantag);

tLiveStats_SetClanTag LiveStats_SetClanTag;

uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"BlackOpsColdWar.exe");
__int64 TagOffset = 0x01; // OFFSET NEEDS TO BE UPDATED VIA THE SIG! See https://unknowncheats.me/forum/call-of-duty-black-ops-cold-war/514606-code-clan-tags-cold-war.html


void MainThread()
{
     while (true)
     {
         if (GetAsyncKeyState(VK_NUMPAD0) & 0x1U)
         {
             LiveStats_SetClanTag(0, "TAGHERE");
         }
     }
}


void Initialize()
{
    LiveStats_SetClanTag = (tLiveStats_SetClanTag)(TagOffset);
    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MainThread, NULL, NULL, NULL);
}


BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)

{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        Initialize();
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
