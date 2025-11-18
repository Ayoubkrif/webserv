/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ArgChecker.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:48:19 by aykrifa           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "ArgChecker.hpp"

void	ArgChecker::checkargs(int argc)
{
	if (argc > 2)
	{
		throw (TooMuchArgs());
	}
	if (argc < 2)
	{
		throw (TooFewArgs());
	}
}
