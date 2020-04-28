#pragma once
#ifndef ERINA_PACKETS_CLIENT_LOGIN_REQUEST_PACKET_H
#define ERINA_PACKETS_CLIENT_LOGIN_REQUEST_PACKET_H

#include <Erina/Packets/PacketHandler.h>

class LoginRequestPacket : public PacketDeserialize
{
public:
	LoginRequestPacket(const char* name) : PacketDeserialize(name) { }
	void Deserialize(const Packet* packet);
};

#endif

