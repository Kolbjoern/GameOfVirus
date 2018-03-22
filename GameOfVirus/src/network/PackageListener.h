#pragma once

#include <SFML\Network.hpp>

#include <unordered_map>
#include <queue>

class PackageListener
{
public:
	PackageListener();

	void init(sf::UdpSocket& socket, std::queue<std::string>& packageQueue);//std::unordered_map<std::string, std::string>& clients);
};

