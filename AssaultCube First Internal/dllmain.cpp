// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <iostream>
#include <cstdio>
#include "offsets.h"

DWORD WINAPI HackThread(HMODULE hModule)
{
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    uintptr_t base = (uintptr_t)GetModuleHandle(L"ac_client.exe");
    uintptr_t localplayer = *(uintptr_t*)(base + localpl);
    bool bHealth = false, bAmmo = false, bSpeed = false, bNads = false;
    std::cout << "LESSAGOO" << std::endl;    
    while (!(GetAsyncKeyState(VK_DELETE) & 1))
    {
        if (GetAsyncKeyState(VK_F1) & 1)
        {
            bHealth = !bHealth;
        }
        if (GetAsyncKeyState(VK_F2) & 1)
        {
            bAmmo = !bAmmo;
        }
        if (GetAsyncKeyState(VK_F3) & 1)
        {
            bNads = !bNads;
        }
        if (GetAsyncKeyState(VK_F4) & 1)
        {
            bSpeed = !bSpeed;
        }
        if (bHealth)
        {
            *(int*)(localplayer + hp) = 1337;
        }
        if (bAmmo)
        {
            *(int*)(localplayer + ammo) = 1337;
        }
        if (bNads)
        {
            *(int*)(localplayer + grenade) = 1337;
        }
        if (bSpeed)
        {
            int* pSpeed = (int*)(localplayer + speed);
            if (*pSpeed == 1)
            {
                *pSpeed = 3;
            }
        }
    }
    system("cls");
    std::cout << "exiting thread, hack uninjecting" << std::endl;
    Sleep(3000);
    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        CloseHandle(CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)HackThread, hModule, NULL, NULL));
        break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

