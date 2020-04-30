#include <Erina/Packets/Client/ClientLoginRequestPacket.h>
#include <iostream>

void ClientLoginRequestPacket::Deserialize(const Packet* packet)
{
	std::cout << "Deserialize " << this->Name << ": " << std::endl;

	auto loginRequest = (ClientLoginRequestStruct*)packet->Data;

	std::cout << "\tUsername: " << loginRequest->UserName << " Unknow: " << loginRequest->Unknow << " Password: " << loginRequest->Password <<std::endl;
}