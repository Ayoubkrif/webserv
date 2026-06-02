/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Status.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 12:47:03 by aykrifa           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

struct Status
{
	Status(std::string _str, unsigned int _code): str(_str), code(_code){}
	std::string		str;
	unsigned int	code;
};
