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
private	:

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
	void						getArgs();

//getters
	std::string							getRawMessage(void) const;
	std::vector <std::string> 			getSplitMessage(void) const;
	std::string							getCmd(void) const;
	std::string							*getArguments(void);
	std::vector <std::string>::iterator	getIt(void) const;
	size_t								getArgsNb(void) const;

//setters

	void	setRawMessage(std::string rawMessage);
	void	setSplitMessage(std::vector <std::string> splitMessage);
	void	setCmd(std::string cmd);
	void	setArguments(std::string *arguments);
	void	setIt(std::vector <std::string>::iterator it);
	void	setArgsNb(size_t argsNb);


};


#endif
