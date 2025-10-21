/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:38:29 by aykrifa           #+#    #+#             */
/*   Updated: 2025/10/21 15:42:01 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include <iostream>
#include <fstream>
#include <sstream>

std::string	extractStr(char *InputFile);
void		commentFilter(std::string &str);
