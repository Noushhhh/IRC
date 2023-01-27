/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:59:15 by aandric           #+#    #+#             */
/*   Updated: 2023/01/27 14:00:13 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#define SOCKET 0
#define PROTOCOL 0
#define BIND 1
#define LISTEN 2

#include "irc.hpp"

class Server
{
	public	:

		Server(int port, std::string password);
		~Server();

		int						getSock()		const;
		int						getPort()		const;
		std::string				getPassword()	const;
		struct sockaddr_in		getAdress()		const;
		// std::list< User >	&getUserList()	const;
		// std::list< Channel >	&getChanList()	const;
		// std::list< Command >	&getCmdList()	const;

		void					setSock(int type, int protocol);
		void					bindSock();
		void					listenTo(int backlog);

	class ServerException : public std::exception
	{
		private :
			int	exceptionType;
		public	:
			ServerException(int exType);
			const std::string	errorMsg() const throw();
	};
	private	:

		int					_sock;
		const int			_port;
		const std::string	_password;
		struct sockaddr_in	_addr;
		// std::list< User >	*_usersList; //List d'utilisateurs du serveur
		// std::list< Channel >	*_channelsList; //List d'utilisateurs du serveur
		// std::list< Comand >	*_comandsList; //List d'utilisateurs du serveur

		Server();
		Server(const Server & newServ);
		Server &operator=(const Server & newServ);
};

#endif