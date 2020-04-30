#pragma once
#ifndef ERINA_PACKETS_CLIENT_LOGIN_REQUEST_PACKET_H
#define ERINA_PACKETS_CLIENT_LOGIN_REQUEST_PACKET_H

#include <Erina/Packets/PacketHandler.h>

#pragma pack(push, 1)
struct ClientLoginRequestStruct
{
	char UserName[19];
	char Unknow[13];
	char Password[16];
};
#pragma pack(pop)

class ClientLoginRequestPacket : public PacketDeserialize
{
public:
	ClientLoginRequestPacket(const char* name) : PacketDeserialize(name) { }
	void Deserialize(const Packet* packet);
};

#endif

