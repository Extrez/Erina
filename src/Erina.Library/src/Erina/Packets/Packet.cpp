#include <Erina/Packets/Packet.h>
#include <vector>
#include <iostream>

Packet::Packet(PacketType packetType, unsigned char* buffer, unsigned short length)
{
	this->Type = packetType;
	this->Data = buffer;
}

Packet::Packet(unsigned char* buffer, unsigned short length)
{
	this->Type = (PacketType)*reinterpret_cast<unsigned short*>(buffer);
	this->Data = buffer + 2;
}