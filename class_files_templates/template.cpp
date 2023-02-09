/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Classname.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:58:06 by mgolinva          #+#    #+#             */
/*   Updated: 2023/01/27 12:58:06 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"
#include "../includes/Classname.hpp"


Classname::Classname()
{
	// std::cerr << "Debug message: Classname Default Constructor called" << std::endl;
}

Classname::Classname(const Classname &src)
{
	*this = classInstance;
	// std::cerr << "Debug message: Classname Default Copy Constructor called" << std::endl;
}

Classname::~Classname()
{
	// std::cerr << "Debug message: Classname Default Destructor called" << std::endl;
}

Classename &Classname::operator=(const Classname &src)
{
	
}

/**************************************************************/
/*                                                            */
/*			               GETTERS                            */
/*                                                            */
/**************************************************************/

/**************************************************************/
/*                                                            */
/*			            MEMBER FUNCTIONS                      */
/*                                                            */
/**************************************************************/

/**************************************************************/
/*                                                            */
/*			            EXCEPTION CLASSES                     */
/*                                                            */
/**************************************************************/=