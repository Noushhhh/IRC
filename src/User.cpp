/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:58:06 by mgolinva          #+#    #+#             */
/*   Updated: 2023/01/27 12:58:06 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

User::User() : _nickname("noNick"), _isRegistered(false)
{
    // std::cerr << "Debug message: User Default Constructor called" << std::endl;
}

User::User(int sockfd, sockaddr_in addr) : _sockfd(sockfd), _addr(addr), _isRegistered(false)
{
    _nickname = "jambon";
    // std::cerr << "Debug message: User Default Constructor called" << std::endl;
}

User::User(const User &src) : _nickname("nonick")
{
    *this = src;
    // std::cerr << "Debug message: User Default Copy Constructor called" << std::endl;
}

User::~User()
{
    // std::cerr << "Debug message: User Default Destructor called" << std::endl;
}

User &User::operator=(const User &src)
{
    (void) _addr;
    this->_sockfd = src._sockfd;
    this->_username = src._username;
    this->_nickname = src._nickname;
    return (*this);
}

// setters

void    User::setPassword(std::string given_password)
{
	this->_givenPassword = given_password;
}

void    User::setNickname(std::string nickname)
{
	this->_nickname = nickname;
}

void    User::setRegistered(void)
{
    this->_isRegistered = true;
}

void    User::setUsername(std::string username)
{
	this->_username = username;
}

void    User::setRealname(std::string username)
{
	this->_username = username;
}

void    User::setPing(std::string ping)
{
    this->_ping = ping;
}

void    User::setPong(std::string pong)
{
    this->_pong = pong;
}

/**************************************************************/
/*                                                            */
/*                         GETTERS                            */
/*                                                            */
/**************************************************************/

int                     User::getSockfd()       const {return (_sockfd);}
std::string             User::getPassword()     const {return (_givenPassword);}
std::string             User::getNickname()     const {return (_nickname);}
bool			        User::getRegistered()   const { return (_isRegistered);};
std::string             User::getUsername()   const {return (_username);}
std::string             User::getRealname()   const {return (_realname);}
// uint8_t                 User::getBitMode() const {return (_bitMode);}
std::string		        User::getPing() const {return (_ping);}
std::string		        User::getPong() const {return (_pong);}
std::list< Channel >    &User::getJoinedChans()	    {return (_joinedChannels);}


/**************************************************************/
/*                                                            */
/*                         FUNCTIONS                          */
/*                                                            */
/**************************************************************/

bool					User::isOnChan(const std::string &cName)
{
    std::list< Channel >::iterator it = _joinedChannels.begin();
    for (; it != _joinedChannels.end(); it ++)
    {
        if (it->getName() == cName)
            return (true);
    }
    return (false);
}



