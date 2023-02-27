/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:23 by mgolinva          #+#    #+#             */
/*   Updated: 2023/02/14 14:59:15 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	Server::Quit(User &user, Message &message)
{
    std::string quit_msg;
    if (message._argsNb == 2)
    {
        message._it = message._splitMessage.begin() + 1;
        quit_msg = user.getNickname() + "@IRC_MAXANA QUIT: QUIT:" + *message._it;
        send(user.getSockfd(), quit_msg.c_str(), quit_msg.length(), 0); 
    }
    else
    {
        quit_msg = user.getNickname() + "@IRC_MAXANA QUIT: QUIT:";
        send(user.getSockfd(), quit_msg.c_str(), quit_msg.length(), 0); 
        // send to channels. Make a send a message to channels with user id 
    }
        // close connection
        // if a client quits without command auit, same behaviour as command wuit with reason known by the server
        // example : "Ping timeout: 120 seconds", "Excess Flood", and "Too many connections from this IP"

}