#include <Erina\Analyzer.h>
#include <Erina\Helpers\ConsoleHelper.h>
#include <Erina\Helpers\MemoryHelper.h>
#include <iostream>
#include <iomanip>
#include <Erina\Packets\Packet.h>
#include <Erina\Packets\PacketHandler.h>

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
	Packet* packet = new Packet(buff, length);

	PacketHandler* handler = new PacketHandler();
	if (!handler->HandleClientPacket(packet))
	{
		std::cout << "C -> S: Unknow opcode: 0x" << std::hex << std::setw(4) << std::setfill('0') << std::uppercase << packet->Type << std::endl;

		for (size_t i = 0; i < length - 2; i++)
		{
			std::cout << std::hex << std::setw(2) << std::setfill('0') << std::uppercase << (int)packet->Data[i] << " ";
		}

		std::cout << std::endl;
	}

	delete packet;
	
	originalSendPacket(buff, length);
}

void __cdecl Analyzer::handlePacketHook(unsigned short packetType, unsigned char* buff, unsigned short length)
{
	Packet* packet = new Packet((PacketType)packetType, buff, length);

	PacketHandler* handler = new PacketHandler();
	if (!handler->HandleServerPacket(packet))
	{
		std::cout << "S -> C: Unknow opcode: 0x" << std::hex << std::setw(4) << std::setfill('0') << std::uppercase << packet->Type << std::endl;

		for (size_t i = 0; i < length; i++)
		{
			std::cout << std::hex << std::setw(2) << std::setfill('0') << std::uppercase << (int)packet->Data[i] << " ";
		}

		std::cout << std::endl;
	}
	
	oroginalHandlePacket(packetType, buff, length);
}