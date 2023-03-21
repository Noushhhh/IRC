/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:59:15 by aandric           #+#    #+#             */
/*   Updated: 2023/03/21 17:22:36 by aandric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#define SOCKET 0
#define PROTOCOL 0
#define BIND 1
#define LISTEN 2
#define HANDLEDCOMMANDSNB 15
#define SERVER "@NOUSHMAKSIRC"
#define HOST "127.0.0.1"

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
        int                                 getSock()           const;
        int                                 getPort()           const;
        std::string                         getPassword()       const;
        struct sockaddr_in                  getAdress()         const;
        std::list< User >::iterator         getUserListIt()     const;
        std::list< Channel >::iterator      getChanListIt()     const;
        std::list< User >                   *getUserList();
        std::list< Channel >                *getChanList();



// setters
        bool                                    init();
        void                                    setSock(int type, int protocol);
        void                                    bindSock();
        void                                    listenTo(int backlog);

// functions
        bool                                    checkPass();
		void                                    closeEmptyChans();
        //void					            close();
		//void					            receiveData();
		
        bool                                    pollDispatch();
        bool                                    addUser();
        bool                                    closeUser(std::vector< struct pollfd >::iterator &it);

        bool                                    handleMessage(User &user, std::string raw_message);
        bool                                    isChannel(std::string channel_name);
        bool                                    isUserWNickname(std::string user_name);
        bool                                    isUserOnChan(const std::string nickname, const std::string channel_name);
        Channel                                 *getChannelWithName(std::string channel_name);
        User                                    *getUserWithNickname(std::string nickname);
        std::list< User >::iterator             getUserItWithFd(int fd);
        std::list< Channel >::iterator          getChanItWithName(std::string name);
        std::vector< struct pollfd >::iterator  &findPollFd(int fd);
        void                                    sendChanUsers(std::string channel_name, std::string message);
        void                                    sendChanUsersExcept(std::string nick, std::string channel_name, std::string message);

// commands

    void	Pass(User &user, Message &message);
	void	Nick(User &user, Message &message);
	void	cmdUser(User &user, Message &message);
	void	Quit(User &user, Message &message); 
	void	Join(User &user, Message &message);
	void	Part(User &user, Message &message);
	void	Mode(User &user, Message &message);
    bool    modesSet(User &user, std::string modes, std::string *modesparams, std::list< Channel >::iterator &channel);
	void	Topic(User &user, Message &message);
	void	List(User &user, Message &message);
	void	Invite(User &user, Message &message);
	void	Kick(User &user, Message &message);
	void	PrivMsg(User &user, Message &message);
	void	Ping(User &user, Message &message);
    void	Cap(User &user, Message &message);
    void	Who(User &user, Message &message);
	void	Pong(User &user, Message &message);

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
        std::list< Channel >::iterator         _channelsListIt;
        std::string                             _rplMsg;
        std::string                             _errMsg;

    //message
        std::string						        _handledCommands[HANDLEDCOMMANDSNB];
        void							        (Server::*_ptrF[HANDLEDCOMMANDSNB])(User &user, Message &message);

        Server();
        Server(const Server & newServ);
        Server &operator=(const Server & newServ);
};

#endif
