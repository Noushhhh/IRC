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
#include "Server.hpp"


// class User;

class Channel
{
	private	:

		std::string			_name;
		std::string			_nameErrorSrc;
		std::string			_password; //optional
		std::string			_topic;
		User				*_creator;
		std::list< User *>	_usersList; //if empty, delete chan except if chan is SAFE
		size_t				_usersLimit; // set with -+l flag
		std::list< User *>	_mutedUsersList; // -+v
		std::list< User *>	_banUsersList; // -+b
		std::list< User *>	_opList; // +o
		char				_type;

		// channel's modes

		bool				_isPswdProtected;	// -+k
		bool				_isInviteOnly	;	// -+i
		bool				_isModerated	;	// -+m
		bool				_isQuiet		;	// -+q
		bool				_isNoOutsideMsg	;	// -+n
		bool				_isPrivate		;	// -+p
		bool				_isSecret		;	// -+s
		bool				_isTopicOPOnly	;	// -+t
		bool				_isUsersLimit	;	// +-l

	public	:

		Channel();
		Channel(const Channel &src);
		Channel & operator=(const Channel &src);
		Channel(const std::string &name, User &chanCreator);
		Channel(const std::string &name, const std::string &pswd, User &chanCreator);
		~Channel();

		/** MODES **/ 
		// see https://www.rfc-editor.org/rfc/rfc2811#section-4


		//getters

		std::list< User *>::iterator	getUserItInList(std::list< User *> &list, std::string name);
		std::string					getName()					   	  const;
		std::string					getNameErrorSrc()				  const;
		std::string					getPswd()						  const;
		std::string					getTopic()						  const;
		User						*getChanCreator()				  const;
		std::list< User *>			&getUsersList()			 	 		   ;
		std::list< User *>			&getOpList()			 	 		   ;
		std::list< User *>			&getMutedList()			 	 		   ;
		std::list< User *>			&getBanList()				 		   ;
		char						getType()						  const;
		size_t						getUsersLimit()					  const;
		bool						getPswdStatus()					  const;
		bool						getInviteStatus()				  const;
		bool						getModerationStatus()			  const;
		bool						getQuietStatus()				  const;
		bool						getOutsideMsgStatus()		      const;
		bool						getPrivacyStatus()				  const;
		bool						getSecrecyStatus()				  const;
		bool						getTopicStatus()				  const;
		bool						getUsersLimitStatus()		      const;

		//setters

		void						setPswd(User &user,std::string pswd, int &addOrRemove);
		void						setInviteMode(User &user,int &addOrRemove);
		void						setModerationMode(Server &serv, User &user,int &addOrRemove);
		void						setQuietMode(User &user,int &addOrRemove);
		void						setOutsideMsgMode(User &user,int &addOrRemove);
		void						setPrivateMode(User &user,int &addOrRemove);
		void						setSecretMode(User &user,int &addOrRemove);
		void						setTopicMode(User &user,int &addOrRemove);
		void						setUsersLimit(User &user, std::string userLimit, int &addOrRemove);
		void						setMutedList(User &user, User *target, int &addOrRemove);
		void						setBanList(Server &serv, User &user, User *target, int &addOrRemove);
		void						setOpList(User &user, User *target, int &addOrRemove);
		void						setTopic(std::string topic);
		
		//functions
		void						sendToUsers(std::string message);
		bool						isUserInChannel(User &user);
		bool						isUserInChannelNickname(std::string nickname);
		bool						isNameValid(std::string nickname);
		bool						userIsInChan(std::string nickname);
		bool						userIsOp(std::string nickname);
		bool 						userIsBanned(std::string nickname);
		bool 						userIsMuted(std::string nickname);


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
