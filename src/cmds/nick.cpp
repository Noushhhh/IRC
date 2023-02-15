/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:09 by mgolinva          #+#    #+#             */
/*   Updated: 2023/02/14 14:59:05 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

bool	Server::Nick(User &user, Message &message)
{
	if (message._argsNb < 2)
	{
        std::string err_msg1 = ERR_NONICKNAMEGIVEN;
		send(user.getSockfd(), err_msg1.c_str(), err_msg1.length(), 0);
		return false;
	}
    message._it = message._splitMessage.begin() + 1;
    std::string nickname = *message._it;
	for (_usersListIt = _usersList.begin(); _usersListIt != _usersList.end(); _usersListIt++)
	{
        std::cout << "nickname user " << _usersListIt->getNickname() << std::endl;
        std::cout << "nickname givem" << nickname << std::endl;
		if (_usersListIt->getNickname() == nickname)
        {
            std::string err_msg2 = ERR_NICKNAMEINUSE(nickname);
            send(user.getSockfd(), err_msg2.c_str(), err_msg2.length(), 0);
            return false ;
        }
	}
    for (size_t i = 0; i < nickname.length(); i++)
    {
        if (!isprint(nickname[i]))
        {
            std::string err_msg3 = ERR_ERRONEUSNICKNAME(nickname);
            send(user.getSockfd(), err_msg3.c_str(), err_msg3.length(), 0);
            return false ;
        }
    }
    user.setNickname(nickname);
	return true ;
}

#define	ERR_NOSUCHNICK(nick)        nick + " :No such nick" // 401
#define ERR_NONICKNAMEGIVEN		    " :No nickname given" //431
#define ERR_ERRONEUSNICKNAME(nick)  nick + " :Erroneous nickname" //432 when a nick contains invalid char
#define ERR_NICKNAMEINUSE(nick)     nick + " :Nickname is in use" // 433