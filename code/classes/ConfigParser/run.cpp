/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:58:41 by aykrifa           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigParser.hpp"
#include "tokens.hpp"
#include <exception>
#include <iostream>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <vector>

Node	*ConfigParser::parseToken(int depth)
{
	std::vector<Token>	buffer;
	while (comp(";") || comp("{") || comp("}") || end())
	{
		buffer.push_back(*_token_it);
		next();
	}
	if (end())
	{
		if (!buffer.empty())
			throw (std::runtime_error("token must be ended by { or ;"));
		return (NULL);
	}
	if (comp("}"))
	{
		if (!buffer.empty())
			throw (std::runtime_error("token  in { must be ended by { or ; and not }"));
		if (!depth)
			throw (std::runtime_error("} error"));
		return (NULL);
	}
	Node	*current = new Node(buffer);

	if (comp("{"))
	{
		next();
		current->child = parseToken(depth + 1);
		current->sibling = parseToken(depth);
	}
	else
	{
		next();
		current->sibling = parseToken(depth);
	}
	return (current);
}

void	printnode(Node *node)
{
	std::cout << "node: ";
	for (std::vector<Token>::iterator it = node->tok.begin(); it != node->tok.end(); it++)
	{
		std::cout << it->str + ' ';
	}
	std::cout << std::endl;
	
	std::cout << " his son :";
	if (!node->child)
		std::cout << "NULL";
	else
		printnode(node->child);

	std::cout << "node: ";
	for (std::vector<Token>::iterator it = node->tok.begin(); it != node->tok.end(); it++)
	{
		std::cout << it->str + ' ';
	}
	std::cout << std::endl;

	std::cout << "his sibling :";
	if (!node->sibling)
		std::cout << "NULL";
	else
		printnode(node->sibling);
}

void	ConfigParser::run(void)
{
	Node	*head;
	tokenInit();

	try
	{
		head = parseToken(0);
		printnode(head);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
}
