#pragma once

#include "network\PackageListener.h"

#include <SFML\Network.hpp>

#include <unordered_map>
#include <queue>

class Server
{
public:
	Server();
	~Server();

	void run();

private:
	void init();

	void tick();

	PackageListener m_receiver;

	sf::UdpSocket m_socket;
	sf::Time m_tickDelay;

	std::unordered_map<std::string, std::string> m_clients;
	std::queue<std::string> m_messageQueue;
};

