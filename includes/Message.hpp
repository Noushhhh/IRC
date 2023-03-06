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
	std::string							_cmd;
	std::string							*_arguments;
	std::vector <std::string>::iterator	_it;
	size_t								_argsNb;

public	:

	Message();
	Message(std::string message);
	Message(const Message &src);
	~Message();
	
	Message &operator=(const Message &src);

	bool						splitMessage(); // add error pass in bool function
	bool						parseMessage();

};


#endif
