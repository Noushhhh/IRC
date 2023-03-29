/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:02:49 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/29 15:54:54 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

Server* Server::_servInstance = NULL;

Server::Server() :
_sock(0),
_port(9999),
_password("0000"),
_usersListIt(_usersList.begin()),
_channelsListIt(_channelsList.begin()),
_clientMsg(""),
_errMsg("")
{
    _servInstance = this;
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(_port);
    std::memset(_addr.sin_zero, 0, sizeof( _addr.sin_zero));

    this->_ptrF[0] = (&Server::Pass);
	this->_ptrF[1] = (&Server::Nick);
	this->_ptrF[2] = (&Server::cmdUser);
	this->_ptrF[3] = (&Server::Quit);
	this->_ptrF[4] = (&Server::Join);
	this->_ptrF[5] = (&Server::Part);
	this->_ptrF[6] = (&Server::Mode);
	this->_ptrF[7] = (&Server::Topic);
	this->_ptrF[8] = (&Server::List);
	this->_ptrF[9] = (&Server::Invite);
	this->_ptrF[10] = (&Server::Kick);
	this->_ptrF[11] = (&Server::PrivMsg);
	this->_ptrF[12] = (&Server::Ping);
    this->_ptrF[13] = (&Server::Cap);
    this->_ptrF[14] = (&Server::Who);
    this->_ptrF[15] = (&Server::Pong);
    this->_ptrF[16] = (&Server::Notice);

	this->_handledCommands[0] = "PASS";
	this->_handledCommands[1] = "NICK";
	this->_handledCommands[2] = "USER";
	this->_handledCommands[3] = "QUIT";
	this->_handledCommands[4] = "JOIN";
	this->_handledCommands[5] = "PART";
	this->_handledCommands[6] = "MODE";
	this->_handledCommands[7] = "TOPIC";
	this->_handledCommands[8] = "LIST";
	this->_handledCommands[9] = "INVITE";
	this->_handledCommands[10] = "KICK";
	this->_handledCommands[11] = "PRIVMSG";
	this->_handledCommands[12] = "PING";
    this->_handledCommands[13] = "CAP";
    this->_handledCommands[14] = "WHO";
    this->_handledCommands[15] = "PONG";
    this->_handledCommands[16] = "NOTICE";
}

Server::Server(int port, std::string password) :
_sock(0),
_port(port),
_password(password),
_usersListIt(_usersList.begin()),
_channelsListIt(_channelsList.begin()),
_clientMsg(""),
_errMsg("")
{
    _servInstance = this;
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(_port);
    std::memset(_addr.sin_zero, 0, sizeof( _addr.sin_zero));
 
    this->_ptrF[0] = (&Server::Pass);
	this->_ptrF[1] = (&Server::Nick);
	this->_ptrF[2] = (&Server::cmdUser);
	this->_ptrF[3] = (&Server::Quit);
	this->_ptrF[4] = (&Server::Join);
	this->_ptrF[5] = (&Server::Part);
	this->_ptrF[6] = (&Server::Mode);
	this->_ptrF[7] = (&Server::Topic);
	this->_ptrF[8] = (&Server::List);
	this->_ptrF[9] = (&Server::Invite);
	this->_ptrF[10] = (&Server::Kick);
	this->_ptrF[11] = (&Server::PrivMsg);
	this->_ptrF[12] = (&Server::Ping);
    this->_ptrF[13] = (&Server::Cap);
    this->_ptrF[14] = (&Server::Who);
    this->_ptrF[15] = (&Server::Pong);
    this->_ptrF[16] = (&Server::Notice);

	this->_handledCommands[0] = "PASS";
	this->_handledCommands[1] = "NICK";
	this->_handledCommands[2] = "USER";
	this->_handledCommands[3] = "QUIT";
	this->_handledCommands[4] = "JOIN";
	this->_handledCommands[5] = "PART";
	this->_handledCommands[6] = "MODE";
	this->_handledCommands[7] = "TOPIC";
	this->_handledCommands[8] = "LIST";
	this->_handledCommands[9] = "INVITE";
	this->_handledCommands[10] = "KICK";
	this->_handledCommands[11] = "PRIVMSG";
	this->_handledCommands[12] = "PING";
    this->_handledCommands[13] = "CAP";
    this->_handledCommands[14] = "WHO";
    this->_handledCommands[15] = "PONG";
    this->_handledCommands[16] = "NOTICE";
}

Server::Server(const Server &src) :
_port(src._port),
_password(src._password),
_addr(src._addr)
{
    *this = src;
}

Server &Server::operator=(const Server &src)
{
    this->_sock = src._sock;
    this->_addr = src._addr;
    this->_clientMsg = src._clientMsg;
    this->_servInstance = src._servInstance;
    _pollFds.clear();
    this->_pollFds = src._pollFds;

    return (*this);
}

Server::~Server()
{
    ;
}

/**************************************************************/
/*                                                            */
/*                         GETTERS                            */
/*                                                            */
/**************************************************************/

int                                 Server::getSock()           const   { return (_sock);           }
int                                 Server::getPort()           const   { return (_port);           }
std::string                         Server::getPassword()       const   { return (_password);       }
struct sockaddr_in                  Server::getAdress()         const   { return (_addr);           }
std::list< User >::iterator         Server::getUserListIt()     const   { return (_usersListIt);    }
std::list< Channel >::iterator      Server::getChanListIt()     const   { return (_channelsListIt); }
std::list< User >                   *Server::getUserList()              { return (&_usersList);      }
std::list< Channel >                *Server::getChanList()              { return (&_channelsList);   }


/**************************************************************/
/*                                                            */
/*                      MEMBER FUNCTIONS                      */
/*                                                            */
/**************************************************************/

void                    Server::setSock(int type, int protocol)
{
    
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = INADDR_ANY;
    _addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if ((_sock = socket(_addr.sin_family, type, protocol)) < 0)
	{
        throw (Server::ServerException(SOCKET));
	}
	int val = 1;
	if (setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)))
		throw (Server::ServerException(SOCKET));
	if (fcntl(_sock, F_SETFL, O_NONBLOCK < 0))
		throw (Server::ServerException(SOCKET));

    struct pollfd                           server_fd = {_sock, POLLIN, 0};

    _pollFds.push_back(server_fd);
}

void                    Server::bindSock()
{
    if (bind(_sock, (struct sockaddr *)&_addr, sizeof(_addr)) < 0)
        throw(Server::ServerException(BIND));
}

void                    Server::listenTo(int backlog)
{
    if (listen(_sock, backlog) < 0)
        throw(Server::ServerException(LISTEN));
}

bool                    Server::init()
{
    try
	{
		this->setSock(SOCK_STREAM, PROTOCOL);
		this->bindSock();
		this->listenTo(BACKLOG);
	}
	catch(const Server::ServerException &e)
	{
		std::cerr << e.errorMsg() << '\n';
		return false ;
	}
	return true ;
}

bool                    Server::pollDispatch()
{
    char buff[MAX_CHAR];

	while (1)
    {
		if (!_channelsList.empty())
			closeEmptyChans();
		if (poll (_pollFds.begin().base(), _pollFds.size(), -1) < 0)
        {
            serverShutdown();
            return (false);
        }
		for (_pollFdsIt = _pollFds.begin(); _pollFdsIt != _pollFds.end(); _pollFdsIt ++)
		{
            if (_pollFdsIt->events == 0)
                continue;
            else if ((_pollFdsIt->revents & POLLIN) == POLLIN)
            {
                if (_pollFdsIt->fd == _sock)
                {
                    if (this->addUser() == false)
                    {
                        serverShutdown();
                        return (false);
                    }
                    break ;
                }
                ssize_t r = 0;
                while (errno != EAGAIN && errno != EWOULDBLOCK)
                {
                    memset(buff, 0, MAX_CHAR);
                    r = recv(_pollFdsIt->fd, buff, MAX_CHAR - 1, MSG_DONTWAIT);
                    _clientMsg.append(std::string(buff));
                    if (r == 0)
                    {
                        if (!this->closeUser())
                        {
                            serverShutdown();
                            return (false);
                        }
                        break ;
                    }
                }
                std::vector <std::string> cmd_array = split_cmd(_clientMsg);
                _clientMsg.clear();
                for (std::vector<std::string>::iterator cmd_it = cmd_array.begin(); cmd_it != cmd_array.end(); cmd_it++)
                    handleMessage(*(getUserItWithFd(_pollFdsIt->fd)), *cmd_it);
                errno = 0;
            }
		}
	}
    return (true);
}


void					Server::closeEmptyChans()
{
	std::list< Channel >::iterator it = _channelsList.begin();
	std::list< Channel >::iterator buff;
	while (it != _channelsList.end())
	{
		if (it->getUsersList().empty() == true)
		{
			buff = it;
			it ++;
			_channelsList.erase(buff);
		}
		else
			it ++;
	}
}

bool                    Server::addUser()
{
    int                 newFd;
    struct sockaddr_in  newAddr;
    socklen_t           nSize = 0;

    newFd = accept(_sock, (struct sockaddr *)&newAddr, &nSize);
    if (newFd < 0)
        return (false);
    struct pollfd tmpfd;
    tmpfd.fd = newFd;
    tmpfd.events = POLLIN|POLLHUP;
    tmpfd.revents = 0;
    _pollFds.push_back(tmpfd);
    
    User newUser(newFd, newAddr);
    this->_usersList.push_back(newUser);
    return (true);
}

bool                    Server::closeUser()
{
    remove_from_all_channels(*getUserItWithFd(_pollFdsIt->fd), _channelsList);
    std::list< User >::iterator lit = _usersList.begin();
    for (; lit != _usersList.end(); lit ++)
    {
        if (lit->getSockfd() == _pollFdsIt->fd)
        {
            _usersList.erase(lit);
            break;
        }
    }
    if (close(_pollFdsIt->fd) < 0)
        return (true);
    _pollFds.erase(_pollFdsIt);
    _pollFdsIt = _pollFds.begin();
    return (true) ;
}

std::list< User >::iterator			Server::getUserItWithFd(int fd)
{
	std::list< User >::iterator listEnd = _usersList.end();

	for (std::list< User >::iterator lit = _usersList.begin(); lit != listEnd; lit ++)
    {
        if (lit->getSockfd() == fd)
            return lit;
    }
	return _usersList.end();
}

User                                *Server::getUserWithNickname(std::string nickname)
{
    std::list< User >::iterator listEnd = _usersList.end();

	for (std::list< User >::iterator lit = _usersList.begin(); lit != listEnd; lit ++)
    {
        if (lit->getNickname() == nickname)
        {
            return &(*lit);
        }
    }
	return NULL;
}

std::list< Channel >::iterator		Server::getChanItWithName(std::string name)
{
	std::list< Channel >::iterator listEnd = _channelsList.end();
	
	for (std::list< Channel >::iterator cit = _channelsList.begin(); cit != listEnd; cit ++)
    {
        if (cit->getName() == name)
            return (cit);
    }
	return (listEnd);
}

bool                    Server::handleMessage(User &user, std::string raw_message)
{
	std::string err_buff;
	if (raw_message.empty() || raw_message == "\n" || raw_message == "\r")
		return false ;
	Message message(raw_message);
		// check if user empty 
    if (!message.parseMessage())
        return false ;
    if (!message.splitMessage())
		return false ;
    int i = 0;
	message._it = message._splitMessage.begin();
	while(_handledCommands[i] != *message._it && i < HANDLEDCOMMANDSNB)
		i++;
	if (i >= HANDLEDCOMMANDSNB)
	{
		err_buff = ERR_UNKNOWNNCOMMAND(user.getReplyName(), user.getNickname(),*message._splitMessage.begin());
		send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
		return false;
	}
	else
	{
		(void)(this->*_ptrF[i])(user, message);
        return true;
	}

}

bool        Server::isChannel(std::string channel_name)
{
    if (getChanList()->empty())
        return false;
    if (channel_name.find("#") != 0)
        return false ;
    _channelsListIt = _channelsList.begin();
    while (_channelsListIt != _channelsList.end())
    {
        if (_channelsListIt->getName() == channel_name)
            return true ;
        _channelsListIt++;
    }
    return false ;
}

bool        Server::isUserWNickname(std::string nickname)
{
    std::list <User>::iterator user_it = getUserList()->begin();
    while (user_it != getUserList()->end())
    {
        if (user_it->getNickname() == nickname)
            return true ;
        user_it++;
    }
    return false ;
}

Channel    *Server::getChannelWithName(std::string channel_name)
{
    std::list <Channel>::iterator channel_it = getChanList()->begin();
    while (channel_it != getChanList()->end())
    {
        if (channel_it->getName() == channel_name)
            return &(*channel_it); // what to return if we want to send class channel ? check if pointer or not
        channel_it++;
    }
    return NULL; // or replace by exception 
    //return NULL;
}

bool					Server::isUserOnChan(const std::string nickname, const std::string channel_name)
{
    Channel *chan = getChannelWithName(channel_name);

    if (chan->isUserInChannel(*getUserWithNickname(nickname)))
        return (true);
    return (false);
}

void                    Server::sendChanUsers(std::string channel_name, std::string message)
{
    _channelsListIt = getChanList()->begin();
    while (_channelsListIt != getChanList()->end()) // send to users of the channel
    {
        if (_channelsListIt->getName() == channel_name)
        {
            _channelsListIt->sendToUsers(message);
        }
        _channelsListIt++;
    }
}

void                    Server::sendChanUsersExcept(std::string nick, std::string channel_name, std::string message)
{
    _channelsListIt = getChanList()->begin();
    while (_channelsListIt != getChanList()->end()) // send to users of the channel
    {
        if (_channelsListIt->getName() == channel_name)
        {
            _channelsListIt->sendToUsersExcept(nick, message);
        }
        _channelsListIt++;
    }
}

/**************************************************************/
/*                                                            */
/*                      EXCEPTION CLASSES                     */
/*                                                            */
/**************************************************************/

Server::ServerException::ServerException(int exType) : exceptionType(exType)
{
    ;
}

const std::string Server::ServerException::errorMsg() const throw()
{
    if (exceptionType == SOCKET)
    {
        std::string str = "error: socket: ";
        str.append(std::strerror(errno));
        return (str);
    }
    else if (exceptionType == BIND)
    {
        std::string str2 = "error: bind: ";
        str2.append(std::strerror(errno));
        return (str2);
    }
    else if (exceptionType == LISTEN)
    {
        std::string str3 = "error: listen: ";
        str3.append(std::strerror(errno));
        return (str3);
    }
    return ("jsp frere");
}
