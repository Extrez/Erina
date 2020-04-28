#include <Erina\Analyzer.h>
#include <Erina\Helpers\ConsoleHelper.h>
#include <Erina\Helpers\MemoryHelper.h>
#include <iostream>
#include <iomanip>
#include <Erina\Packets\Packet.h>

typedef void(__cdecl* _sendPacket)(unsigned char* buff, unsigned short length);
_sendPacket originalSendPacket;

typedef void(__cdecl* _handlePacket)(unsigned short packetType, unsigned char* buff, unsigned short length);
_handlePacket oroginalHandlePacket;

void Analyzer::Initialize()
{
	DWORD sendPacket = 0x00549C10;
	DWORD handlePacket = 0x0054D560;

	originalSendPacket = (_sendPacket) MemoryHelper::Hook(sendPacket, 5, (DWORD)sendPacketHook);
	oroginalHandlePacket = (_handlePacket)MemoryHelper::Hook(handlePacket, 9, (DWORD)handlePacketHook);

	ConsoleHelper::CreateConsole();
}


void __cdecl  Analyzer::sendPacketHook(unsigned char* buff, unsigned short length)
{
	Packet packet = Packet(buff, length);

	std::cout << "C -> S: Packet(0x" << std::hex << std::setw(4) << std::setfill('0') << std::uppercase << packet.Type;

	for (size_t i = 0; i < packet.Data.size(); i++)
	{
		std::cout << std::hex << std::setw(2) << std::setfill('0') << std::uppercase << (int)packet.Data[i] << " ";
	}

	std::cout << std::endl;
	
	originalSendPacket(buff, length);
}

void __cdecl Analyzer::handlePacketHook(unsigned short packetType, unsigned char* buff, unsigned short length)
{
	Packet packet = Packet((PacketType)packetType, buff, length);

	std::cout << "S -> C: Packet(0x" << std::hex << std::setw(4) << std::setfill('0') << std::uppercase << packet.Type << "): ";

	for (size_t i = 0; i < packet.Data.size(); i++)
	{
		std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)packet.Data[i] << " ";
	}
	std::cout << std::endl;
	
	oroginalHandlePacket(packetType, buff, length);
}