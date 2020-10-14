#ifndef NETCORE_H
#define NETCORE_H
#include "stdafx.h"

class NetCore
{
private:
	const unsigned short port = 27000;
	sf::IpAddress ipaddres;
	sf::UdpSocket socket;
	sf::Packet packet;

public:
	void initnet();




	virtual void sendPack(char cdata);
	virtual void sendPack(sf::Vector2f pos);

	virtual void resiver();



	NetCore();
	virtual ~NetCore();

};



#endif // !NETCORE_H
