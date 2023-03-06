/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:02:49 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/06 17:13:09 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

Server::Server() :
_sock(0),
_port(9999),
_password("0000"),
_uIt(_usersList.begin()),
_cIt(_channelsList.begin())
{
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(_port);
    std::memset(_addr.sin_zero, 0, sizeof( _addr.sin_zero));

    this->_ptrF[0] = (&Server::Pass);
	this->_ptrF[1] = (&Server::Nick);
	// this->_ptrF[2] = (&Server::cmdUser);
	// this->_ptrF[3] = (&Server::Quit);
	// this->_ptrF[4] = (&Server::Join);
	// this->_ptrF[5] = (&Server::Part);
	// this->_ptrF[6] = (&Server::Mode);
	// this->_ptrF[7] = (&Server::Topic);
	// this->_ptrF[8] = (&Server::Names);
	// this->_ptrF[9] = (&Server::List);
	// this->_ptrF[10] = (&Server::Invite);
	// this->_ptrF[11] = (&Server::Kick);
	// this->_ptrF[12] = (&Server::Msg);
	// this->_ptrF[13] = (&Server::Privmsg);
	// this->_ptrF[14] = (&Server::Notice);
	// this->_ptrF[15] = (&Server::Ping);
	// this->_ptrF[16] = (&Server::Pong);

	this->_handledCommands[0] = "PASS";
	this->_handledCommands[1] = "NICK";
	this->_handledCommands[2] = "USER";
	this->_handledCommands[3] = "QUIT";
	this->_handledCommands[4] = "JOIN";
	this->_handledCommands[5] = "PART";
	this->_handledCommands[6] = "MODE";
	this->_handledCommands[7] = "TOPIC";
	this->_handledCommands[8] = "NAMES";
	this->_handledCommands[9] = "LIST";
	this->_handledCommands[10] = "INVITE";
	this->_handledCommands[11] = "KICK";
	this->_handledCommands[12] = "MSG";
	this->_handledCommands[13] = "PRIVMSG";
	this->_handledCommands[14] = "NOTICE";
	this->_handledCommands[15] = "PING";
	this->_handledCommands[16] = "PONG";
    // std::cerr << "Debug message: Server Default Constructor called" << std::endl;
}

Server::Server(int port, std::string password) :
_sock(0),
_port(port),
_password(password),
_uIt(_usersList.begin()),
_cIt(_channelsList.begin())
{
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(_port);
    std::memset(_addr.sin_zero, 0, sizeof( _addr.sin_zero));
 
    this->_ptrF[0] = (&Server::Pass);
	this->_ptrF[1] = (&Server::Nick);
	// this->_ptrF[2] = (&Server::cmdUser);
	// this->_ptrF[3] = (&Server::Quit);
	this->_ptrF[4] = (&Server::Join);
	// this->_ptrF[5] = (&Server::Part);
	this->_ptrF[6] = (&Server::Mode);
	// this->_ptrF[7] = (&Server::Topic);
	// this->_ptrF[8] = (&Server::Names);
	// this->_ptrF[9] = (&Server::List);
	// this->_ptrF[10] = (&Server::Invite);
	// this->_ptrF[11] = (&Server::Kick);
	// this->_ptrF[12] = (&Server::Msg);
	// this->_ptrF[13] = (&Server::Privmsg);
	// this->_ptrF[14] = (&Server::Notice);
	// this->_ptrF[15] = (&Server::Ping);
	// this->_ptrF[16] = (&Server::Pong);

	this->_handledCommands[0] = "PASS";
	this->_handledCommands[1] = "NICK";
	this->_handledCommands[2] = "USER";
	this->_handledCommands[3] = "QUIT";
	this->_handledCommands[4] = "JOIN";
	this->_handledCommands[5] = "PART";
	this->_handledCommands[6] = "MODE";
	this->_handledCommands[7] = "TOPIC";
	this->_handledCommands[8] = "NAMES";
	this->_handledCommands[9] = "LIST";
	this->_handledCommands[10] = "INVITE";
	this->_handledCommands[11] = "KICK";
	this->_handledCommands[12] = "MSG";
	this->_handledCommands[13] = "PRIVMSG";
	this->_handledCommands[14] = "NOTICE";
	this->_handledCommands[15] = "PING";
	this->_handledCommands[16] = "PONG";

    // std::cerr << "Debug message: Server Constructor called" << std::endl;
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
    return (*this);
}

Server::~Server()
{
    // std::cerr << "Debug message: Server Destructor called" << std::endl;
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
std::list< User >::iterator         Server::getUserListIt()     const   { return (_uIt);    }
std::list< Channel >::iterator      Server::getChanListIt()     const   { return (_cIt); }
std::list< User >                   *Server::getUserList()              { return (&_usersList);      }
std::list< Channel >                *Server::getChanList()              { return (&_channelsList);   }

// std::list< Command > &Server::getCmdList()   const   { return (commandsList);    }


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
    char                                    buff[MAX_CHAR];
    std::string                             msg;
    std::vector< struct pollfd >::iterator  it;

	while (1)
    {
		if (!_channelsList.empty())
			closeEmptyChans();
		if (poll (_pollFds.begin().base(), _pollFds.size(), -1) < 0)
            return (false);
		for (it = _pollFds.begin(); it != _pollFds.end(); it ++)
		{
            if (it->events == 0)
                continue;
            else if ((it->revents & POLLIN) == POLLIN)
            {
                if (it->fd == _sock)
                {
                    if (this->addUser() == false)
                    {
                        //close all sockets
                        return (false);
                    }
                    break ;
                }
                ssize_t r = 0;
                while (errno != EAGAIN && errno != EWOULDBLOCK)
                {
                    memset(buff, 0, MAX_CHAR);
                    r = recv(it->fd, buff, MAX_CHAR - 1, MSG_DONTWAIT);
                    msg.append(std::string(buff));
                    if (r == 0)
                    {
                        if (!this->closeUser(it))
                        {
                            // close all sockets
                            return (false);
                        }
                        break ;
                    }
                }
                std::cerr << msg;
				handleMessage(*(getUserItWithFd(it->fd)), msg); // check if reference of uesr good
                msg = "";
                errno = 0;
            }
		}
	}
    //free all except 1 and close all sockets
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
    // if bad passw
    int                 newFd;
    struct sockaddr_in  newAddr;
    socklen_t           nSize = 0;

    newFd = accept(_sock, (struct sockaddr *)&newAddr, &nSize);
    if (newFd < 0)
        return (false);
    struct pollfd *tmpfd = new struct pollfd;
    tmpfd->fd = newFd;
    tmpfd->events = POLLIN|POLLHUP;
    tmpfd->revents = 0;
    _pollFds.push_back(*tmpfd);

    User newUser(newFd, newAddr);
    this->_usersList.push_back(newUser);
    //commande NICK et PASS
    return (true);
}




bool                    Server::closeUser(std::vector< struct pollfd >::iterator &it)
{
    //supress from all channels he belongs to
	std::list< User >::iterator user = getUserItWithFd(it->fd);

	for (std::list < Channel >::iterator cit = _channelsList.begin(); cit != _channelsList.end(); cit ++)
	{
		for (std::list< User >::iterator lit = cit->getUsersList().begin(); lit != cit->getUsersList().end(); lit ++)
		{
			if (user->getNickname() == lit->getNickname())
			{
				cit->getUsersList().erase(lit);
				break ;
			}
		}
	}
	//close user FD
    for (std::list< User >::iterator lit = _usersList.begin(); lit != _usersList.end(); lit ++)
    {
        if (lit->getSockfd() == it->fd)
        {
            _usersList.erase(lit);
            break;
        }
    }
    if (close(it->fd) < 0)
        return (false);
    _pollFds.erase(it);
    it = _pollFds.begin();
    return (true) ;
}



std::list< User >::iterator			Server::getUserItWithFd(int fd)
{
	std::list< User >::iterator listEnd = _usersList.end();

	for (std::list< User >::iterator lit = _usersList.begin(); lit != listEnd; lit ++)
    {
        if (lit->getSockfd() == fd)
        {
            return (lit);
        }
    }
	return _usersList.end();
}

std::list< Channel >::iterator		Server::getChanWithName(std::string name)
{
	std::list< Channel >::iterator listEnd = _channelsList.end();
	
	for (std::list< Channel >::iterator cit = _channelsList.begin(); cit != listEnd; cit ++)
    {
        if (cit->getName() == name)
        {
            return (cit);
        }
    }
	throw(Channel::BadNameException(": Channel doesn't exist\n"));
	return (listEnd);
}

bool                    Server::handleMessage(User &user, std::string raw_message)
{
	std::string err_buff;
	if (raw_message.empty() || raw_message == "\n" || raw_message == "\r")
		return false ;
	//std::cout << std::endl << raw_message << std::endl;
	Message message(raw_message);
		// check if user empty 
	//std::cout << "sock number in handle msg: " << user.getSockfd();
    if (!message.parseMessage())
        return false ;
    if (!message.splitMessage())
		return false ;
    int i = 0;
	message._it = message._splitMessage.begin();
	while(_handledCommands[i] != *message._it && i < HANDLEDCOMMANDSNB)
		i++;
	// std::cout << "YO " << std::endl;
	// std::cout << "_handledCommands[0] = " << _handledCommands[0] << std::endl;
	// std::cout << "*message._it = " << *message._it << std::endl;
	// std::cout << "index handle message" << i << std::endl;
	if (i >= HANDLEDCOMMANDSNB)
	{
		err_buff = ERR_UNKNOWNNCOMMAND(*message._splitMessage.begin());
		send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
		return false;
	}
	else
	{
		message._argsNb = message._splitMessage.size();
		return (bool)(this->*_ptrF[i])(user, message);
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

/**************************************************************/
/*                                                            */
/*                      COMMANDS                              */
/*                                                            */
/**************************************************************/

bool	Server::Pass(User &user, Message &message)
{
	if (message._argsNb < 2)
	{
		send(user.getSockfd(), "ERR_NEEDMOREPARAMS", 18, 0); 
		return false;
	}
	if (user.getPassword().empty())
	{
		message._it = message._splitMessage.begin() + 1;
		user.setPassword(*message._it);
		return true;
	}
	else
	{
		send(user.getSockfd(), "ERR_ALREADYREGISTRED", 20, 0); 
		return false;
	}
	return true ;
}


bool	Server::Nick(User &user, Message &message)
{
	if (message._argsNb < 2)
	{
		send(user.getSockfd(), "ERR_NONICKNAMEGIVEN", 19, 0); 
		return false;
	}
	
	// ERR_ERRONEUSNICKNAME
	// std::list<User>::const_iterator it;
	// it = std::find()

	// for (std::list::const_iterator it = 0; it != this._channelList.size() )
	return true ;
}


// bool	cmdUser(User &user, Message &message);
// bool	Quit(User &user, Message &message);
// bool	Join(User &user, Message &message);
// bool	Part(User &user, Message &message);
// bool	Mode(User &user, Message &message);
// bool	Topic(User &user, Message &message);
// bool	Names(User &user, Message &message);
// bool	List(User &user, Message &message);
// bool	Invite(User &user, Message &message);
// bool	Kick(User &user, Message &message);
// bool	Msg(User &user, Message &message);
// bool	Privmsg(User &user, Message &message);
// bool	Notice(User &user, Message &message);
// bool	Ping(User &user, Message &message);
// bool	Pong(User &user, Message &message);
