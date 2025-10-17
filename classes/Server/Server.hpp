/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:11:18 by aykrifa           #+#    #+#             */
/*   Updated: 2025/10/17 15:35:16 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <vector>
#include <string>
#include <iostream>

class	Server
{
	public:

		Server(void);
		Server(const Server& src);

		~Server();

		Server& operator=(const Server& server);

		void print();
		/*std::vector<Location> getLocations() const;    */
		/**/
		/*// Access config*/
		/*const Config& getConfig() const;*/
		/**/
		/*void startServer();*/
		/*void stopServer();*/
		/*void listening();*/
		/**/
		/*void addConnection();*/
		/*void endConnection();*/
		/**/
	private:
		;
};
