/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:05:55 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/21 11:37:27 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void    Server::Who(User &user, Message &message)
{
    // reply (user, RPL_WHOREPLY(rplname, channel, username, host, server, nick, flags, realname) rplname + " " + channel + " " + username + " " + host + " " + nick +  " " + flags + " :1 " + realname + "\n\r")
    (void) user;
    (void) message;
}