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

bool                    Server::init()
{
    try
        {
            this->setSock(SOCK_STREAM, PROTOCOL);
            this->bindSock();
            this->listenTo(BACKLOG);
            std::cout << "test" <<std::endl;
        }
        catch(const Server::ServerException &e)
        {
            std::cerr << e.errorMsg() << '\n';
            return false ;
        }
        return true ;
}

bool                    Server::acceptUsers()
{
    int new_socket;
    socklen_t addr_size;
    struct sockaddr_in their_addr;
	// accept if pass ok and nickname ok

	addr_size = sizeof(their_addr);
	new_socket = accept(this->getSock(), (struct sockaddr *)&their_addr, &addr_size);
	if (new_socket > 0)
	{
		if (!this->addUser(new_socket, their_addr))
			return false; // msg User couldnt be added
	}
	else if (new_socket < 0)
	{
		std::cout << "error: accept: " << std::strerror(errno) << std::endl;
	}
	std::cout << "new_sock = " << new_socket << std::endl;

	//display msg when client connecting - DO IT WITH POLL INSTEAD OF SEND
    // display "WELCOME TO THE FUTURE\n"
    // display "PASS MESSAGE ?"

	const char *msg = "Welcome to the future\n";
	int len, bytes_sent;
	len = strlen(msg);
	bytes_sent = send(new_socket, msg, len, 0);
	(void) bytes_sent;

		return true ;
}

// PAssword : checks if good / sends message if good only after getting nick and user 
// mutltiple commands . \r \n at the end of command. 
// Parse with split with spaces
// tableau de fonctions avec commandes correspondantes
// 

// bool                    checkPass();
// {

// }


// void					close()
// {
// 	// rm all users with delete and close sockets
// }

//void					receiveData();

void                    Server::setSock(int type, int protocol)
{
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = INADDR_ANY;
    _addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // fcntl(_sock, F_SETFD, O_NONBLOCK);
    if ((_sock = socket(_addr.sin_family, type, protocol)) < 0)
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

void                    Server::pollDispatch()
{
    std::list< User >::iterator     it = _usersList.begin();
    int                             usrNbr = _usersList.size();
    char buff[250];

    struct pollfd   pollarray[usrNbr];
    for (int i = 0; i < usrNbr; i ++)
    {
        pollarray[i].fd = (*it)._sockfd;
        it ++;
    }
    poll(pollarray, usrNbr, -1);
    int i = 0;
    while (i < usrNbr && pollarray[i].events & POLLIN)
    {
        std::cerr << "test" << std::endl;
        if (recv(pollarray[i].fd, buff, sizeof(buff), 0) > 0)
        {
            std::cerr << "test" << buff;
            memset(buff, 0, 250);
        }
        else
        {
            ;
        }
        //send to all channel users
        i ++;
    }
}

bool                    Server::addUser(int sockfd, sockaddr_in addr)
{
    // if bad passw
    User newUser(sockfd, addr);
    this->_usersList.push_back(newUser);
    //commande NICK et PASS
    return (true);
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
