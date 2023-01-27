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
#include "../includes/User.hpp"


User::User()
{
	// std::cerr << "Debug message: User Default Constructor called" << std::endl;
}

User::User(int sockfd) : _sockfd(sockfd)
{
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
	
}
