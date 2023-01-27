/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:58:06 by mgolinva          #+#    #+#             */
/*   Updated: 2023/01/27 12:58:06 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"
#include "../includes/Replies.hpp"


Replies::Replies()
{
	// std::cerr << "Debug message: Replies Default Constructor called" << std::endl;
}

Replies::Replies(const Replies &src)
{
	*this = classInstance;
	// std::cerr << "Debug message: Replies Default Copy Constructor called" << std::endl;
}

Replies::~Replies()
{
	// std::cerr << "Debug message: Replies Default Destructor called" << std::endl;
}

Classename &Replies::operator=(const Replies &src)
{
	
}
