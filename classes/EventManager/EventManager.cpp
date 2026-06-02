/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventManager.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:50:38 by aykrifa           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "EventManager.hpp"

#include <cerrno>
#include <csignal>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdexcept>

#include "Event.hpp"
#include "Server.hpp"
#include "Request.hpp"
#include "Cgi.hpp"
#include "helpers.hpp"

std::string intToIPv4(uint32_t);
EventManager::EventManager(std::vector<Server> &servers): _alive(true), lastZombieCheck(std::time(NULL)), _servers(servers)
{
    _fd = epoll_create1(0);
    if (_fd == -1)
	{
        perror("epoll_create1");
		throw (std::runtime_error("epoll"));
    }
	for(std::vector<Server>::iterator it = servers.begin(); it != servers.end(); it++)
	{
		it->startListen();
		EventAdd(it->getFd(), EPOLLIN, &*it);
	}
	// building jumptable thx to gemini
	epollinHandler[0] = &EventManager::serverAcceptClient;
	epollinHandler[1] = &EventManager::recvFromClient;
	epollinHandler[2] = &EventManager::handlePipe;
}

EventManager::~EventManager(void)
{
	close (this->_fd);
	for (std::list<Request*>::iterator it = requests.begin(); it != requests.end(); it++)
	{
		delete (*it);
	}
}

void	EventManager::run(void)
{
	std::signal(SIGPIPE, SIG_IGN);
	while (_alive)
	{
		// for each events
		for (getNewEvent(); getPtr(); eventNext())
		{
			if (eventIs(EPOLLIN)) // retriving which func it will call in th ejumptable epollinHandler
				(this->*epollinHandler[checkEvent()])();
			else if (eventIs(EPOLLOUT) && checkEvent() == CLIENT) // EPOLLOUT can only be for client send queue
				sendToClient();
			else if (eventIs(EPOLLHUP) && checkEvent() == PIPE)
				handlePipe();
			if (_alive == false)
				break;
		}
		zombieCheck();
	}
}
