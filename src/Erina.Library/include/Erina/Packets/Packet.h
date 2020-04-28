#pragma once
#ifndef ERINA_PACKETS_PACKET_H
#define ERINA_PACKETS_PACKET_H
#include <Erina\Packets\PacketType.h>
#include <vector>

class Packet
{
public:

	Packet(Packet const&) = delete;
	Packet& operator=(Packet const&) = delete;
	
	PacketType Type;

	std::vector<unsigned char> Data;

	Packet(PacketType packetType, unsigned char* buffer, unsigned short length);
	Packet(unsigned char* buffer, unsigned short length);

private:

};

#endif
