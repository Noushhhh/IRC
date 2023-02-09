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

class Server
{
    public  :

        Server(int port, std::string password);
        ~Server();

// getters
        int                     getSock()       const;
        int                     getPort()       const;
        std::string             getPassword()   const;
        struct sockaddr_in      getAdress()     const;
        std::list< User >       &getUserList()  const;
        // std::list< Channel > &getChanList()  const;
        // std::list< Command > &getCmdList()   const;

// setters
        void                    setSock(int type, int protocol);

// functions
        bool                    init();
        bool                    checkPass();
		//void					close();
		//void					receiveData();
		

        void                    bindSock();
        void                    listenTo(int backlog);

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
        std::list< class User >                 _usersList; //List d'utilisateurs du serveur
        // std::list< Channel > *_channelsList; //List d'utilisateurs du serveur
        // std::list< Comand >  *_comandsList; //List d'utilisateurs du serveur

        Server();
        Server(const Server & newServ);
        Server &operator=(const Server & newServ);
};

#endif