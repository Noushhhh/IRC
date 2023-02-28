/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:09 by mgolinva          #+#    #+#             */
/*   Updated: 2023/02/28 16:49:52 by aandric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	Server::Nick(User &user, Message &message)
{
	if (message._argsNb < 2)
	{
        _errMsg= ERR_NONICKNAMEGIVEN;
		send(user.getSockfd(), _errMsg.c_str(), _errMsg.length(), 0);
		return ;
	}
    message._it = message._splitMessage.begin() + 1;
    std::string nickname = *message._it;
	for (_usersListIt = _usersList.begin(); _usersListIt != _usersList.end(); _usersListIt++)
	{
        std::cout << "nickname user " << _usersListIt->getNickname() << std::endl;
        std::cout << "nickname givem" << nickname << std::endl;
		if (_usersListIt->getNickname() == nickname)
        {
            _errMsg = ERR_NICKNAMEINUSE(nickname);
            send(user.getSockfd(), _errMsg.c_str(), _errMsg.length(), 0);
            return ;
        }
	}
    for (size_t i = 0; i < nickname.length(); i++)
    {
        if (!isprint(nickname[i]))
        {
            _errMsg = ERR_ERRONEUSNICKNAME(nickname);
            send(user.getSockfd(), _errMsg.c_str(), _errMsg.length(), 0);
            return ;
        }
    }
    if (!user.getRegistered())
    {
        user.setNickname(nickname);
        std::string nickmsg = "New nick in use: " + nickname;
        send(user.getSockfd(), nickmsg.c_str(), nickmsg.length(), 0);
    }
    else
    {
        std::string nickmsg = user.getNickname() + "changed his nickname to: " + nickname;
        send(user.getSockfd(), nickmsg.c_str(), nickmsg.length(), 0);
        user.setNickname(nickname);
    }
}
