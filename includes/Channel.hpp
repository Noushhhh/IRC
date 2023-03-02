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
#define LOCAL	'&'	//the clients connected can only see and talk to other clients on the same server.
#define REGULAR '#' //is known to all servers that are connected to the network.
#define UNMOD	'+' //personne peut etre op ou chancreator
#define SAFE	'!' //se cree grace a la commande JOIN

#include "irc.hpp"
#include "User.hpp"


// class User;

class Channel
{
	private	:

		std::string			_name;
		std::string			_nameErrorSrc;
		std::string			_password; //optional
		std::string			_topic;
		User				_creator;
		std::list< User >	_usersList; //if empty, delete chan except if chan is SAFE
		int					_usersLimit; // set with -l flag
		std::list< User >	_mutedUsersList; // -+v
		std::list< User >	_banUsersList; // -+b
		std::list< User >	_opList;
		char				_type;


	public	:

		Channel();
		Channel(const Channel &src);
		Channel & operator=(const Channel &src);
		Channel(const std::string &name, User &chanCreator);
		Channel(const std::string &name, const std::string &pswd, User &chanCreator);
		~Channel();

		/** MODES **/ 
		// see https://www.rfc-editor.org/rfc/rfc2811#section-4

		bool				_isPswdProtected;	// -+k
		bool				_isInviteOnly	;	// -+i
		bool				_isModerated	;	// -+m
		bool				_isQuiet		;	// -+q
		bool				_isNoOutsideMsg	;	// -+n
		bool				_isPrivate		;	// -+p
		bool				_isSecret		;	// -+s
		bool				_isTopicOPOnly	;	// -+t

		//getters

		std::string			getName()			const;
		std::string			getNameErrorSrc()	const;
		std::string			getPswd()			const;
		std::string			getTopic()			const;
		bool				getPswdStatus()		const;
		User				getChanCreator()	const;
		std::list< User >	&getUsersList()			 ;
		std::list< User >	&getOpList()			 ;
		char				getType()			const;
		
		//functions

		bool				isNameValid(std::string name);
		bool				userIsOp(std::string name);

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
