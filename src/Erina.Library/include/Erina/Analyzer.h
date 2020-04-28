#pragma once
#ifndef ERINA_ANALYZER_H
#define ERINA_ANALYZER_H
class Analyzer
{
public:
	static void Initialize();

private:
	static void __cdecl sendPacketHook(unsigned char* buff, unsigned short length);
	static void __cdecl handlePacketHook(unsigned short packetType, unsigned char* buff, unsigned short length);
};

#endif