#include <Erina/Helpers/MemoryHelper.h>

void* MemoryHelper::Hook(DWORD address, size_t length, DWORD target)
{
	DWORD oldProtection = 0;

	if (!VirtualProtect(reinterpret_cast<void*>(address), length, PAGE_EXECUTE_READWRITE, &oldProtection))
	{
		return 0;
	}

	// Save the original code
	auto originalCode = new BYTE[length];
	memcpy(originalCode, reinterpret_cast<void*>(address), length);

	// Jumps to the target
	*reinterpret_cast<BYTE*>(address) = JMP;
	*reinterpret_cast<DWORD*>(address + 1) = static_cast<DWORD>(target - address - 5);

	if (length > 5)
	{
		for (size_t i = 0; i < length; i++)
		{
			*reinterpret_cast<BYTE*>(address + 5 + i) = NOP;
		}
	}

	VirtualProtect(reinterpret_cast<void*>(address), length, oldProtection, NULL);

	auto trampoline = VirtualAlloc(NULL, length + 5, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	memcpy(trampoline, originalCode, length);

	DWORD caveAddress = reinterpret_cast<DWORD>(trampoline);
	caveAddress += length;

	*reinterpret_cast<BYTE*>(caveAddress) = 0xE9;
	*reinterpret_cast<DWORD*>(caveAddress + 1) = static_cast<DWORD>((address + length) - caveAddress - 5);

	return trampoline;
}
