#include <Erina/Packets/PacketHandler.h>
#include <Erina/Packets/Client/ClientLoginRequestPacket.h>
#include <Erina/Packets/Server/ServerLoginRequestPacket.h>

PacketHandler::PacketHandler()
{
	// Client handler
	this->_clientPacketHandler[PacketType::LoginRequest] = new ClientLoginRequestPacket("Login Request");

	// Server handler
	this->_serverPacketHandler[PacketType::LoginRequest] = new ServerLoginRequestPacket("Login Request");
}

bool PacketHandler::HandleClientPacket(const Packet* packet)
{
	int count = this->_clientPacketHandler.count(packet->Type);

	if (count < 1)
	{
		return false;
	}

	this->_clientPacketHandler[packet->Type]->Deserialize(packet);

	return true;
}

bool PacketHandler::HandleServerPacket(const Packet* packet)
{
	int count = this->_serverPacketHandler.count(packet->Type);

	if (count < 1)
	{
		return false;
	}

	this->_serverPacketHandler[packet->Type]->Deserialize(packet);

	return true;
}