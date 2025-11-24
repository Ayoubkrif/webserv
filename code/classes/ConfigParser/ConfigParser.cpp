/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:23:47 by aykrifa           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigParser.hpp"
#include "Logger.hpp"
#include "Server.hpp"
#include "Location.hpp"
#include "tokens.hpp"
#include <exception>
#include <vector>
#include <fstream>
#include <sstream>

int	ConfigParser::checkDirective(std::string &token)
{
	for (int i = 0; i != NONE; ++i)
	{
		if (token == DIRECTIVE[i])
			return (i);
	}
	throw (std::runtime_error("Unrecognized token " + token));
}

void	ConfigParser::parseLocation(std::vector<Location> &locations, std::vector<std::string>::iterator &it)
{
	Location	current;
	while (true)
	{
		switch (checkDirective(*it))
		{
			case ROOT:
				;
			break ;

			case ALIAS:
				;
			break ;

			case CLIENT_MAX_BODY_SIZE:
				;
			break ;

			case CGI_SUFFIX:
				;
			break ;

			case METHODS:
				;
			break ;

			case RETURN:
				;
			break ;

			case AUTOINDEX:
				;
			break ;

			case CLOSING_BRACKET:
			goto BREAK;
			
			default :
				throw (std::runtime_error("Unauthorized directive in location scope :" + *it));
		}
	}
	BREAK:
	locations.push_back(current);
}

void	ConfigParser::parseServer(std::vector<Server> &servers, std::vector<std::string>::iterator &it)
{
	Server	current;
	// check if there is an opening bracket
	if (*it != "{")
	{
		throw (std::runtime_error("Unrecognized token " + *it));
	}
	it++;
	std::vector<Location>	locations;
	switch (checkDirective(*it))
	{
		case LISTEN:
			// parseListen(server, it);
			break ;
		case LOCATION:
			parseLocation(locations, it);
			break ;
		default :
			throw (std::runtime_error("Unauthorized directive in server scope :" + *it));
	}
	// check interface:port are unique
	for (std::vector<Server>::iterator it1 = servers.begin(); it1 != servers.end(); it++)
	{
		// if (current *it1)
			// throw (std::runtime_error("Server may not have same port" + *it));
	}
	current.setLocations(locations);
	servers.push_back(current);
}

void	ConfigParser::run(char *file)
{
	std::vector<std::string>	token;
	std::vector<Server>	servers;

	tokenize(token, file);
	for (std::vector<std::string>::iterator it = token.begin(); it != token.end(); ++it)
	{
		switch (checkDirective(*it))
		{
			case SERVER:
				it++;
				parseServer(servers, it);
				break ;
			default :
				throw (std::runtime_error("Unauthorized directive in server scope :" + *it));
		}
	}
}
