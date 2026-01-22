/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:51:43 by aykrifa           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <ostream>
#include <string>
#include <vector>

struct Token
{
	std::string		str;
	unsigned int	line;
	Token(std::string str, unsigned int line) : str(str), line(line) {}
};

std::ostream	&operator<<(std::ostream&lhs, const Token&rhs);

struct Node
{
	std::vector<Token>	tok;
	Node				*sibling;
	Node				*child;

	Node(std::vector<Token> token) : tok(token), sibling(NULL), child(NULL) {}

    // Destructeur récursif
    ~Node() {
        delete sibling;  // Appelle récursivement le destructeur de l'enfant gauche
        delete child; // Appelle récursivement le destructeur de l'enfant droit
        // Le C++ garantit que 'delete' sur un pointeur NULL ne fait rien.
    }
};
