/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdUser.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:57:38 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/10 14:35:29 by aandric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	Server::cmdUser(User &user, Message &message)
{
    if (message._argsNb != 6)
    {
        // _errMsg = ERR_NEEDMOREPARAMS(message._cmd);
		// send(user.getSockfd(), _errMsg.c_str(), _errMsg.length(), 0);
        reply(user, ERR_NEEDMOREPARAMS(message._cmd));
        return ;
	}
    if (user.getRegistered())
    {
        // _errMsg = ERR_ALREADYREGISTERED;
		// send(user.getSockfd(), _errMsg.c_str(), _errMsg.length(), 0);
        reply(user, ERR_ALREADYREGISTERED);
        return ;
    }
    user.setUsername(message._arguments[0]);
    if ((message._arguments[1]).length() != 1 || !((message._arguments[1]).find_first_not_of("012345678")) || message._arguments[2] != "*")
    {
        // _errMsg = "wrong format for user mode: try: '0 *'\n";
        // send(user.getSockfd(), _errMsg.c_str(), _errMsg.length(), 0);
        reply(user, "wrong format for user mode: try: '0 *'\n");
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
        // _errMsg = ERR_PASSWDMISMATCH;
        // send(user.getSockfd(), _errMsg.c_str(), _errMsg.length(), 0);
        reply(user, ERR_PASSWDMISMATCH);
    }
    // _rplMsg = RPL_WELCOME(user.getNickname());
	// send(user.getSockfd(), _rplMsg.c_str(), _rplMsg.length(), 0);
    reply(user, RPL_WELCOME(user.getNickname()));
}
