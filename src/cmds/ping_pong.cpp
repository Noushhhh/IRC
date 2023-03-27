/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_pong.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:18 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/27 15:24:05 by aandric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	Server::Ping(User &user, Message &message)
{
    if (!user.getRegistered())
    {
        reply(user, ERR_NOTREGISTERED(user.getReplyName(), user.getNickname()));
        return ;
    } 

    if (message._argsNb < 2)
    {
        reply(user, ERR_NOORIGIN(user.getReplyName(), user.getNickname()));
        return ;
    }
    if (message._arguments[0].empty())
    {
        reply(user, ERR_NOORIGIN(user.getReplyName(), user.getNickname()));
        return ;
    }

    reply(user, "PING :IRC_NOUSHMAKS\n");
}

void	Server::Pong(User &user, Message &message)
{
    if (!user.getRegistered())
    {
        reply(user, ERR_NOTREGISTERED(user.getReplyName(), user.getNickname()));
        return ;
    }

    if (message._argsNb < 2)
    {
        reply(user, ERR_NOORIGIN(user.getReplyName(), user.getNickname()));
        return ;
    }
    if (message._arguments[0].empty())
    {
        reply(user, ERR_NOORIGIN(user.getReplyName(), user.getNickname()));
        return ;
    }
    
    user.setPong(message._arguments[0]);
}
