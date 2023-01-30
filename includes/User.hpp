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
		const int	_sockfd;
		const int	_username;
		std::string _nickname;

	// PASS Check if the passwd is ok if not reject user
	// NICK set nickename for user

	public	:

		User();
		User(int sockfd);
		User(const User &src);
		~User();
		
		User &operator=(const User &src);

		int		getSockfd() const;
};



#endif
