/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 12:57:39 by aykrifa           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "Logger.hpp"

std::map<std::string, std::ofstream*> Logger::_outfile;

std::ofstream	&Logger::print(const std::string &file)
{
    return (*_outfile.at(file));
}

void	Logger::add(const std::string &file)
{
    if (_outfile.find(file) != _outfile.end())
		throw std::runtime_error("Log file already registered" + file);
	std::ofstream	*ofs = new std::ofstream();
    ofs->open(file.c_str());
    if (!ofs->is_open())
    {
        // Supprime l'entrée créée avant de throw
        _outfile.erase(file);
		delete (ofs);
        throw std::runtime_error("Failed to open log file: " + file);
    }
	_outfile.insert(std::make_pair(file, ofs));
}

void	Logger::delete_streams(void)
{
    for (std::map<std::string, std::ofstream*>::iterator it = _outfile.begin();
         it != _outfile.end();
         ++it)
    {
        if (it->second)
        {
            it->second->close();   // ferme le flux si ouvert
            delete it->second;     // libère la mémoire
        }
    }
    _outfile.clear(); // vide la map
}
