#pragma once

#include <map>
#include <vector>
#include <string>
#include <iostream>

class	Server;

class ServerSocket
{
	public:
		ServerSocket(void);
		ServerSocket(const ServerSocket& src);
		~ServerSocket();

		ServerSocket& operator=(const ServerSocket& server);
	
	private:
		std::string			_host;
		std::string			_port;
		std::vector<Server>	_virtualHost;
};
