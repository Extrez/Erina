#pragma once
#ifndef ERINA_HELPERS_CONSOLE_H
#define ERINA_HELPERS_CONSOLE_H

#define JMP 0xE9
#define NOP 0x90

#include <Windows.h>

class ConsoleHelper
{
public:
	static void CreateConsole();
};

#endif