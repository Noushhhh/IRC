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
	;
}

Classname::Classname(const Classname &src)
{
	*this = classInstance;
}

Classname::~Classname()
{
	;
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