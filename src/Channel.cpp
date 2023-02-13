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
	;
}

Channel::Channel(const std::string &name, User &chanCreator) :
_identifier(""), 
_nameErrorSrc(""),
_password("")
{
	//must check for duplicate name in creation command
	if (!isNameValid(name))
		throw (Channel::BadNameException(_nameErrorSrc));
	_name = name;
	if (_type != UNMOD)
		_creator = chanCreator;
	_isPswdProtected = false;
	_usersList.push_back(chanCreator);
}

Channel::Channel(const std::string &name, const std::string &pswd, User &chanCreator) :
_identifier(""), 
_nameErrorSrc("")
{
	if (!isNameValid(name))
		throw (Channel::BadNameException(_nameErrorSrc));
	_name = name;
	if (_type != UNMOD)
		_creator = chanCreator;
	_password = pswd;
	_isPswdProtected = true;
	_usersList.push_back(chanCreator);
}

Channel::Channel(const Channel &src)
{
	*this = src;
}

Channel::~Channel()
{
	;
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
	std::string			Channel::getIdentifier()	const {return (_identifier);}
	std::string			Channel::getNameErrorSrc()	const {return (_nameErrorSrc);}
	std::string			Channel::getPswd()			const {return (_password);}
	bool				Channel::getPswdStatus()	const {return (_isPswdProtected);}
	User				Channel::getChanCreator()	const {return (_creator);}
	std::list< User >	Channel::getUsersList()		const {return (_usersList);}
	std::list< User >	Channel::getOpList()		const {return (_opList);}
	char				Channel::getType()			const {return (_type);}

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
			_type = LOCAL;
			break ;
		case '#' :
			_type = REGULAR;
			break ;
		case '+' :
			_type = UNMOD;
			break ;
		case '!' :
			_nameErrorSrc = "safe channels must be created using JOIN cmd";
			return (false);
		default :
			_nameErrorSrc = "channels's names must start with '&' '#' '+' or '!'";
			return (false);
	}
	if (name.size() == 1)
	{
		_nameErrorSrc = "channel's name cannot only contain channel type specfier";
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