#include "Server.h"

#include "Globals.h"

#include <iostream>
#include <thread>

Server::Server()
{
}

Server::~Server()
{
}

void Server::run()
{
	init();

	std::thread thread(&PackageListener::init, &m_receiver, std::ref(m_socket), std::ref(m_messageQueue));

	while (true)
	{
		sf::sleep(m_tickDelay);
		tick();
	}

	thread.join();
}

void Server::init()
{
	// bind socket to a port
	m_socket.bind(PORT_SERVER);

	m_tickDelay = sf::milliseconds(2000);//100

	std::cout << "waiting" << std::endl;
}

void Server::tick()
{
	std::cout << "tick" << std::endl;

	while (!m_messageQueue.empty())
	{
		std::cout << m_messageQueue.front() << std::endl;
		m_messageQueue.pop();
	}

	/*for (std::pair<std::string, std::string> client : m_clients)
	{
		sf::Packet packet;
		packet.clear();
		packet << "hello " + client.first;
		if (m_socket.send(packet, client.first, PORT_CLIENT) != sf::Socket::Done)
		{
			std::cout << "server message failed" << std::endl;
		}
	}*/
}