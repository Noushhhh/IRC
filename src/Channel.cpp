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

Channel::Channel(const std::string &name)
{
	if (!isNameValid(name))
		throw (Channel::BadNameException(_nameErrorSrc));
	_name = name;
}

Channel::Channel(const Channel &src)
{
	*this = src;
	// std::cerr << "Debug message: Channel Default Copy Constructor called" << std::endl;
}

Channel::~Channel()
{
	// std::cerr << "Debug message: Channel Default Destructor called" << std::endl;
}

Channel &Channel::operator=(const Channel &src)
{
	this->_usersList = src._usersList;
	this->_name		= src._name;
	return (*this);
}

/**************************************************************/
/*                                                            */
/*                         GETTERS                            */
/*                                                            */
/**************************************************************/

	std::string			Channel::getName()			const {return (_name);}
	std::string			Channel::getNameErrorSrc()	const {return (_nameErrorSrc);}
	char				Channel::getType()			const {return (_type);}
	std::list< User >	Channel::getUsersList()		const {return (_usersList);}
	std::list< User >	Channel::getOpList()		const {return (_opList);}

/**************************************************************/
/*                                                            */
/*                      MEMBER FUNCTIONS                      */
/*                                                            */
/**************************************************************/

	bool				Channel::isNameValid(std::string name)
	{
		if (name.empty())
		{
			_nameErrorSrc = "channels's names cannot be blank";
			return (false);
		}
		else if (name.size() > 50)
		{
			_nameErrorSrc = "channels's names cannot be over 50 char";
			return (false);
		}
		switch (name[0])
		{
			case '&' :
				break ;
			case '#' :
				break ;
			case '+' :
				break ;
			case '!' :
				break ;
			default :
				_nameErrorSrc = "channels's names must start with '&' '#' '+' or '!'";
				return (false);
		}
		for (size_t i = 0; i < name.size(); i ++)
		{
			if (name[i] == ' ' || name[i] == 7 || name[i] == ',')
			{
				_nameErrorSrc = "channels's names cannot contain ' ', ^G or ','";
				return (false);
			}
		}
		return (true);
	}

/**************************************************************/
/*                                                            */
/*                      EXCEPTION CLASSES                     */
/*                                                            */
/**************************************************************/

Channel::BadNameException::BadNameException(std::string error) : errorSrc(error)
{
	;
}

std::string Channel::BadNameException::badName() const throw ()
{
	return (errorSrc);
}