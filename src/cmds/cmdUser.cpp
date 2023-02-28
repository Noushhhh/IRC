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
    message._it = message._splitMessage.begin() + 1;
    user.setUsername(*message._it);
    message._it++;
    if ((*message._it).length() != 1 || !((*message._it).find_first_not_of("012345678")) || (*(message._it + 1) != "*"))
    {
        _errMsg = "wrong format for user mode: try: '0 *'\n";
        send(user.getSockfd(), _errMsg.c_str(), _errMsg.length(), 0);
        return ;
    }
    //user.setBitMode((uint8_t) atoi(*message._it)); ?? not needed ??
    message._it + 2;
    user.setRealname(*message._it + " " + *(message._it + 1));
    // split with separator ":" when merge with max spit function
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
