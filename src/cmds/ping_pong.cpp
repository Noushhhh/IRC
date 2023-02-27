/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_pong.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:18 by mgolinva          #+#    #+#             */
/*   Updated: 2023/02/14 14:59:12 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	Server::Ping(User &user, Message &message)
{
    std::string err_msg;
    if (message._argsNb != 2)
    {
        err_msg = ERR_NEEDMOREPARAMS(message._cmd);
        send(user.getSockfd(), err_msg.c_str(), err_msg.length(), 0);
    }
    // ERR_NOORIGIN (409) means empty string for token. same as needmore params...
    message._it = message._splitMessage.begin() + 1;
    user.setPing(*message._it);
    std::string pong_msg = "PONG IRC_MAXANA " + user.getPing();
    send(user.getSockfd(), pong_msg.c_str(), pong_msg.length(), 0);
}

// bool	Server::Pong(User &user, Message &message)
// {
//     std::string err_msg;
//     if (message._argsNb != 3)
//     {
//         // err_msg = ERR_NEEDMOREPARAMS(message._cmd);
//         return false ;
//     }
//     message._it = message._splitMessage.begin() + 2;
//     if (*message._it != user.getPing())
//         return false ;
// 	return true ;
// }
