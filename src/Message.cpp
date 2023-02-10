/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:58:06 by mgolinva          #+#    #+#             */
/*   Updated: 2023/01/27 12:58:06 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"
#include "../includes/Message.hpp"


Message::Message() : _message(""), // init members
{

	this->_ptrF[0] = (&Message::Pass);
	this->_ptrF[1] = (&Message::Nick);
	this->_ptrF[2] = (&Message::User);
	this->_ptrF[3] = (&Message::Quit);
	this->_ptrF[4] = (&Message::Join);
	this->_ptrF[5] = (&Message::Part);
	this->_ptrF[6] = (&Message::Mode);
	this->_ptrF[7] = (&Message::Topic);
	this->_ptrF[8] = (&Message::Names);
	this->_ptrF[9] = (&Message::List);
	this->_ptrF[10] = (&Message::Invite);
	this->_ptrF[11] = (&Message::Kick);
	this->_ptrF[12] = (&Message::Msg);
	this->_ptrF[13] = (&Message::Privmsg);
	this->_ptrF[14] = (&Message::Notice);
	this->_ptrF[15] = (&Message::Ping);
	this->_ptrF[16] = (&Message::Pong);

	this->_handledCommands[0] = "PASS";
	this->_handledCommands[1] = "NICK";
	this->_handledCommands[2] = "USER";
	this->_handledCommands[3] = "QUIT";
	this->_handledCommands[4] = "JOIN";
	this->_handledCommands[5] = "PART";
	this->_handledCommands[6] = "MODE";
	this->_handledCommands[7] = "TOPIC";
	this->_handledCommands[8] = "NAMES";
	this->_handledCommands[9] = "LIST";
	this->_handledCommands[10] = "INVITE";
	this->_handledCommands[11] = "KICK";
	this->_handledCommands[12] = "MSG";
	this->_handledCommands[13] = "PRIVMSG";
	this->_handledCommands[14] = "NOTICE";
	this->_handledCommands[15] = "PING";
	this->_handledCommands[16] = "PONG";

	// std::cerr << "Debug message: Message Default Constructor called" << std::endl;
}

Message::Message(User fromUser, std::string message) : _message(message), _fromUser(fromUser)
{
	this->_ptrF[0] = (&Message::Pass);
	this->_ptrF[1] = (&Message::Nick);
	this->_ptrF[2] = (&Message::User);
	this->_ptrF[3] = (&Message::Quit);
	this->_ptrF[4] = (&Message::Join);
	this->_ptrF[5] = (&Message::Part);
	this->_ptrF[6] = (&Message::Mode);
	this->_ptrF[7] = (&Message::Topic);
	this->_ptrF[8] = (&Message::Names);
	this->_ptrF[9] = (&Message::List);
	this->_ptrF[10] = (&Message::Invite);
	this->_ptrF[11] = (&Message::Kick);
	this->_ptrF[12] = (&Message::Msg);
	this->_ptrF[13] = (&Message::Privmsg);
	this->_ptrF[14] = (&Message::Notice);
	this->_ptrF[15] = (&Message::Ping);
	this->_ptrF[16] = (&Message::Pong);

	this->_handledCommands[0] = "PASS";
	this->_handledCommands[1] = "NICK";
	this->_handledCommands[2] = "USER";
	this->_handledCommands[3] = "QUIT";
	this->_handledCommands[4] = "JOIN";
	this->_handledCommands[5] = "PART";
	this->_handledCommands[6] = "MODE";
	this->_handledCommands[7] = "TOPIC";
	this->_handledCommands[8] = "NAMES";
	this->_handledCommands[9] = "LIST";
	this->_handledCommands[10] = "INVITE";
	this->_handledCommands[11] = "KICK";
	this->_handledCommands[12] = "MSG";
	this->_handledCommands[13] = "PRIVMSG";
	this->_handledCommands[14] = "NOTICE";
	this->_handledCommands[15] = "PING";
	this->_handledCommands[16] = "PONG";

} // init members

Message::Message(const Message &src)
{
	*this = src;
	// std::cerr << "Debug message: Message Default Copy Constructor called" << std::endl;
}

Message::~Message()
{
	// std::cerr << "Debug message: Message Default Destructor called" << std::endl;
}

Message &Message::operator=(const Message &src)
{

}

std::string * Message::splitMessage()
{
	char *string_to_split = new char[_message.length()+1];
	char *token = strtok(string_to_split, " ");
	std::string *split_message;
	int			it = 0;

	while(token != NULL)
	{
		split_message[it] = token;
		token = strtok(NULL, "\r \n");
		it++;
	}
	delete[] string_to_split;
	return (split_message);
}

bool Message::parseMessage()
{

	if (_message.empty()) 
	{
		std::cout << "empty message." << std::endl;
		return false;
	}

	std::string *split_mesage = splitMessage();

	int i = 0;
	while(i <= HANDLEDCOMMANDSNB)
	{
		if (_handledCommands[i] == split_mesage[0])
			break ;
		i++;
	}
	if (i > HANDLEDCOMMANDSNB) // check if > or >=
	{
		std::cout << "Not a request" << std::endl;
		return false;
	}
	size_t args_nb = sizeof(splitMsg) / sizeof(std::string);
	else
	{
		//int args_nb = sizeof(split_mesage) / sizeof(std::string);
		return (bool)(this->*_ptrF[i])(split_mesage);
	}
}


bool	Message::Pass(std::string *splitMsg)
{
	if (argsNb != 2)
	{
		std::cout << "error: message: pass: wrong number of arguments." << std::endl;
	}
	_fromUser->set


}


// bool	Nick(std::string *splitMsg);
// bool	User(std::string *splitMsg);
// bool	Quit(std::string *splitMsg);
// bool	Join(std::string *splitMsg);
// bool	Part(std::string *splitMsg);
// bool	Mode(std::string *splitMsg);
// bool	Topic(std::string *splitMsg);
// bool	Names(std::string *splitMsg);
// bool	List(std::string *splitMsg);
// bool	Invite(std::string *splitMsg);
// bool	Kick(std::string *splitMsg);
// bool	Msg(std::string *splitMsg);
// bool	Privmsg(std::string *splitMsg);
// bool	Notice(std::string *splitMsg);
// bool	Ping(std::string *splitMsg);
// bool	Pong(std::string *splitMsg);
