/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdUser.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:57:38 by mgolinva          #+#    #+#             */
/*   Updated: 2023/02/14 14:58:52 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

bool	cmdUser(User &user, Message &message)
{
    if (message._argsNb < 4)
    {
        std::string err_msg1 = ERR_NEEDMOREPARAMS(message._cmd);
		send(user.getSockfd(), err_msg1.c_str(), err_msg1.length(), 0);
		return false;
	}
    if (user.getRegistered())
    {
        std::string err_msg = ERR_ALREADYREGISTERED;
		send(user.getSockfd(), err_msg.c_str(), err_msg.length(), 0);
		return false;
    }
    message._it = message._splitMessage.begin() + 1;
    user.setUsername(*message._it);
    message._it++;
    int lol = std::stoi(*message._it);
   // user.setBitMode(stoi(*message._it));
    message._it + 2;
    user.setRealname(*message._it);
}

#define ERR_ALREADYREGISTERED	    ":Unauthorized command (already registered)" // 462, send as a response to a second USER call trying to overide user info 
