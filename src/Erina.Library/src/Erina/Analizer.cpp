#include <Erina\Analyzer.h>
#include <Erina\Helpers\ConsoleHelper.h>
#include <Erina\Helpers\MemoryHelper.h>
#include <iostream>
#include <iomanip>

typedef void(__cdecl* _sendPacket)(unsigned char* packet, unsigned short length);
_sendPacket originalSendPacket;

typedef void(__cdecl* _handlePacket)(unsigned short packetType, unsigned char* packet, unsigned short length);
_handlePacket oroginalHandlePacket;

void Analyzer::Initialize()
{
	DWORD sendPacket = 0x00549C10;
	DWORD handlePacket = 0x0054D560;

	originalSendPacket = (_sendPacket) MemoryHelper::Hook(sendPacket, 5, (DWORD)sendPacketHook);
	oroginalHandlePacket = (_handlePacket)MemoryHelper::Hook(handlePacket, 9, (DWORD)handlePacketHook);

	ConsoleHelper::CreateConsole();
}


void __cdecl  Analyzer::sendPacketHook(unsigned char* packet, unsigned short length)
{
	auto packetType = *reinterpret_cast<unsigned short*>(packet);
	std::cout << "C-S -> Packet(0x" << std::hex << packetType << "):";

	for (size_t i = 2; i < length; i++)
	{
		std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)packet[i] << " ";
	}
	std::cout << "\tLength: " << length << std::endl;
	
	originalSendPacket(packet, length);
}

void __cdecl Analyzer::handlePacketHook(unsigned short packetType, unsigned char* packet, unsigned short length)
{
	std::cout << "S-C -> Packet(0x" << std::hex << packetType << "):";

	for (size_t i = 0; i < length; i++)
	{
		std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)packet[i] << " ";
	}
	std::cout << "\tLength: " << length << std::endl;
	
	oroginalHandlePacket(packetType, packet, length);
}