/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <bordeau@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:36:44 by cbordeau          #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_header.hpp"
#include "../classes/Request/Request.hpp"
#include "../classes/Cgi/Cgi.hpp"

void	parse_header_type(Request *request)
{
	std::string::size_type	cursor = 0;
	std::string				token;

	if (request->getHeader().empty())
		return;
	request->getToken(&token, &cursor);
	parse_request_line(request, token);
	if (request->getState() == CGI)
		parse_cgi_header(request);
	else
		parse_header(request);
		
	//if CGI parse_header in cgi mode
	//state CGI but same parsing function?
}

void	parse_header(Request *request)
{
	std::string::size_type	cursor = 0;
	std::string				token;

	if (request->getHeader().empty())
		return;
	
	int type;
	while (1)
	{
		if (request->getHeader().empty())
		{
			std::cout << "header emptied" << std::endl;
			break;
		}
		if (!move_cursor(&cursor, request->getHeader(), ":"))
		{
			std::cout << RED << ": not found" << WHITE << std::endl;
			break; //throw error?
		}
		type = request->getField(&cursor);
		if (type < 0)
		{
			std::cout << RED << "Type = -1" << WHITE << std::endl;
			break; //throw error?
		}
		request->getToken(&token, &cursor);
		if (Request::fctField[type] != NULL)
			(request->*Request::fctField[type])(token);
		else
			std::cout << "Invalid index is " << type << std::endl;//not necessarly, field can be valid but no function
		
	}
	//check_complete_header(event);
	if (request->getTransferEncoding() == CHUNKED)
		request->setState(CHUNK_SIZE);
	else
		request->setState(BODY);
}

void	parse_cgi_header(Request *request)
{
	std::string::size_type	cursor = 0;
	std::string				token;
	std::string				field;
	Cgi						cgi;

	if (request->getHeader().empty())
		return;
	
	while (1)
	{
		if (request->getHeader().empty())
		{
			std::cout << "header emptied" << std::endl;
			break;
		}
		if (!move_cursor(&cursor, request->getHeader(), ":"))
		{
			std::cout << RED << ": not found" << WHITE << std::endl;
			break; //throw error?
		}
		request->getField(&field, &cursor);//why don't get field do the search?
		request->getToken(&token, &cursor);// should skip the ows qnd not parsers
		cgi.addFields(field, token);
	}
	//check_complete_header(event); //if content_length absent -> add it
	if (request->getTransferEncoding() == CHUNKED)
		request->setState(CHUNK_SIZE);
	else
		request->setState(BODY);
}
