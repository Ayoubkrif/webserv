/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:09:36 by aykrifa           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "ConfigParser.hpp"
#include "Location.hpp"
#include "Server.hpp"
#include "Request.hpp"
#include "errors.hpp"

const std::string	MIMES_PATH = "resources/mime.types";
const std::string	DEFAULT_CONF_PATH = "configs/default.conf";
const std::string	DEFAULT_LOCATION_ERRORPAGES_PATH = "./resources/default_error_pages/";

class TooMuchArgs : public std::exception
{
	public:
		virtual const char	*what() const throw()
		{
			return (ARG_TOO_MUCH);
		}
};
