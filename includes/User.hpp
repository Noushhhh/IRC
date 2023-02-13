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
		int	_sockfd;
		sockaddr_in _addr;
		//const int	_username;
		std::string _nickname;
		std::string	_givenPassword;

	// PASS Check if the passwd is ok if not reject user
	// NICK set nickename for user

	public	:

		User();
		User(int sockfd, sockaddr_in addr);
		User(const User &src);
		~User();
		
//setter
		void setPassword(std::string given_password);
		void setNickname(std::string nickname);

//getter
		std::string		getPassword()	const;
        int             getSockfd()     const;
        std::string     getNickname()   const;


        User &operator=(const User &src);
};

#endif
