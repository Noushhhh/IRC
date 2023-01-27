/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:58:06 by mgolinva          #+#    #+#             */
/*   Updated: 2023/01/27 12:58:06 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"
#include "../includes/Message.hpp"


Message::Message()
{
	// std::cerr << "Debug message: Message Default Constructor called" << std::endl;
}

Message::Message(const Message &src)
{
	*this = classInstance;
	// std::cerr << "Debug message: Message Default Copy Constructor called" << std::endl;
}

Message::~Message()
{
	// std::cerr << "Debug message: Message Default Destructor called" << std::endl;
}

Classename &Message::operator=(const Message &src)
{
	
}
