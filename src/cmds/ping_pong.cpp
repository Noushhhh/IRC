/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_pong.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:18 by mgolinva          #+#    #+#             */
/*   Updated: 2023/02/28 16:50:49 by aandric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	Server::Ping(User &user, Message &message)
{
    if (message._argsNb != 2)
    {
        _errMsg = ERR_NEEDMOREPARAMS(message._cmd);
        send(user.getSockfd(), _errMsg.c_str(), _errMsg.length(), 0);
    }
    // ERR_NOORIGIN (409) means empty string for token. same as needmore params...
    message._it = message._splitMessage.begin() + 1;
    user.setPing(*message._it);
    std::string pong_msg = "PONG IRC_MAXANA " + user.getPing();
    send(user.getSockfd(), pong_msg.c_str(), pong_msg.length(), 0);
}
