/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statusCodes.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <bordeau@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 12:24:14 by cbordeau          #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
static const std::string OK = "200 OK";
static const std::string CREATED = "201 Created";

static const std::string BAD_REQUEST = "400 Bad Request";
static const std::string NOT_FOUND = "404 Not Found";
static const std::string REQUEST_TIMEOUT = "408 Request Timeout";
static const std::string LENGTH_REQUIRED = "411 Length Required";
static const std::string PAYLOAD_TOO_LARGE = "413 Payload Too Large"; //or Request Entity Too Large
static const std::string URI_TOO_LONG = "414 URI Too Long"; //or Request-URI Too Long
static const std::string HEADER_TOO_LONG = "431 Request Header Fields Too Large";

static const std::string INTERNAL_SERVER_ERROR = "500 Internal Server Error";
