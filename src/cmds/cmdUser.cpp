/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdUser.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:57:38 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/08 10:03:56 by aandric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	Server::cmdUser(User &user, Message &message)
{
    if (message._argsNb != 6)
    {
        _errMsg = ERR_NEEDMOREPARAMS(message._cmd);
		send(user.getSockfd(), _errMsg.c_str(), _errMsg.length(), 0);
        return ;
	}
    if (user.getRegistered())
    {
        _errMsg = ERR_ALREADYREGISTERED;
		send(user.getSockfd(), _errMsg.c_str(), _errMsg.length(), 0);
        return ;
    }
    user.setUsername(message._arguments[0]);
    if ((message._arguments[1]).length() != 1 || !((message._arguments[1]).find_first_not_of("012345678")) || message._arguments[2] != "*")
    {
        _errMsg = "wrong format for user mode: try: '0 *'\n";
        send(user.getSockfd(), _errMsg.c_str(), _errMsg.length(), 0);
        return ;
    }
    if (message._arguments[4].find(":") == 0)
    {
        std::string realname = message._arguments[4].substr(1) + " " + message._arguments[5];
        user.setRealname(realname);
    }
    if (user.getPassword() == this->getPassword())
        user.setRegistered();
    else
    {
        _errMsg = ERR_PASSWDMISMATCH;
        send(user.getSockfd(), _errMsg.c_str(), _errMsg.length(), 0);
    }
    std::string welcome_msg = RPL_WELCOME(user.getNickname());
	send(user.getSockfd(), welcome_msg.c_str(), welcome_msg.length(), 0);
}
