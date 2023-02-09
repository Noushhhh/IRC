/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:02:49 by mgolinva          #+#    #+#             */
/*   Updated: 2023/01/30 11:35:41 by mgolinva         ###   ########.fr       */
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
_password(password) // replace port by type uint
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
/*                         GETTERS                            */
/*                                                            */
/**************************************************************/

int                     Server::getSock()       const   { return (_sock);           }
int                     Server::getPort()       const   { return (_port);           }
std::string             Server::getPassword()   const   { return (_password);       }
struct sockaddr_in      Server::getAdress()     const   { return (_addr);           }
// std::list< User >    &Server::getUserList()  const   { return (_usersList);      }
// std::list< Channel > &Server::getChanList()  const   { return (_channelsList);   }
// std::list< Command > &Server::getCmdList()   const   { return (commandsList);    }


/**************************************************************/
/*                                                            */
/*                      MEMBER FUNCTIONS                      */
/*                                                            */
/**************************************************************/

void                    Server::setSock(int type, int protocol)
{
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = INADDR_ANY;
    _addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if ((_sock = socket(_addr.sin_family, type, protocol)) < 0)
	{
        throw (Server::ServerException(SOCKET));
	}
	int val = 1;
	if (setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)))
		throw (Server::ServerException(SOCKET));
	if (fcntl(_sock, F_SETFL, O_NONBLOCK == - 1))
		throw (Server::ServerException(SOCKET));
}

void                    Server::bindSock()
{
    if (bind(_sock, (struct sockaddr *)&_addr, sizeof(_addr)) < 0)
        throw(Server::ServerException(BIND));
}

void                    Server::listenTo(int backlog)
{
    if (listen(_sock, backlog) < 0)
        throw(Server::ServerException(LISTEN));
}

bool                    Server::init()
{
    try
	{
		this->setSock(SOCK_STREAM, PROTOCOL);
		this->bindSock();
		this->listenTo(BACKLOG);
	}
	catch(const Server::ServerException &e)
	{
		std::cerr << e.errorMsg() << '\n';
		return false ;
	}
	return true ;
}

bool                    Server::pollDispatch()
{
    struct pollfd                           server_fd = {_sock, POLLIN, 0};
    std::vector< struct pollfd >::iterator  it = _pollFds.begin();
    char                                    buff[MAX_CHAR];

    _pollFds.push_back(server_fd);
	while (1)
    {
        it = _pollFds.begin();

		if (poll (_pollFds.begin().base(), _pollFds.size(), -1) < 0)
        {
            return (false);
        }
		for (it = _pollFds.begin(); it != _pollFds.end(); it ++)
		{
            if (it->events == 0)
                continue;
			// if ((it->revents & POLLHUP) == POLLHUP)
            // {
            // }
            else if ((it->revents & POLLIN) == POLLIN)
            {
                if (it->fd == _sock)
                {
                    if (this->addUser() == false)
                    {
                        //close all sockets
                        return (false);
                    }
                    break ;
                }
                memset(buff, 0, MAX_CHAR);
                if (recv(it->fd, buff, MAX_CHAR, 0) == 0)
                {
                    if (!this->closeUser(it))
                    {
                        //close all sockets
                        return (false);
                    }
                    break ;
                }
                //receive message, stock it and parse it
                std::cout << buff;
                //send message or execute command and send reply
            }
		}
	}
    //free all except 1 and close all sockets
    return (true);
}

bool                    Server::addUser()
{
    // if bad passw
    int                 newFd;
    struct sockaddr_in  newAddr;
    socklen_t           nSize = 0;

    newFd = accept(_sock, (struct sockaddr *)&newAddr, &nSize);
    if (newFd < 0)
        return (false);
    struct pollfd *tmpfd = new struct pollfd;
    tmpfd->fd = newFd;
    tmpfd->events = POLLIN|POLLHUP;
    tmpfd->revents = 0;
    _pollFds.push_back(*tmpfd);

    User newUser(newFd, newAddr);
    this->_usersList.push_back(newUser);
    //commande NICK et PASS
    return (true);
}

bool                    Server::closeUser(std::vector< struct pollfd >::iterator it)
{
    //supress from all channels he belongs to
    for (std::list< User >::iterator lit = _usersList.begin(); lit != _usersList.end(); lit ++)
    {
        if (lit->getSockfd() == it->fd)
        {
            _usersList.erase(lit);
            break;
        }
    }
    if (close(it->fd) < 0)
        return (false);
    _pollFds.erase(it);
    return (true) ;

}

/**************************************************************/
/*                                                            */
/*                      EXCEPTION CLASSES                     */
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
