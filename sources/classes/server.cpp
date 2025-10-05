#include "server.hpp"

Server::Server() {}

Server::Server(const Server& other) {
	_port = other._port;
	_name = other._name;
	_root = other._root;
}

Server::~Server() {

}

Server::Server(
		unsigned short port, 
		std::string name, 
		std::string root,
		std::vector<Location> locations) {
	_port = port;
	_name = name;
	_root = root;
	_locations = locations;
}

Server& Server::operator=(const Server& server) {
	(void)server;
	return *this;
}

void	addConnection() {

}

void	endConnection() {

}
