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
#include <map>

#include "Node.hpp"

class	ConfigParser
{
	public:
		ConfigParser(const char *);
		~ConfigParser(){}
		void	run(void);
		Node	*parseToken(int);

	private:

		std::string							_str;

		void	tokenInit(void);
		void	tokenize(void);

		std::vector<Token>			_token_vec;
		std::vector<Token>::iterator	_token_it;
		void	next()
				{_token_it++;}
		bool	end()
				{return _token_it == _token_vec.end();}
		bool	comp(std::string str)
				{return _token_it->str == str;}

		ConfigParser(){}
};
