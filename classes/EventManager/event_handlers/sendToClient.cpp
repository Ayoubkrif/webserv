/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sendToClient.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 14:28:00 by aykrifa           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "EventManager.hpp"
#include "Request.hpp"
#include "Cgi.hpp"
#include <cerrno>

bool	EventManager::sendBuffer(Request &client)
{
	std::string toSend = client._response.get(BUFFER_SIZE);

	if (send(client.fd, toSend.data(), toSend.size(), 0) == -1)
	{
		EventDelete(client.fd);
		this->requests.remove((Request *)getPtr());
		delete (Request *)getPtr();
		return (false);
	}
	return (client._response.transmissionComplete());
}

void	EventManager::sendToClient(void)
{
	Request &client = *(Request *)getPtr();

	if (!sendBuffer(client))
		return;

	if (client.getConnection() == KEEP_ALIVE)
	{
		client.resetRequest();
		EventModify(client.fd, EPOLLIN, &client);
	}
	else
	{
		EventDelete(client.fd);
		this->requests.remove((Request *)getPtr());
		delete (Request *)getPtr();
	}
}
