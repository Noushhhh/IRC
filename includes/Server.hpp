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

#include "irc.hpp"
#include "User.hpp"
#include "Channel.hpp"

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
        bool                    closeUser(std::vector< struct pollfd >::iterator it);

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

        Server();
        Server(const Server & newServ);
        Server &operator=(const Server & newServ);
};

#endif