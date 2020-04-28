#include <Erina/Packets/Client/LoginRequestPacket.h>
#include <iostream>

void LoginRequestPacket::Deserialize(const Packet* packet)
{
	std::cout << "Deserialize packet: " << this->Name << std::endl;
}