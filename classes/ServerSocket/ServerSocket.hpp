#pragma once

#include <map>
#include <vector>
#include <string>
#include <iostream>

class ServerSocket
{
	public:
		ServerSocket(void);
		ServerSocket(const ServerSocket& src);
		~ServerSocket();

		ServerSocket& operator=(const ServerSocket& server);
	
	private:
		;
};
