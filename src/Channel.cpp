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
		_creator = &chanCreator;
	// else 
	// 	_creator = NULL;
	this->_isPswdProtected = false;
	this->_isInviteOnly		= false;	
	this->_isModerated		= false;		
	this->_isQuiet			= false;	
	this->_isNoOutsideMsg	= false;	
	this->_isPrivate		= false;
	this->_isSecret			= false;
	this->_isTopicOPOnly	= true;
	this->_isUsersLimit		= false;
	this->_usersLimit		= 0;
	_usersList.push_back(&chanCreator);
	_opList.push_back(&chanCreator);
}

Channel::Channel(const std::string &name, const std::string &pswd, User &chanCreator) :
_nameErrorSrc(""),
_topic("")
{
	if (!isNameValid(name))
		throw (Channel::BadNameException(_nameErrorSrc));
	_name = name;
	if (_type != UNMOD)
		_creator = &chanCreator;
	// else 
	// 	_creator = NULL;
	_password = pswd;
	this->_isPswdProtected = false;
	this->_isInviteOnly		= false;	
	this->_isModerated		= false;		
	this->_isQuiet			= false;	
	this->_isNoOutsideMsg	= false;	
	this->_isPrivate		= false;
	this->_isSecret			= false;
	this->_isTopicOPOnly	= true;
	this->_isUsersLimit		= false;
	this->_usersLimit		= 0;
	_usersList.push_back(&chanCreator);
	_opList.push_back(&chanCreator);
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
	this->_topic			= src._topic;
	this->_isPswdProtected	= src._isPswdProtected;
	this->_creator			= src._creator;
	this->_usersList		= src._usersList;
	this->_opList			= src._opList;
	this->_mutedUsersList	= src._mutedUsersList;
	this->_banUsersList		= src._banUsersList;
	this->_type				= src._type;
	this->_isPswdProtected	= src._isPswdProtected;
	this->_isInviteOnly		= src._isInviteOnly;	
	this->_isModerated		= src._isModerated;		
	this->_isQuiet			= src._isQuiet;	
	this->_isNoOutsideMsg	= src._isNoOutsideMsg;	
	this->_isPrivate		= src._isPrivate;
	this->_isSecret			= src._isSecret;
	this->_isTopicOPOnly	= src._isTopicOPOnly;
	this->_isUsersLimit		= src._isUsersLimit;
	this->_usersLimit		= src._usersLimit;		

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
	User						*Channel::getChanCreator()			const {return (_creator);}
	std::list< User *>			&Channel::getUsersList()		  		  {return (_usersList);}
	std::list< User *>			&Channel::getOpList()			  		  {return (_opList);}
	std::list< User *>			&Channel::getMutedList()			 	  {return (_mutedUsersList);}
	std::list< User *>			&Channel::getBanList()				 	  {return (_banUsersList);}
	std::list< User *>::iterator Channel::getUserItInList(std::list< User *> &list, std::string name)
	{
		std::list< User *>::iterator listEnd = list.end();

		for (std::list< User *>::iterator lit = list.begin(); lit != listEnd; lit ++)
		{
			
			if ((*lit)->getNickname() == name)
				return (lit);
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

void				Channel::setPswd(User &user, std::string pswd, int &addOrRemove)
{
	if (addOrRemove == ADD)
	{
		_password = pswd;
		_isPswdProtected = true;
		reply(user, this->getName().append(": Password protection successfully set\n"));
	}
	else
	{
		_password = "";
		_isPswdProtected = false;
		reply(user, this->getName().append(": Password protection successfully removed\n"));
	}
}
void				Channel::setInviteMode(User &user, int &addOrRemove)
{	
	if (addOrRemove == ADD)
	{
		_isInviteOnly = true;
		reply(user, this->getName().append(": Invite only mode successfully set\n"));
	}
	else
	{
		_isInviteOnly = false;
		reply(user, this->getName().append(": Invite only mode successfully removed\n"));
	}
}

void				Channel::setModerationMode(Server &serv, User &user, int &addOrRemove)
{
	std::list<User *>::iterator it;
	std::list<User *>::iterator end = _usersList.end();

	if (addOrRemove == ADD)
	{
		_isModerated = true;
		for (it = _usersList.begin(); it != end; it ++)
		{
			if (!userIsOp((*it)->getNickname()))
			{
				setMutedList(user, serv.getUserWithNickname((*it)->getNickname()), addOrRemove);
			}
		}
		reply(user, this->getName().append(": Moderation mode successfully set\n"));
	}
	else
	{
		_isModerated = false;
		reply(user, this->getName().append(": Moderation mode successfully removed\n"));
	}
}

void				Channel::setQuietMode(User &user, int &addOrRemove)
{
	// mute/unmute all standard user TO DO
	if (addOrRemove == ADD)
	{
		_isQuiet = true;
		reply(user, this->getName().append(": Quiet mode successfully set\n"));
	}
	else
	{
		_isQuiet = false;
		reply(user, this->getName().append(": Quiet mode successfully removed\n"));
	}
}

void				Channel::setOutsideMsgMode(User &user, int &addOrRemove)
{
	if (addOrRemove == ADD)
	{
		_isNoOutsideMsg = true;
		reply(user, this->getName().append(": No Outside message mode successfully set\n"));
	}
	else
	{
		_isNoOutsideMsg = false;
		reply(user, this->getName().append(": No Outside message mode successfully removed\n"));
	}
}

void				Channel::setPrivateMode(User &user, int &addOrRemove)
{
	if (addOrRemove == ADD)
	{
		_isPrivate = true;
		reply(user, this->getName().append(": Private mode successfully set\n"));
	}
	else
	{
		_isPrivate = false;
		reply(user, this->getName().append(": Private mode successfully removed\n"));
	}
}

void				Channel::setSecretMode(User &user, int &addOrRemove)
{
	if (addOrRemove == ADD)
	{
		_isSecret = true;
		reply(user, this->getName().append(": Secret mode successfuly set\n"));
	}
	else
	{
		_isSecret = false;
		reply(user, this->getName().append(": Secret mode successfuly removed\n"));
	}
}

void				Channel::setTopicMode(User &user, int &addOrRemove)
{
	if (addOrRemove == ADD)
	{
		_isTopicOPOnly = true;
		reply(user, this->getName().append(": Topic set OP only mode successfuly set\n"));
	}
	else
	{
		_isTopicOPOnly = false;
		reply(user, this->getName().append(": Topic set OP only mode successfuly removed\n"));
	}
}

void				Channel::setUsersLimit(User &user, std::string userLimit, int &addOrRemove)
{
	if (addOrRemove == ADD)
	{
		for (size_t i = 0; i < userLimit.size(); i ++)
		{
			if (std::isdigit(userLimit[i]) == false)
			{
				reply(user, this->getName().append(": MODE +l: Users limit can only be an unsigned integer\n"));
				return ;
			}
		}
		if (static_cast< size_t >(std::atoi(userLimit.c_str())) < _usersList.size())
		{
			reply(user, this->getName().append(": MODE +l: Users limit cannot be less than actual channel's population.\n"));
			return ;
		}
		_usersLimit = static_cast< ssize_t >(std::atoi(userLimit.c_str()));
		_isUsersLimit = true;
		reply(user,  RPL_USERLIMITSET(_name, userLimit));
	}
	else
	{
		_isUsersLimit = false;
		reply(user, this->getName().append(": users limit successfully removed\n"));
	}
}

void				Channel::setMutedList(User &user, User *target, int &addOrRemove)
{
	if (target->getNickname() == _creator->getNickname())
		reply(user, ERR_ISCHANOP(target->getNickname()));
	else if (addOrRemove == REMOVE) // here remove = remove voice privilege, so -v is muting, +v is giving voice priv
	{
		if (this->getUserItInList(_mutedUsersList, target->getNickname()) != _mutedUsersList.end())
			reply(user, RPL_ALLRDYMUTED(target->getNickname(), this->getName())); // reply TO DO
		else
		{
			this->_mutedUsersList.push_back(target);
			reply(user, RPL_MUTED(target->getNickname(), this->getName()));
		}
	}
	else
	{
		if (this->getUserItInList(_mutedUsersList, target->getNickname()) != _mutedUsersList.end())
		{
			this->_mutedUsersList.erase(getUserItInList(_mutedUsersList, target->getNickname()));
			reply(user, RPL_UNMUTED(target->getNickname(), this->getName()));
		}
		else
			reply(user, RPL_NOTMUTED(target->getNickname(), this->getName()));
	}
}
void				Channel::setBanList(Server &serv, User &user, User *target, int &addOrRemove)
{	
	if (target->getNickname() == _creator->getNickname())
		reply(user, ERR_ISCHANOP(target->getNickname()));
	else if (addOrRemove == ADD)
	{
		if (this->getUserItInList(_banUsersList, target->getNickname()) != _banUsersList.end())
			reply(user, RPL_ALLRDYBANNED(target->getNickname(), this->getName()));
		else
		{
			reply(user, RPL_BANNED(target->getNickname(), this->getName()));
			if (this->getUserItInList(_opList, target->getNickname()) != _opList.end())
				this->_opList.erase(this->getUserItInList(_opList, target->getNickname()));
			if (this->getUserItInList(_mutedUsersList, target->getNickname()) != _mutedUsersList.end())
				this->_mutedUsersList.erase(this->getUserItInList(_mutedUsersList, target->getNickname()));
			
			this->_banUsersList.push_back(serv.getUserWithNickname(target->getNickname()));
			this->_usersList.erase(this->getUserItInList(_usersList, target->getNickname()));
		}
	}
	else
	{
		if (this->getUserItInList(_banUsersList, target->getNickname()) != _banUsersList.end())
		{
			this->_banUsersList.erase(getUserItInList(_banUsersList, target->getNickname()));
			reply(user, RPL_UNBANNED(target->getNickname(), this->getName()));
		}
		else
			reply(user, RPL_NOTBANNED(target->getNickname(), this->getName()));
	}
}

void				Channel::setOpList(User &user, User *target, int &addOrRemove)
{
	if (target->getNickname() == _creator->getNickname())
		reply(user, ERR_ISCHANOP(target->getNickname()));
	else if (addOrRemove == ADD)
	{
		if (this->getUserItInList(_opList, target->getNickname()) != _opList.end())
			reply(user, RPL_ALLRDYOP(target->getNickname(), this->getName()));
		else
		{
			this->_opList.push_back(target);
			reply (user, RPL_OPED(target->getNickname(), this->getName()));
		}
	}
	else
	{
		if (this->getUserItInList(_opList, target->getNickname()) != _opList.end())
		{
			this->_opList.erase(getUserItInList(_opList, target->getNickname()));
			reply (user, RPL_UNOPED(target->getNickname(), this->getName()));
		}
		else
			reply(user, RPL_NOTOP(target->getNickname(), this->getName()));
	}
}

void				Channel::setTopic(std::string topic)
{
	_topic = topic;
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
		case '#' :
			_type = REGULAR;
			break ;
		default :
			_nameErrorSrc = ": channels's names must start with '#'\n";
			return (false);
	}
	if (name.size() >= 2 && name[0] == '#' && name[1] == '#')
	{
		_nameErrorSrc = ": channel's name cannot contain '#' appart from their first charachter\n";
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
	std::list < User *>::iterator it = _usersList.begin();
	while (it != _usersList.end())
	{
		send((*it)->getSockfd(), message.c_str(), message.length(), 0);
		it++;
	}
}

bool				Channel::isUserInChannel(User &user)
{
	std::list < User *>::iterator user_it = getUsersList().begin();
	std::list < User *>::iterator end = getUsersList().end();
	while (user_it != end)
	{
		if((*user_it)->getSockfd() == user.getSockfd())
			return true;
		user_it++;
	}
	return false;
}


bool				Channel::isUserInChannelNickname(std::string nickname)
{
	std::list < User *>::iterator user_it = getUsersList().begin();
	std::list < User *>::iterator end = getUsersList().end();
	while (user_it != end)
	{
		if((*user_it)->getNickname() == nickname)
			return true;
		user_it++;
	}
	return false;
}

bool 				Channel::userIsOp(std::string nickname)
{
	std::list< User *>::iterator listEnd = _opList.end();

	for (std::list< User *>::iterator lit = _opList.begin(); lit != listEnd; lit ++)
    {
        if ((*lit)->getNickname() == nickname)
        {
            return (true);
        }
    }
	return (false);
}

bool 				Channel::userIsBanned(std::string nickname)
{
	std::list< User *>::iterator listEnd = _banUsersList.end();

	for (std::list< User *>::iterator lit = _banUsersList.begin(); lit != listEnd; lit ++)
    {
        if ((*lit)->getNickname() == nickname)
        {
            return (true);
        }
    }
	return (false);
}

bool 				Channel::userIsMuted(std::string nickname)
{
	std::list< User *>::iterator listEnd = _mutedUsersList.end();

	for (std::list< User *>::iterator lit = _mutedUsersList.begin(); lit != listEnd; lit ++)
    {
        if ((*lit)->getNickname() == nickname)
        {
            return (true);
        }
    }
	return (false);
}

bool				Channel::userIsInChan(std::string nickname)
{
	std::list< User *>::iterator listEnd = _usersList.end();

	for (std::list< User *>::iterator lit = _usersList.begin(); lit != listEnd; lit ++)
    {
        if ((*lit)->getNickname() == nickname)
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