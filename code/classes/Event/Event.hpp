/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Event.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 10:41:38 by aykrifa           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <unistd.h>

typedef enum e_type
{
	SRV = 0,
	CLIENT,
	PIPE
} type;

struct Event
{
	Event(type _type):_type(_type), _fd(-1){}
	~Event(void)
	{
		if (_fd != -1)
			close (_fd);
	};
	int	getFd(void) const
	{
		return (this->_fd);
	}
	void	setFd(const int fd)
	{
		this->_fd = fd;
	}
	type _type;
	int _fd;
private:
};
