#include <Erina/Packets/PacketHandler.h>
#include <Erina/Packets/Client/LoginRequestPacket.h>

PacketHandler::PacketHandler()
{
	this->_clientPacketHandler[PacketType::LoginRequest] = new LoginRequestPacket("Login Request");
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