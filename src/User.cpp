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

User::User()
{
    // std::cerr << "Debug message: User Default Constructor called" << std::endl;
}

User::User(int sockfd, sockaddr_in addr) : _sockfd(sockfd), _addr(addr)
{
    // _username = "jambon";
    _nickname = "jambon";
    // _realname = "jambon";
    // std::cerr << "Debug message: User Default Constructor called" << std::endl;
}

User::User(const User &src)
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
    this->_sockfd = src._sockfd;
    // this->_username = src._username;
    this->_nickname = src._nickname;
    return (*this);
}

void User::setPassword(std::string given_password)
{
	this->_givenPassword = given_password;
}

void User::setPNickname(std::string nickname)
{
	this->_nickname = nickname;
}

/**************************************************************/
/*                                                            */
/*                         GETTERS                            */
/*                                                            */
/**************************************************************/

int             User::getSockfd()     const {return (_sockfd);}
// std::string     User::getUsername()   const {return (_username);}
std::string     User::getNickname()   const {return (_nickname);}
// std::string     User::getRealname()   const {return (_realname);}
