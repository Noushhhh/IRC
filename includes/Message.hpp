/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:58:22 by mgolinva          #+#    #+#             */
/*   Updated: 2023/01/27 12:58:22 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "irc.hpp"
#include "User.hpp"



class Message
{
public	:

	std::string							_rawMessage;
	std::vector <std::string>			_splitMessage;
	std::vector <std::string>::iterator	_it;
	size_t								_argsNb;

public	:

	Message();
	Message(std::string message);
	Message(const Message &src);
	~Message();
	
	Message &operator=(const Message &src);

	bool	Pass(std::string *splitMessage);
	bool	Nick(std::string *splitMessage);
	bool	User(std::string *splitMessage);
	bool	Quit(std::string *splitMessage);
	bool	Join(std::string *splitMessage);
	bool	Part(std::string *splitMessage);
	bool	Mode(std::string *splitMessage);
	bool	Topic(std::string *splitMessage);
	bool	Names(std::string *splitMessage);
	bool	List(std::string *splitMessage);
	bool	Invite(std::string *splitMessage);
	bool	Kick(std::string *splitMessage);
	bool	Msg(std::string *splitMessage);
	bool	Privmsg(std::string *splitMessage);
	bool	Notice(std::string *splitMessage);
	bool	Ping(std::string *splitMessage);
	bool	Pong(std::string *splitMessage);
	bool						splitMessage(); // add error pass in bool function
	bool						parseMessage();

};


#endif
