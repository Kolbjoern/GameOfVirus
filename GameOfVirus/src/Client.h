#pragma once

#include <SFML\Network.hpp>

class Client
{
public:
	Client();
	~Client();

	void run();

private:
	void init();

	sf::UdpSocket m_socket;
};

