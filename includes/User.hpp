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

class User
{
	private	:
		int			_sockfd;
		sockaddr_in _addr;
		std::string _nickname;
		std::string	_givenPassword;
		bool		_isRegistered;
		std::string	_username;
		std::string	_realname;
		uint8_t		_bitMode;

	public	:

		User();
		User(int sockfd, sockaddr_in addr);
		User(const User &src);
		~User();
		
//setter
		void			setPassword(std::string given_password);
		void			setNickname(std::string nickname);
		void			setRegistered(void);
		void			setUsername(std::string username);
		void			setRealname(std::string realname);
		void			setBitMode(uint8_t bit);

//getter
        int             getSockfd()     const;
		std::string		getPassword()	const;
        std::string     getNickname()   const;
		bool			getRegistered()   const;
		std::string		getUsername()	const;
		std::string		getRealname()	const;
		uint8_t         getBitMode() const;

        User &operator=(const User &src);
};

#endif
