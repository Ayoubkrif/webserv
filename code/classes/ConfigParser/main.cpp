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

std::ostream	&operator<<(std::ostream&lhs, const Token&rhs)
{
	lhs << '"' + rhs.str + '"' + " l:" << rhs.line;
	return (lhs);
}

int	main(void)
{
	ConfigParser	config("default.conf");
	config.run();
}
