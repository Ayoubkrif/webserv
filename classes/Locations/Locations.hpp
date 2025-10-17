/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Locations.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:06:50 by aykrifa           #+#    #+#             */
/*   Updated: 2025/10/17 12:07:39 by aykrifa          ###   ########.fr       */
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
		;
};
