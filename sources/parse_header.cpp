/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:43:32 by cbordeau          #+#    #+#             */
/*   Updated: 2025/11/17 14:15:40 by cbordeau         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_header.hpp"
#include "../classes/HeaderParser/HeaderParser.hpp"

void	parse_buffer(Request *request)
{
	std::string::size_type cursor = 0;
	//header is full in buffer
	if (move_cursor(&cursor, request->getBuffer(), DCRLF) && !request->get_hEnd())
	{
		request->tokenize(cursor, HEADER);
		parse_header(request);
		//body is full in buffer
		if (move_cursor(&cursor, request->getBuffer(), DCRLF))
		{
			request->tokenize(cursor, BODY);
		}
	}
	if (request->get_hEnd() && !request->get_bEnd() && move_cursor(&cursor, request->getBuffer(), DCRLF))
	{
		request->tokenize(cursor, BODY);
	}
	std::cout << "header is : " << request->getHeader() << std::endl;
	std::cout << "body is : " << request->getBody() << std::endl;
	std::cout << "buffer is : " << request->getBuffer() << std::endl;
}

void	parse_header(Request *request)
{
	std::string::size_type	cursor = 0;
	std::string				token;

	request->getToken(&token, &cursor);
	//parse_request(token, event);
	int type;
	while (1)
	{
		cursor = request->getHeader().find(":");
		if (cursor != std::string::npos)
		{
			type = request->getField(&cursor);
		}
		// else
		// 	;
			//throw error;
		if (type < 0)
			break;
		request->getToken(&token, &cursor);
		(request->*HeaderParsing::ptr[type])(token, request);
		
	}
	//check_complete_header(event);
}
