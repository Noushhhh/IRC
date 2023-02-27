/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:59:15 by aandric           #+#    #+#             */
/*   Updated: 2023/01/27 17:14:08 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#define SOCKET 0
#define PROTOCOL 0
#define BIND 1
#define LISTEN 2
#define HANDLEDCOMMANDSNB 17

#include "irc.hpp"
#include "User.hpp"
#include "Channel.hpp"
#include "Message.hpp"

class Server
{
    public  :

        Server(int port, std::string password);
        ~Server();

// getters
        int                             getSock()           const;
        int                             getPort()           const;
        std::string                     getPassword()       const;
        struct sockaddr_in              getAdress()         const;
        std::list< User >::iterator     getUserListIt()     const;
        std::list< Channel >::iterator  getChanListIt()     const;
        std::list< User >               *getUserList();
        std::list< Channel >            *getChanList();

        std::list< User >::iterator      getUserItWithFd(int fd);
        // std::list< Command > &getCmdList()   const;

// setters
        bool                    init();
        void                    setSock(int type, int protocol);
        void                    bindSock();
        void                    listenTo(int backlog);

// functions
        bool                    checkPass();
		//void					close();
		//void					receiveData();
		
        bool                    pollDispatch();
        bool                    addUser();
        bool                    closeUser(std::vector< struct pollfd >::iterator &it);

        bool                    handleMessage(User &user, std::string raw_message);

// commands

    bool	Pass(User &user, Message &message); // ok
	bool	Nick(User &user, Message &message); // ok
	bool	cmdUser(User &user, Message &message); // ok
	bool	Quit(User &user, Message &message);
	bool	Join(User &user, Message &message);
	bool	Part(User &user, Message &message);
	bool	Mode(User &user, Message &message);
	bool	Topic(User &user, Message &message);
	bool	Names(User &user, Message &message);
	bool	List(User &user, Message &message);
	bool	Invite(User &user, Message &message);
	bool	Kick(User &user, Message &message);
	bool	Msg(User &user, Message &message);
	bool	Privmsg(User &user, Message &message);
	bool	Notice(User &user, Message &message);
	bool	Ping(User &user, Message &message);
	bool	Pong(User &user, Message &message);

// USER

// PASS
// NICK
// USER
// QUIT
// 

// CHANNEL
// JOIN
// PART
// MODE :  O - give "channel creator" status;
        // o - give/take channel operator privilege;
        // v - give/take the voice privilege; + si affinite mais pas oblige
// TOPIC
// NAMES
// LIST
// INVITE
// KICK

// MSG
// PRIVMSG
// NOTICE - same as privmsg pour les bots (a bot never receives message when calling notice)

// MISCELLANEOUS
// PING
// PONG


    class ServerException : public std::exception
    {
        private :
            int exceptionType;
        public  :
            ServerException(int exType);
            const std::string   errorMsg() const throw();
    };
    private :

        int                                     _sock;
        const int                               _port;
        const std::string                       _password;
        struct sockaddr_in                      _addr;
        std::vector< struct pollfd >            _pollFds; //element new a delete
        std::list< User >                       _usersList; //List d'utilisateurs du serveur
        std::list< User >::iterator             _usersListIt;
        std::list< Channel >                    _channelsList;
        std::list< Channel >::iterator          _channelsListIt;

    //message
        std::string						        _handledCommands[HANDLEDCOMMANDSNB];
        bool							        (Server::*_ptrF[HANDLEDCOMMANDSNB])(User &user, Message &message);

        Server();
        Server(const Server & newServ);
        Server &operator=(const Server & newServ);
};

#endif
