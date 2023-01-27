/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:02:49 by mgolinva          #+#    #+#             */
/*   Updated: 2023/01/27 14:08:07 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

Server::Server() :
_sock(0),
_port(9999),
_password("0000")
{
	_addr.sin_family = AF_INET; // use IPv4 or IPv6, whichever
	_addr.sin_port = htons(_port);
	// _addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // or INADDR_ANY >> set random usable IP Address
	std::memset(_addr.sin_zero, 0, sizeof( _addr.sin_zero));
	// std::cerr << "Debug message: Server Default Constructor called" << std::endl;
}

Server::Server(int port, std::string password) :
_sock(0),
_port(port),
_password(password)
{
	_addr.sin_family = AF_INET; // use IPv4 or IPv6, whichever
	_addr.sin_port = htons(_port);
	// _addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // or INADDR_ANY >> set random usable IP Address
	std::memset(_addr.sin_zero, 0, sizeof( _addr.sin_zero));
	// std::cerr << "Debug message: Server Constructor called" << std::endl;
}

Server::Server(const Server &src) :
_port(src._port),
_password(src._password),
_addr(src._addr)
{
	*this = src;
}

Server &Server::operator=(const Server &src)
{
	this->_sock = src._sock;
	this->_addr = src._addr;
	return (*this);
}

Server::~Server()
{
	// std::cerr << "Debug message: Server Destructor called" << std::endl;
}

/**************************************************************/
/*                                                            */
/*			               GETTERS                            */
/*                                                            */
/**************************************************************/

int						Server::getSock()		const	{ return (_sock);			}
int						Server::getPort()		const	{ return (_port);			}
std::string				Server::getPassword()	const	{ return (_password);		}
struct sockaddr_in		Server::getAdress()		const	{ return (_addr); 			}
// std::list< User >	&Server::getUserList()	const	{ return (_usersList);		}
// std::list< Channel >	&Server::getChanList()	const	{ return (_channelsList);	}
// std::list< Command >	&Server::getCmdList()	const	{ return (commandsList);	}


/**************************************************************/
/*                                                            */
/*			            MEMBER FUNCTIONS                      */
/*                                                            */
/**************************************************************/

void					Server::setSock(int type, int protocol)
{
	if ((_sock = socket(_addr.sin_family, type, protocol)) < 0)
		throw (Server::ServerException(SOCKET));
}

void					Server::bindSock()
{
	if (bind(_sock, (struct sockaddr *)&_addr, sizeof(_addr)) < 0)
		throw(Server::ServerException(BIND));
}

void					Server::listenTo(int backlog)
{
	if (listen(_sock, backlog) < 0)
		throw(Server::ServerException(LISTEN));
}

/**************************************************************/
/*                                                            */
/*			            EXCEPTION CLASSES                     */
/*                                                            */
/**************************************************************/

Server::ServerException::ServerException(int exType) : exceptionType(exType)
{
	;
}

const std::string Server::ServerException::errorMsg() const throw()
{
	if (exceptionType == SOCKET)
	{
		std::string str = "error: socket: ";
		str.append(std::strerror(errno)); 
		return (str);
	}
	else if (exceptionType == BIND)
	{
		std::string str2 = "error: bind: ";
		str2.append(std::strerror(errno)); 
		return (str2);
	}
	else if (exceptionType == LISTEN)
	{
		std::string str3 = "error: listen: ";
		str3.append(std::strerror(errno)); 
		return (str3);
	}
	return ("jsp frere");
}
