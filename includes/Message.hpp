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

#define HANDLEDCOMMANDSNB 17

class Message
{
public	:

	User							&_fromUser;
	std::list <Channel>				&_channelList;
	std::string						_message;
	std::string						_handledCommands[HANDLEDCOMMANDSNB];
	size_t							_argsNb;
	bool							(Message::*_ptrF[HANDLEDCOMMANDSNB])(std::string *splitMessage);
	// std::string						*_commands;
	// std::string						*_parameters;

public	:

	Message();
	Message(std::list <User> &user_list, std::list<Channel> &channel_list, User &from_user, std::string message);
	Message(const Message &src);
	~Message();
	
	Message &operator=(const Message &src);

	std::string*	splitMessage();
	bool			parseMessage();

	bool	Pass(std::string *splitMessage);
	bool	Nick(std::string *splitMessage);
	// bool	User(std::string *splitMessage);
	// bool	Quit(std::string *splitMessage);
	// bool	Join(std::string *splitMessage);
	// bool	Part(std::string *splitMessage);
	// bool	Mode(std::string *splitMessage);
	// bool	Topic(std::string *splitMessage);
	// bool	Names(std::string *splitMessage);
	// bool	List(std::string *splitMessage);
	// bool	Invite(std::string *splitMessage);
	// bool	Kick(std::string *splitMessage);
	// bool	Msg(std::string *splitMessage);
	// bool	Privmsg(std::string *splitMessage);
	// bool	Notice(std::string *splitMessage);
	// bool	Ping(std::string *splitMessage);
	// bool	Pong(std::string *splitMessage);

};

// USER

// PASS
// NICK
// USER
// QUIT
// 

// CHANNEL
// JOIN
// PART
// MODE :  O - give "channel creator" status;
        // o - give/take channel operator privilege;
        // v - give/take the voice privilege; + si affinite mais pas oblige
// TOPIC
// NAMES
// LIST
// INVITE
// KICK

// MSG
// PRIVMSG
// NOTICE - same as privmsg pour les bots (a bot never receives message when calling notice)

// MISCELLANEOUS
// PING
// PONG

#endif
