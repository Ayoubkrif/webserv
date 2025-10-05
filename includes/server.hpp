#pragma once

#include <vector>
#include <string>

class Server {

	// ports range from 0 to 65535
	unsigned short	_port;
	// We can use bit masks for aloowed methods
	unsigned short	_methods;
	std::string	_name;
	std::string	_root;
	// Unsure about this one
	std::vector<std::string> _contents;	

//	std::vector<Clients> clients;

	Server();

	public:

	Server(unsigned short port, std::string name, std::string root);
	~Server();
	Server(const Server& src);

	Server& operator=(const Server& server);

	void addConnection();
	void endConnection();
};
