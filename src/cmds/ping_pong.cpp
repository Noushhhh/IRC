/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_pong.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:18 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/09 10:35:57 by aandric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	Server::Ping(User &user, Message &message)
{
    if (message._argsNb != 2)
    {
        _errMsg = ERR_NEEDMOREPARAMS(message._cmd);
        send(user.getSockfd(), _errMsg.c_str(), _errMsg.length(), 0);
        return ;
    }
    message._it = message._splitMessage.begin() + 1;
    user.setPing(*message._it);
    std::string pong_msg = "PONG IRC_MAXANA " + user.getPing();
    send(user.getSockfd(), pong_msg.c_str(), pong_msg.length(), 0);
}
