/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_request_line.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <bordeau@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:33:51 by cbordeau          #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

//parse method
//reconstitue/parse URI
//check HTTP/1.1
void	Request::parseRequestLine(std::string token)
{
	std::string::size_type cursor= 0;

	if (moveCursor(&cursor, token, " "))
	{
		this->parseMethod(token.substr(0, cursor));
		token.erase(0, cursor + 1);
		if (isState(ERROR))
			return;
	}
	else
	{
		this->setStatus(BAD_REQUEST);
		this->setState(ERROR);
		return;
	}
	if (moveCursor(&cursor, token, " "))
	{
		this->parseURI(token.substr(0, cursor));
		token.erase(0, cursor + 1);
		if (isState(ERROR))
			return;
	}
	else
	{
		this->setStatus(BAD_REQUEST);
		this->setState(ERROR);
		return;
	}
	if (token.compare("HTTP/1.1"))
	{
		this->setStatus(BAD_REQUEST);
		this->setState(ERROR);
		streams.get(LOG_REQUEST) << "[ERROR]" << std::endl
			<< "Wrong HTTP protocol:" << token
			<< std::endl;
	}
}
