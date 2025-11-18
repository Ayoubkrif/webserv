/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeaderParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <bordeau@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 10:45:29 by cbordeau          #+#    #+#             */
/*   Updated: 2025/11/18 11:55:33 by cbordeau         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "HeaderParser.hpp"

std::string HeaderParsing::fields[207][3] = {};
void (Request::*HeaderParsing::ptr[210])(std::string) = {NULL};

void HeaderParsing::initFields()
{
	HeaderParsing::fields[40][0] = "range";
	HeaderParsing::fields[42][0] = "accept";
	HeaderParsing::fields[58][0] = "host";
	HeaderParsing::fields[66][0] = "origin";
	HeaderParsing::fields[67][0] = "expect";
	HeaderParsing::fields[70][0] = "cookies";
	HeaderParsing::fields[102][0] = "connection";
	HeaderParsing::fields[147][0] = "accept-language";
	HeaderParsing::fields[150][0] = "accept-encoding";
	HeaderParsing::fields[150][1] = "cache-control";
	HeaderParsing::fields[164][0] = "authorization";
	HeaderParsing::fields[187][0] = "if-none-match";
	HeaderParsing::fields[189][0] = "content-length";
	HeaderParsing::fields[191][0] = "content-type";
	HeaderParsing::fields[201][0] = "transfer-encoding";
	HeaderParsing::fields[205][0] = "if-modified-since";

	// HeaderParsing::ptr[40] = &Request::parseRange;
	HeaderParsing::ptr[42] = &Request::parseAccept;
	HeaderParsing::ptr[58] = &Request::parseHost;
	// HeaderParsing::ptr[66] = &Request::parseOrigin;
	HeaderParsing::ptr[67] = &Request::parseExpect;
	HeaderParsing::ptr[70] = &Request::parseCookies;
	HeaderParsing::ptr[102] = &Request::parseConnection;
	HeaderParsing::ptr[147] = &Request::parseLanguage;
	HeaderParsing::ptr[150] = &Request::parseAcceptEncoding;
	// HeaderParsing::ptr[151] = &Request::parseCacheControl;
	HeaderParsing::ptr[164] = &Request::parseAuthorization;
	// HeaderParsing::ptr[187] = &Request::parseIfNoneMatch;
	HeaderParsing::ptr[189] = &Request::parseContentLength;
	HeaderParsing::ptr[191] = &Request::parseContentType;
	HeaderParsing::ptr[201] = &Request::parseTransferEncoding;
	HeaderParsing::ptr[205] = &Request::parseIfModifiedSince;
}
