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

#define HANDLEDCOMMANDS "{ "PASS", "NICK", "USER", "QUIT", "JOIN", "PART", "MODE", "TOPIC", "NAMES", "LIST", "INVITE", "KICK", "MSG", "PRIVMSG", "NOTICE", "PING", "PONG" }"
#define HANDLEDCOMMANDSNB 17

class Message
{
public	:

	std::string						_message;

	bool							_isRequest;
	std::string						_handledCommands[HANDLEDCOMMANDSNB];
	void							(Message::*_ptrF[HANDLEDCOMMANDSNB])(std::string command, std::string parameters);
	// std::string						*_commands;
	// std::string						*_parameters;

public	:

	Message();
	Message(std::string message);
	Message(const Message &src);
	~Message();
	
	Message &operator=(const Message &src);

	bool			isRequest();
	std::string*	splitMessage();
	bool			parseMessage();

	void	Pass(std::string *splitMessage);
	void	Nick(std::string *splitMessage);
	void	User(std::string *splitMessage);
	void	Quit(std::string *splitMessage);
	void	Join(std::string *splitMessage);
	void	Part(std::string *splitMessage);
	void	Mode(std::string *splitMessage);
	void	Topic(std::string *splitMessage);
	void	Names(std::string *splitMessage);
	void	List(std::string *splitMessage);
	void	Invite(std::string *splitMessage);
	void	Kick(std::string *splitMessage);
	void	Msg(std::string *splitMessage);
	void	Privmsg(std::string *splitMessage);
	void	Notice(std::string *splitMessage);
	void	Ping(std::string *splitMessage);
	void	Pong(std::string *splitMessage);

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
