#pragma once
#ifndef ERINA_HELPERS_MEMORY_H
#define ERINA_HELPERS_MEMORY_H

#define JMP 0xE9
#define NOP 0x90

#include <Windows.h>

class MemoryHelper
{
public:
	static void* Hook(DWORD address, size_t length, DWORD target);
};

#endif