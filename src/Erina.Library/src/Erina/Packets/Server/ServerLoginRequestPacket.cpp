#include <Erina/Packets/Server/ServerLoginRequestPacket.h>
#include <Erina/Packets/Packet.h>
#include <iostream>

void ServerLoginRequestPacket::Deserialize(const Packet* packet) 
{
	std::cout << "Deserialize " << this->Name << ": " << std::endl;

	auto loginRequest = (ServerLoginRequestStruct*)packet->Data;

	std::cout << "\tError: " << (loginRequest->Error ? "yes" : "no") << " UserId: " << loginRequest->UserId << " Session key: " << loginRequest->SessionKey << std::endl;
}