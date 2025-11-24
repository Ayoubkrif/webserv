/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:28:02 by aykrifa           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include "tokens.hpp"

class	Server;
class	Location;

class	ConfigParser
{
	public:
		static void	run(char *);
		static void	tokenize(std::vector<std::string>&, char*);
		static void	parseServer(std::vector<Server>&, std::vector<std::string>::iterator&);
		static void	parseLocation(std::vector<Location>&, std::vector<std::string>::iterator&);
		static int	checkDirective(std::string &token);

	private:
		ConfigParser(){}
		~ConfigParser(){}
};
