/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Locations.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:06:50 by aykrifa           #+#    #+#             */
/*   Updated: 2025/10/19 15:14:34 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <string>

class	Location
{
    public:

        Location(void);
		Location(const Location& src);
        ~Location();

    	Location& operator=(const Location& src);
	
	private:
		std::string	_root;
		std::string	_key;
		std::string	_index;
		bool		_get;
		bool		_post;
		bool		_delete;
};
