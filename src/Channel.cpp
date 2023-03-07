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
	this->_isPswdProtected = false;
	this->_isInviteOnly		= false;	
	this->_isModerated		= true;		
	this->_isQuiet			= false;	
	this->_isNoOutsideMsg	= false;	
	this->_isPrivate		= false;
	this->_isSecret			= false;
	this->_isTopicOPOnly	= true;
	this->_isUsersLimit		= false;
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
	this->_isPswdProtected = false;
	this->_isInviteOnly		= false;	
	this->_isModerated		= true;		
	this->_isQuiet			= false;	
	this->_isNoOutsideMsg	= false;	
	this->_isPrivate		= false;
	this->_isSecret			= false;
	this->_isTopicOPOnly	= true;
	this->_isUsersLimit		= false;
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
	this->_nameErrorSrc		= src._nameErrorSrc;
	this->_topic			= src._password;
	this->_isPswdProtected	= src._isPswdProtected;
	this->_creator			= src._creator;
	this->_usersList		= src._usersList;
	this->_opList			= src._opList;
	this->_mutedUsersList	= src._mutedUsersList;
	this->_banUsersList		= src._banUsersList;
	this->_opList			= src._opList;
	this->_type				= src._type;
	this->_isPswdProtected	= src._isPswdProtected;
	this->_isInviteOnly		= src._isInviteOnly;	
	this->_isModerated		= src._isModerated;		
	this->_isQuiet			= src._isQuiet;	
	this->_isNoOutsideMsg	= src._isNoOutsideMsg;	
	this->_isPrivate		= src._isPrivate;
	this->_isSecret			= src._isSecret;
	this->_isTopicOPOnly	= src._isTopicOPOnly;
	return (*this);
}

/**************************************************************/
/*                                                            */
/*                         GETTERS                            */
/*                                                            */
/**************************************************************/

	std::string					Channel::getName()					const {return (_name);}
	std::string					Channel::getNameErrorSrc()			const {return (_nameErrorSrc);}
	std::string					Channel::getPswd()					const {return (_password);}
	std::string					Channel::getTopic()					const {return (_topic);}
	User						Channel::getChanCreator()			const {return (_creator);}
	std::list< User >			&Channel::getUsersList()		  		  {return (_usersList);}
	std::list< User >			&Channel::getOpList()			  		  {return (_opList);}
	std::list< User >			&Channel::getMutedList()			 	  {return (_mutedUsersList);}
	std::list< User >			&Channel::getBanList()				 	  {return (_banUsersList);}
	std::list< User >::iterator	Channel::getUserItInList(std::list< User > list, std::string name)
	{
		std::list< User >::iterator listEnd = list.end();

		for (std::list< User >::iterator lit = list.begin(); lit != listEnd; lit ++)
		{
			if (lit->getNickname() == name)
			{
				return (lit);
			}
		}
		return (listEnd);
	}
	char						Channel::getType()					const {return (_type);}
	size_t						Channel::getUsersLimit()			const {return (_usersLimit);}
	bool						Channel::getPswdStatus()			const {return (_isPswdProtected);}
	bool						Channel::getInviteStatus()			const {return (_isInviteOnly);}
	bool						Channel::getModerationStatus()		const {return (_isModerated);}
	bool						Channel::getQuietStatus()			const {return (_isQuiet);}
	bool						Channel::getOutsideMsgStatus()		const {return (_isNoOutsideMsg);}
	bool						Channel::getPrivacyStatus()			const {return (_isPrivate);}
	bool						Channel::getSecrecyStatus()			const {return (_isSecret);}
	bool						Channel::getTopicStatus()			const {return (_isTopicOPOnly);}
	bool						Channel::getUsersLimitStatus()		const {return (_isUsersLimit);};

/**************************************************************/
/*                                                            */
/*                         SETTERS                            */
/*                                                            */
/**************************************************************/

void				Channel::setPswd(std::string pswd, int &addOrRemove)
{
	if (addOrRemove == ADD)
	{
		_password = pswd;
		_isPswdProtected = true;
	}
	else
	{
		_password = "";
		_isPswdProtected = false;
	}
}
void				Channel::setInviteMode(int &addOrRemove)
{
	if (addOrRemove == ADD)
		_isInviteOnly = true;
	else
		_isInviteOnly = false;
}

void				Channel::setModerationMode(int &addOrRemove)
{
	if (addOrRemove == ADD)
		_isModerated = true;
	else
		_isModerated = false;
}

void				Channel::setQuietMode(int &addOrRemove)
{
	if (addOrRemove == ADD)
		_isQuiet = true;
	else
		_isQuiet = false;
}

void				Channel::setOutsideMsgMode(int &addOrRemove)
{
	if (addOrRemove == ADD)
		_isNoOutsideMsg = true;
	else
		_isNoOutsideMsg = false;
}

void				Channel::setPrivateMode(int &addOrRemove)
{
	if (addOrRemove == ADD)
		_isPrivate = true;
	else
		_isPrivate = false;
}

void				Channel::setSecretMode(int &addOrRemove)
{
	if (addOrRemove == ADD)
		_isSecret = true;
	else
		_isSecret = false;
}

void				Channel::setTopicMode(int &addOrRemove)
{
	if (addOrRemove == ADD)
		_isTopicOPOnly = true;
	else
		_isTopicOPOnly = false;
}

void				Channel::setUsersLimit(User &user, std::string userLimit, int &addOrRemove)
{
	std::string err_buff;

	if (addOrRemove == ADD)
	{
		for (size_t i = 0; i < userLimit.size(); i ++)
		{
			if (std::isdigit(userLimit[i]) == false)
			{
				err_buff = ": MODE +l: Users limit can only be an unsigned integer\n";
        		send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
				return ;
			}
		}
		if (static_cast< size_t >(std::atoi(userLimit.c_str())) < _usersList.size())
		{
			err_buff = "MODE +l: Users limit cannot be less than actual channel's population.\n";
        	send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
			return ;
		}
		_usersLimit = static_cast< ssize_t >(std::atoi(userLimit.c_str()));
		_isUsersLimit = true;
	}
	else
		_isUsersLimit = false;
}

void				Channel::setMutedList(User &user, User &target, int &addOrRemove)
{
	std::string err_buff;

	if (target.isOnChan(this->getName()) == false)
	{
		err_buff = ERR_USERNOTINCHANNEL(target.getNickname(), this->getName());
		send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
		return;
	}
	if (addOrRemove == ADD)
	{
		this->_mutedUsersList.push_back(target);
		err_buff = RPL_MUTED(target.getNickname(), this->getName());
		send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
	}
	else
	{
		this->_mutedUsersList.erase(getUserItInList(_mutedUsersList, target.getNickname()));
		err_buff = RPL_UNMUTED(target.getNickname(), this->getName());
		send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
	}
}
void				Channel::setBanList(User &user, User &target, int &addOrRemove)
{	
	std::string err_buff;

	if (target.isOnChan(this->getName()) == false)
	{
		err_buff = ERR_USERNOTINCHANNEL(target.getNickname(), this->getName());
		send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
		return;
	}
	if (addOrRemove == ADD)
	{
		this->_banUsersList.push_back(target);
		err_buff = RPL_MUTED(target.getNickname(), this->getName());
		send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
	}
	else
	{
		this->_banUsersList.erase(getUserItInList(_banUsersList, target.getNickname()));
		err_buff = RPL_UNMUTED(target.getNickname(), this->getName());
		send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
	}
}

void				Channel::setOpList(User &user, User &target, int &addOrRemove)
{	
	std::string err_buff;

	if (target.isOnChan(this->getName()) == false)
	{
		err_buff = ERR_USERNOTINCHANNEL(target.getNickname(), this->getName());
		send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
		return;
	}
	if (addOrRemove == ADD)
	{
		this->_opList.push_back(target);
		err_buff = RPL_MUTED(target.getNickname(), this->getName());
		send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
	}
	else
	{
		this->_opList.erase(getUserItInList(_opList, target.getNickname()));
		err_buff = RPL_UNMUTED(target.getNickname(), this->getName());
		send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
	}
}

/**************************************************************/
/*                                                            */
/*                      MEMBER FUNCTIONS                      */
/*                                                            */
/**************************************************************/

bool				Channel::isNameValid(std::string name) // can contain multiple channel characters example :@#Channelname. To updadte ? function should be in Server so it can be used only with string
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

void				Channel::sendToUsers(std::string message)
{
	std::list < User >::iterator it = _usersList.begin();
	while (it != _usersList.end())
	{
		send(it->getSockfd(), message.c_str(), message.length(), 0);
		it++;
	}
}

bool				Channel::isUserInChannel(User &user)
{
	std::list < User >::iterator user_it = getUsersList().begin();
	while (user_it != getUsersList().end())
	{
		if(user_it->getSockfd() == user.getSockfd())
			return true;
		user_it++;
	}
	return false;
}


bool				Channel::isUserInChannelNickname(std::string nickname)
{
	std::list < User >::iterator user_it = getUsersList().begin();
	while (user_it != getUsersList().end())
	{
		if(user_it->getNickname() == nickname)
			return true;
		user_it++;
	}
	return false;
}

bool 				Channel::userIsOp(std::string nickname)
{
	std::list< User >::iterator listEnd = _opList.end();

	for (std::list< User >::iterator lit = _opList.begin(); lit != listEnd; lit ++)
    {
        if (lit->getNickname() == nickname)
        {
            return (true);
        }
    }
	return (false);
}

bool 				Channel::userIsBanned(std::string nickname)
{
	std::list< User >::iterator listEnd = _banUsersList.end();

	for (std::list< User >::iterator lit = _banUsersList.begin(); lit != listEnd; lit ++)
    {
        if (lit->getNickname() == nickname)
        {
            return (true);
        }
    }
	return (false);
}

bool 				Channel::userIsMuted(std::string nickname)
{
	std::list< User >::iterator listEnd = _mutedUsersList.end();

	for (std::list< User >::iterator lit = _mutedUsersList.begin(); lit != listEnd; lit ++)
    {
        if (lit->getNickname() == nickname)
        {
            return (true);
        }
    }
	return (false);
}

bool				Channel::userIsInChan(std::string nickname)
{
	std::list< User >::iterator listEnd = _usersList.end();

	for (std::list< User >::iterator lit = _usersList.begin(); lit != listEnd; lit ++)
    {
        if (lit->getNickname() == nickname)
        {
            return (true);
        }
    }
	return (false);
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