/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_buffer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:43:32 by cbordeau          #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include "Cgi.hpp"
#include "statusCodes.hpp"
#include <iostream>


void	Request::parseBuffer(void)
{
	streams.get(LOG_REQUEST) << "[BUFFER BEFORE PARSING]" << std::endl
		<< this->getBuffer()
		<< std::endl;
	//can a \r or \n be alone in header???
	std::string::size_type cursor = 0;
	//header is full in buffer
	if (this->getState() == HEADER && moveCursor(&cursor, this->getBuffer(), DCRLF))
	{
		this->fillHeader(cursor);
		parseHeaderType();
		if (!this->getStatus().empty())
			return;
		if (this->getContentLength() == 0 && this->getTransferEncoding() != CHUNKED)
			this->setState(SEND);
		else if (this->getTransferEncoding() == CHUNKED)
			this->setState(CHUNK_SIZE);
		else
			this->setState(BODY);
	}

	if (this->getState() == BODY || this->getState() == CHUNK_SIZE || this->getState() == TRAILERS)
	{
		//fill body according to content-length and transfer-encoding (chunked)
		if (this->getTransferEncoding() == CHUNKED)
			this->fillChunkedBody();
		else
			this->fillBody();
	}
	if (this->getState() == SEND && this->getContentLength() != this->getBody().length())
	{
		this->setStatus(BAD_REQUEST);
	}
	printRequest(this);
}
