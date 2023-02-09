/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:58:22 by mgolinva          #+#    #+#             */
/*   Updated: 2023/01/27 12:58:22 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "irc.hpp"
#include "User.hpp"

#define REGULAR '#' //is known to all servers that are connected to the network.
#define LOCAL	'&'	//the clients connected can only see and talk to other clients on the same server.
#define SAFE	'!' //jcrois osef
#define UNMOD	'+' //osef pareil je crois


class Channel
{
private	:

	Channel();

	std::string			_name;
	std::string			_nameErrorSrc;
	std::list< User >	_usersList;
	std::list< User >	_opList;
	char				_type;

public	:

	Channel(const Channel &src);
	Channel(const std::string &name);
	~Channel();

	//getters

	std::string			getName()			const;
	std::string			getNameErrorSrc()	const;
	char				getType()			const;
	std::list< User >	getUsersList()		const;
	std::list< User >	getOpList()			const;
	
	//functions

	bool				isNameValid(std::string name);

	//operators

	Channel 			&operator=(const Channel &src);

	//exceptions

	class BadNameException : public std::exception
	{
		private	:
			std::string	errorSrc;
		public	:
			~BadNameException() throw (){}
			BadNameException(std::string error);
			std::string badName() const throw();
	};
};



#endif
