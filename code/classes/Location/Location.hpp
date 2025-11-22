/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 13:31:52 by aykrifa           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <vector>
#include <map>


static const int	GET = 0;
static const int	POST = 1;
static const int	DELETE = 2;

class	Location
{
public:
	public:Location(void);
	public:Location(Location&);
	public:~Location(void);

	public:Location							&operator=(const Location&);

	public:const std::string					&getName(void) const;
	public:void								setName(std::string);

	public:void								setAlias(std::string);
	public:const std::string					&getAlias(void) const;

	public:void								setClientMaxBodySize(unsigned int);
	public:unsigned int						getClientMaxBodySize(void) const;

	public:void								setCgiSuffix(std::vector<std::string>);
	public:const std::vector<std::string>		&getCgiSuffix(void) const;

	public:void								setMethod(bool[3]);
	public:const bool							*isMethodAllowed(void) const;

	public:const std::string					&getRoot(void) const;
	public:void								setRoot(std::string);

	public:const std::string					&getRedirect(void) const;
	public:void								setRedirect(std::string);

	public:bool								isAutoindexEnabled(void) const;
	public:void								setAutoindex(bool);

	public:const std::map<int, std::string>	&getErrorPages(void) const;
	public:void								setErrorPages(std::map<int, std::string>);

	public:const std::string					&getPostDirectory(void) const;
	public:void								setPostDirectory(std::string);

private:
	private:std::string					_name;
	private:std::string					_root;
	private:std::string					_alias;
	private:std::string					_redirect;
	private:unsigned int				_client_max_body_size;
	private:bool						_autoindex;
	private:std::vector<std::string>	_cgi_suffix;
	private:std::map<int, std::string>	_error_page;
	private:bool						_methods[3];
	private:std::string					_post_directory;
};
