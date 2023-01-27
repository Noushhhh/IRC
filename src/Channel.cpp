/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:58:06 by mgolinva          #+#    #+#             */
/*   Updated: 2023/01/27 12:58:06 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"
#include "../includes/Channel.hpp"


Channel::Channel()
{
	// std::cerr << "Debug message: Channel Default Constructor called" << std::endl;
}

Channel::Channel(const Channel &src)
{
	*this = classInstance;
	// std::cerr << "Debug message: Channel Default Copy Constructor called" << std::endl;
}

Channel::~Channel()
{
	// std::cerr << "Debug message: Channel Default Destructor called" << std::endl;
}

Classename &Channel::operator=(const Channel &src)
{
	
}
