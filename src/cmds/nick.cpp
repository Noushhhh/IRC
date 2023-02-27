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

void	Server::Nick(User &user, Message &message)
{
	if (message._argsNb < 2)
	{
        std::string err_msg1 = ERR_NONICKNAMEGIVEN;
		send(user.getSockfd(), err_msg1.c_str(), err_msg1.length(), 0);
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
            std::string err_msg2 = ERR_NICKNAMEINUSE(nickname);
            send(user.getSockfd(), err_msg2.c_str(), err_msg2.length(), 0);
            return ;
        }
	}
    for (size_t i = 0; i < nickname.length(); i++)
    {
        if (!isprint(nickname[i]))
        {
            std::string err_msg3 = ERR_ERRONEUSNICKNAME(nickname);
            send(user.getSockfd(), err_msg3.c_str(), err_msg3.length(), 0);
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
