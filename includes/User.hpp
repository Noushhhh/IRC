/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:58:22 by mgolinva          #+#    #+#             */
/*   Updated: 2023/01/27 12:58:22 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
#define USER_HPP

#include "irc.hpp"

class Channel;

class User
{
	private	:
		int						_sockfd;
		sockaddr_in 			_addr;
		std::string 			_nickname;
		std::string				_givenPassword;
		bool					_isRegistered;
		std::string				_username;
		std::string				_realname;
		std::string				_ping;
		std::string				_pong;
		std::list < Channel *>	_joinedChannels;

	public	:
		User();
		User(int sockfd, sockaddr_in addr);
		User(const User &src);
        User &operator=(const User &src);
		~User();
		
//setter
		void					setPassword(std::string given_password);
		void					setNickname(std::string nickname);
		void					setRegistered(void);
		void					setUsername(std::string username);
		void					setRealname(std::string realname);
		void					setPing(std::string ping);
		void					setPong(std::string pong);

//getter
        int             		getSockfd()     const;
		std::string				getPassword()	const;
        std::string     		getNickname()   const;
		std::string             getReplyName();
		bool					getRegistered()   const;
		std::string				getUsername()	const;
		std::string				getRealname()	const;
		uint8_t         		getBitMode() const;
		std::string				getPing() const;
		std::string				getPong() const;
		std::list< Channel *>	&getJoinedChans();
		void                    freeJoinedChans();

//members functions

		bool					isOnChan(const std::string &cName);

};

#endif
