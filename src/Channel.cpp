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
_nameErrorSrc(""),
_topic("")
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
_nameErrorSrc(""),
_topic("")
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
	this->_name				= src._name;
	this->_password			= src._password;
	this->_topic			= src._password;
	this->_isPswdProtected	= src._isPswdProtected;
	this->_creator			= src._creator;
	this->_usersList		= src._usersList;
	this->_opList			= src._opList;
	this->_type				= src._type;
	return (*this);
}

/**************************************************************/
/*                                                            */
/*                         GETTERS                            */
/*                                                            */
/**************************************************************/

	std::string			Channel::getName()			const {return (_name);}
	std::string			Channel::getNameErrorSrc()	const {return (_nameErrorSrc);}
	std::string			Channel::getPswd()			const {return (_password);}
	std::string			Channel::getTopic()			const {return (_topic);}
	bool				Channel::getPswdStatus()	const {return (_isPswdProtected);}
	User				Channel::getChanCreator()	const {return (_creator);}
	std::list< User >	&Channel::getUsersList()		  {return (_usersList);}
	std::list< User >	&Channel::getOpList()			  {return (_opList);}
	char				Channel::getType()			const {return (_type);}

/**************************************************************/
/*                                                            */
/*                      MEMBER FUNCTIONS                      */
/*                                                            */
/**************************************************************/

bool				Channel::isNameValid(std::string name)
{
	if (name[0] == '\0')
	{
		_nameErrorSrc = ": channels's names cannot be blank\n";
		return (false);
	}
	else if (name.size() > 50)
	{
		_nameErrorSrc = ": channels's names cannot be over 50 char\n";
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
			_nameErrorSrc = ": safe channels must be created using JOIN cmd\n";
			return (false);
		default :
			_nameErrorSrc = ": channels's names must start with '&' '#' '+' or '!'\n";
			return (false);
	}
	if (name.size() == 1)
	{
		_nameErrorSrc = ": channel's name cannot only contain channel type specfier\n";
		return (false);
	}
	for (size_t i = 0; i < name.size(); i ++)
	{
		if (name[i] == ' ' || name[i] == 7 || name[i] == ',')
		{
			_nameErrorSrc = ": channels's names cannot contain ' ', ^G or ','\n";
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