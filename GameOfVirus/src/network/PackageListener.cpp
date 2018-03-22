#include "PackageListener.h"

#include <iostream>


PackageListener::PackageListener()
{
}

void PackageListener::init(sf::UdpSocket& socket, std::queue<std::string>& packageQueue)//std::unordered_map<std::string, std::string>& clients)
{
	sf::IpAddress sender;
	unsigned short port;
	sf::Packet packet;

	while (true)
	{
		packet.clear();
		if (socket.receive(packet, sender, port) != sf::Socket::Done)
		{
			std::cout << "message failed" << std::endl;
		}
		else
		{
			/*if (clients.find(sender.toString()) == clients.end())
			{
				std::cout << "new client registered: " << sender.toString() << std::endl;
				clients.insert({ sender.toString(), sender.toString() });
			}*/

			std::string message;

			if (packet >> message)
			{
				packageQueue.push(message);
				//std::cout << message << std::endl;
			}
		}
	}
}