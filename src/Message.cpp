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
#include "../includes/User.hpp"

Message::Message() :  _rawMessage(""), _argsNb(0) // init members
{
	// std::cerr << "Debug message: Message Default Constructor called" << std::endl;
}

Message::Message(std::string message) : _rawMessage(message)
{

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
	_rawMessage = src._rawMessage;
	_argsNb = src._argsNb;
	return *this;
}

bool Message::splitMessage()
{
	char *string_to_split = new char[_rawMessage.length()+1];
	std::strcpy(string_to_split, _rawMessage.c_str());
	char *token = strtok(string_to_split, "\r \n");
	if (!token)
		return false ;
	while(token != NULL)
	{
		_splitMessage.push_back(token);
		token = strtok(NULL, "\r \n");
	}
	delete[] string_to_split;
	return true ;
}

bool Message::parseMessage()
{
	if (_rawMessage.empty()) 
	{
		std::cout << "empty message." << std::endl;
		return false;
	}
	

	return true ;
}

