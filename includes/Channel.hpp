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

#define LOCAL	'&'	//the clients connected can only see and talk to other clients on the same server.
#define REGULAR '#' //is known to all servers that are connected to the network.
#define UNMOD	'+' //personne peut etre op ou chancreator
#define SAFE	'!' //se cree grace a la commande JOIN


class Channel
{
private	:

	std::string			_name;
	std::string			_nameErrorSrc;
	std::string			_password; //optional
	std::string			_topic;
	bool				_isPswdProtected;
	User				_creator;
	std::list< User >	_usersList; //if empty, delete chan except if char is SAFE
	std::list< User >	_opList;
	char				_type; //askip useless

public	:

	Channel();
	Channel(const Channel &src);
	Channel & operator=(const Channel &src);
	Channel(const std::string &name, User &chanCreator);
	Channel(const std::string &name, const std::string &pswd, std::string topic, User &chanCreator);
	~Channel();

	//getters

	std::string			getName()			const;
	std::string			getNameErrorSrc()	const;
	std::string			getPswd()			const;
	std::string			getTopic()			const;
	bool				getPswdStatus()		const;
	User				getChanCreator()	const;
	std::list< User >	getUsersList()		const;
	std::list< User >	getOpList()			const;
	char				getType()			const;
	
	//functions

	bool				isNameValid(std::string name);

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
