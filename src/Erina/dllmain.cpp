// dllmain.cpp : Define el punto de entrada de la aplicación DLL.
#include "pch.h"
#include <iostream>
#include <string>
#include <thread>
#include <Erina/Helpers/MemoryHelper.h>

void CreateConsole()
{
    std::string text = std::string();

    AllocConsole();

    FILE* fDummy;
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONOUT$", "w", stdout);

    std::cout << "Hello world from Shaiya console" << std::endl;

    DWORD sendPacket = 0x00549C10;
    DWORD decryptPacket = 0x005451C0;

    auto helper = MemoryHelper();
    helper.Hook(sendPacket, 5, decryptPacket);
    helper.Hook(decryptPacket, 5, sendPacket);
}


BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved)
{
    std::thread newThread;
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        newThread = std::thread(CreateConsole);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
