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

void	printnode(Node *node, unsigned int depth)
{
	for (unsigned int i = 0; i != depth; i++)
	{
	  std::cout << "\t";
	}
	std::cout << "Node:";
	for (std::vector<Token>::iterator it = node->tok.begin(); it != node->tok.end(); it++)
	{
		std::cout << it->str + ' ';
	}
	std::cout << std::endl;
}

Node	*ConfigParser::parseToken(int depth)
{
	std::vector<Token>	buffer;
	while (!comp(";") && !comp("{") && !comp("}") && !end())
	{
		buffer.push_back(*_token_it);
		next();
	}
	if (end())
	{
		if (!buffer.empty())
			throw (std::runtime_error("Expression must be ended with \";\" or \"{\"\n-->" + *_token_it));
		return (NULL);
	}
	if (comp("}"))
	{
		if (!buffer.empty())
			throw (std::runtime_error("Unexpected \"}\": content should be ended with \";\" or \"{\"\n-->" + *_token_it));
		if (depth == 0)
			throw (std::runtime_error("\"}\" found while no \"{\" before\n-->" + *_token_it));
		next();
		return (NULL);
	}
	if (buffer.empty())
		throw (std::runtime_error("Content expected before\n-->" + *_token_it));
	Node	*current = new Node(buffer);
	printnode(current, depth);

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

void	ConfigParser::run(void)
{
	tokenInit();

	try
	{
		this->head = parseToken(0);
	}
	catch (std::exception &e)
	{
		std::cerr << "Error in config: " << e.what() << std::endl;
	}
	currentNode = head;
}
