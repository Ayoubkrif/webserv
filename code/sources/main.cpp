/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:37:55 by aykrifa           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

int	main(int argc, char **argv)
{
	try
	{
		Logger::add(LOG_CONFIGPARSER);
		Logger::print(LOG_CONFIGPARSER) << "DELIVRANCE" << std::endl;
		ArgChecker::checkargs(argc);
		ConfigParser::run(argv[1]);
		Logger::delete_streams();
	}
	catch (std::exception	&e)
	{
		Logger::delete_streams();
		std::cerr << "Exception caught :"<< e.what() << std::endl;
	}
}
