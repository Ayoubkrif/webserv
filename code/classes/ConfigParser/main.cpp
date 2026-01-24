/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:39:41 by aykrifa           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigParser.hpp"
#include <sstream>

std::string	nbrToString(size_t nbr)
{
	std::ostringstream oss;
	oss << nbr;
	std::string str = oss.str();
	return str;
}

std::ostream	&operator<<(std::ostream&lhs, const Token&rhs)
{
	lhs << '"' + rhs.str + '"' + " l:" << rhs.line;
	return (lhs);
}

std::string	&operator+(std::string&lhs, const Token&rhs)
{
	lhs.append(rhs.str + " l:" + nbrToString(rhs.line));
	return (lhs);
}

std::string	operator+(const char *lhs, const Token&rhs)
{
	std::string	str(lhs);
	str.append(rhs.str + " l:" + nbrToString(rhs.line));
	return (str);
}

int	main(void)
{
	ConfigParser	config("default.conf");
	config.run();
}
