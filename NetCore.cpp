#include "NetCore.h"

void NetCore::initnet()
{
	this->ipaddres = sf::IpAddress("109.86.203.126");
}

void NetCore::sendPack(char cdata)
{
    char data[] ={cdata};

    if (socket.send(data, sizeof(data), this->ipaddres, this->port) != sf::Socket::Done)
        throw "Err send data";
}

void NetCore::sendPack(sf::Vector2f pos)
{
    this->packet << pos.x << pos.y;
    if(socket.send(this->packet,this->ipaddres,this->port)!=sf::Socket::Done)
      throw "ERR::NETCORE::sendPack error with send pos player";
}

void NetCore::resiver()
{
   // if (this->socket.receive())
    

    
}

NetCore::NetCore()
{
    this->initnet();
}

NetCore::~NetCore()
{
}
