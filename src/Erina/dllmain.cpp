// dllmain.cpp : Define el punto de entrada de la aplicación DLL.
#include "pch.h"
#include <iostream>
#include <string>
#include <thread>

void CreateConsole()
{
    std::string text = std::string();

    AllocConsole();

    FILE* fDummy;
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONOUT$", "w", stdout);

    std::cout << "Hello world from Shaiya process" << std::endl;
    std::cout << "Write a message" << std::endl;
    std::cin >> text;

    std::cout << "You write the message: " << text << std::endl;
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
