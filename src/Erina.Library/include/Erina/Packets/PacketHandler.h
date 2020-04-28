#pragma once
#ifndef ERINA_PACKETS_PACKETHANDLER_H
#define ERINA_PACKETS_PACKETHANDLER_H

#include <Erina\Packets\Packet.h>
#include <map>
#include <string>

class PacketDeserialize
{
public:
	PacketDeserialize(const char* name) : Name(name) { }

	const char* Name;
	virtual void Deserialize(const Packet* packet) = 0;
};

class PacketHandler
{
public:
	PacketHandler();

	bool HandleClientPacket(const Packet* packet);
	bool HandleServerPacket(const Packet* packet);

private:
	std::map<unsigned short, PacketDeserialize*> _clientPacketHandler;
	std::map<unsigned short, PacketDeserialize*> _serverPacketHandler;
};
#endif
