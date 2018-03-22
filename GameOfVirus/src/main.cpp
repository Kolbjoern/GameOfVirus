#pragma once

#include "Server.h"
#include "Client.h"

#include <iostream>

int main()
{
	char who;
	std::cout << "server (s) or client(c)? ";
	std::cin >> who;
	std::cin.ignore(); //clears newline

	if (who == 'c')
	{
		Client client;
		client.run();
	}
	else
	{
		Server server;
		server.run();
	}

	return 0;
}
