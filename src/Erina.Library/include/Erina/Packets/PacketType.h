#pragma once
#ifndef ERINA_PACKETS_PACKETTYPE_H
#define ERINA_PACKETS_PACKETTYPE_H

enum PacketType : unsigned short
{
	Ping = 0x02,
	LoginHandshake = 0xA101,
	LoginRequest = 0xA102,
};

#endif
