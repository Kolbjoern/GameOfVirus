#include "Client.h"

#include <iostream>

Client::Client()
{
}

Client::~Client()
{
}

void Client::run()
{
	init();
}

void Client::init()
{
	sf::Packet packet;
	std::string serverIp;

	std::cout << "Server address:: ";
	std::cin >> serverIp;
	std::cin.ignore(); //clears newline

	while (true)
	{
		std::string message;
		std::getline(std::cin, message);
		packet.clear();
		packet << message;

		if (m_socket.send(packet, serverIp, 43000) != sf::Socket::Done)
		{
			std::cout << "client message failed" << std::endl;
		}
	}
}