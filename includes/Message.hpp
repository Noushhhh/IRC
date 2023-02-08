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

	bool	isRequest();
	bool	parseMessage();

	void	Pass(std::string command, std::string parameters);
	void	Nick(std::string command, std::string parameters);
	void	User(std::string command, std::string parameters);
	void	Quit(std::string command, std::string parameters);
	void	Join(std::string command, std::string parameters);
	void	Part(std::string command, std::string parameters);
	void	Mode(std::string command, std::string parameters);
	void	Topic(std::string command, std::string parameters);
	void	Names(std::string command, std::string parameters);
	void	List(std::string command, std::string parameters);
	void	Invite(std::string command, std::string parameters);
	void	Kick(std::string command, std::string parameters);
	void	Msg(std::string command, std::string parameters);
	void	Privmsg(std::string command, std::string parameters);
	void	Notice(std::string command, std::string parameters);
	void	Ping(std::string command, std::string parameters);
	void	Pong(std::string command, std::string parameters);

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
