/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 15:26:33 by aykrifa           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Location.hpp"

const std::map<std::string, Location>	&Server::getLocations(void) const
{
	return (this->_locations);
}

void	Server::setLocationsMap(std::map<std::string, Location>	&locations)
{
	this->_locations = locations;
}

void	Server::addLocations(std::string &key, Location &value)
{
	if (this->_locations.find(key) != this->_locations.end())
		throw (std::runtime_error("URL already exist"));
	this->_locations[key] = Location(value);
}

unsigned short int	Server::getPort(void) const
{
	return (this->_port);
}

void	Server::setPort(unsigned short int port)
{
	this->_port = port;
}

unsigned int	Server::getInterface(void) const
{
	return (this->_interface);
}

void	Server::setInterface(unsigned int interface)
{
	this->_interface = interface;
}
