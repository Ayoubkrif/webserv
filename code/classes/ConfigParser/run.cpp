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

Node	*ConfigParser::parseToken(void)
{
	std::vector<Token>	token;
	while (_token_it->str != ";" 
		&& _token_it->str != "{"
		&& _token_it->str != "}")
	{
		std::cout << "pushing" << _token_it->str;
		token.push_back(*_token_it);
		_token_it = _token_vec.erase(_token_it);
		if (_token_it == _token_vec.end())
			throw (std::runtime_error("END OF FILE WITHOUT DELIMITER"));
	}
	std::cout << std::endl << "size of actual vec:" << token.size() << std::endl;
	Node	*current = new Node(token);

	// if ((_token_it->str == ";" || _token_it->str == "{")
	// 	&& token.size() == 0)
	// {
	// 	throw (std::runtime_error("error size 0"));
	// }

	if (_token_it->str == ";")
	{
		_token_it = _token_vec.erase(_token_it);
		if (_token_it == _token_vec.end())
			return (current);
		current->sibling = parseToken();
	}
	if (_token_it->str == "{")
	{
		_token_it = _token_vec.erase(_token_it);
		if (_token_it == _token_vec.end())
			throw (std::runtime_error("Unexpected end after token {"));
		current->child = parseToken();
		if (!current->child)
			throw (std::runtime_error("error child empty"));
		if (_token_it == _token_vec.end())
			throw (std::runtime_error("Unexpected end after token {"));
		current->sibling = parseToken();
		if (_token_it == _token_vec.end())
			throw (std::runtime_error("Unexpected end after token {"));
	}
	if (_token_it->str == "}")
	{
		_token_it = _token_vec.erase(_token_it);
		return (NULL);
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
		head = parseToken();
		printnode(head);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
}
