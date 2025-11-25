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
#include <stdexcept>
#include <utility>

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
		throw (std::runtime_error(""));
	// this->_locations[key] = value;
	this->_locations[key] = Location(value);
	// std::pair<std::string, Location> pair = std::make_pair(key, value);
	// this->_locations.insert(pair);
}
