#pragma once
#ifndef ERINA_PACKETS_SERVER_LOGIN_REQUEST_PACKET_H
#define ERINA_PACKETS_SERVER_LOGIN_REQUEST_PACKET_H
#include <Erina/Packets/PacketHandler.h>

#pragma pack(push, 1)
struct ServerLoginRequestStruct
{
	bool Error = 0;
	int UserId = 0;
	char SessionKey[16];
};
#pragma pack(pop)

class ServerLoginRequestPacket : public PacketDeserialize
{
public:
	ServerLoginRequestPacket(const char* name) : PacketDeserialize(name) { }
	void Deserialize(const Packet* packet);
};

#endif
