/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:43:32 by cbordeau          #+#    #+#             */
/*   Updated: 2025/10/20 16:11:34 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/epoll.h>
#include <string>
#include <iostream>
#include "Request.hpp"

const std::string DCRLF = "\r\n\r\n";
const std::string CRLF = "\r\n";

int	move_cursor(std::string::size_type *cursor, std::string str, std::string toFind)
{
	*cursor = str.find(toFind);
	if (*cursor != std::string::npos)
		return 1;
	else
		return 0;
}
void	parse_buffer(std::string buffer, Request *request)
{
	std::string::size_type cursor = 0;
	if (move_cursor(&cursor, buffer, DCRLF) && !request->get_hEnd())
	{
		request->appendHeader(buffer, 0, cursor);
		request->set_hEnd(1);
		buffer.erase(0, cursor + 2);
		if (move_cursor(&cursor, buffer, DCRLF))
		{
		}
	}
}

void	get_token(std::string *header, std::string *token, std::string::size_type *cursor)
{
	*cursor = header->find(CRLF);
	if (*cursor != std::string::npos)
	{
		token->assign(*header, 0, *cursor);
		*cursor += 2;
		header->erase(0, *cursor);
	}
	else
		;
		//throw error;
}

int	find_type(std::string str, int end)
{
	//map.at(token)?
	//strncmp(str, tab[i], end);
	return -1;
}

void	parse_header(std::string *header, struct epoll_event *event)
{
	std::string::size_type	cursor = 0;
	std::string				token;

	get_token(header, &token, &cursor);
	//parse_request(token, event);
	int type;
	while (1)
	{
		cursor = header->find(":");
		if (cursor != std::string::npos)
		{
			type = find_type(*header, cursor);
			cursor += 1;
			header->erase(0, cursor);
			cursor = header->find(CRLF);
		}
		else
			;
			//throw error;
		if (type < 0)
			break;
		get_token(header, &token, &cursor);
		//fct[type](token, event);
		
	}
	//check_complete_header(event);
}
