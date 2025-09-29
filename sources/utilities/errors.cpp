#include "webserv.hpp"

int	errorMessage(const char *message, int ecode) {

	std::cerr << message << std::endl;
	return ecode;
} 
