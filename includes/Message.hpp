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

	std::string						_rawMessage;
	std::vector <std::string>		_splitMessage;
	// std::string						_handledCommands[HANDLEDCOMMANDSNB];
	size_t							_argsNb;
	// bool							(Message::*_ptrF[HANDLEDCOMMANDSNB])();
	// std::string						*_commands;
	// std::string						*_parameters;

public	:

	Message();
	Message(std::string message);
	Message(const Message &src);
	~Message();
	
	Message &operator=(const Message &src);

	void						splitMessage(); // add error pass in bool function
	bool						parseMessage();

};


#endif
