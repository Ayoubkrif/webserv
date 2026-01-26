/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header_utils.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <bordeau@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 13:39:14 by cbordeau          #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include "Request.hpp"

int	moveCursor(std::string::size_type *cursor, std::string str, std::string toFind)
{
	*cursor = str.find(toFind);
	if (*cursor != std::string::npos)
		return 1;
	else
		return 0;
}

int	moveCursor(std::string::size_type *cursor, std::string str, int start, std::string toFind)
{
	*cursor = str.find(toFind, start);
	if (*cursor != std::string::npos)
		return 1;
	else
		return 0;
}

void	printRequest(Request *request)
{
	streams.get(LOG_REQUEST) << "[HEADER AFTER PARSING]" << std::endl
		<< request->getHeader() << std::endl
		<< std::endl
		<< "[BODY AFTER PARSING]" << std::endl
		<< request->getBody() << std::endl
		<< std::endl
		<< "[BUFFER AFTER PARSING]" << std::endl
		<< request->getBuffer() << std::endl
		<< std::endl
		<< "[REQUEST IS]" << std::endl
		<< *request
		<< std::endl;
}
