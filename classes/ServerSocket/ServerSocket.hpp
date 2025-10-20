/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:49:02 by aykrifa           #+#    #+#             */
/*   Updated: 2025/10/20 13:49:04 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <vector>
#include <string>
#include <iostream>

class	Server;

class ServerSocket
{
	public:
		ServerSocket(void);
		ServerSocket(const ServerSocket& src);
		~ServerSocket();

		ServerSocket& operator=(const ServerSocket& server);
	
	private:
		std::string			_host;
		std::string			_port;
		std::vector<Server>	_virtualHost;
};
