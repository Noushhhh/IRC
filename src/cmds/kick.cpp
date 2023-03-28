/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:57:55 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/27 16:29:23 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	Server::Kick(User &user, Message &message)
{
    if (!user.getRegistered())
    {
        reply(user, ERR_NOTREGISTERED(user.getReplyName(), user.getNickname()));
        return ;
    } 
    
    if (message._argsNb < 3)
    {
        reply(user, ERR_NEEDMOREPARAMS(user.getReplyName(), user.getNickname(), message._cmd));
        return ;
    }

    std::string channel_name = message._arguments[0];
    std::string nickname = message._arguments[1];
    if (message._arguments[0] == "IRC_NOUSHMAKS")
    {
        if (message._argsNb < 4)
        {
            reply(user, ERR_NEEDMOREPARAMS(user.getReplyName(), user.getNickname(), message._cmd));
            return ;
        }
        channel_name = message._arguments[1];
        nickname = message._arguments[2].substr(1);
    }
    
    Channel *chan = getChannelWithName(channel_name);
    if (!isChannel(channel_name))
    {
        reply(user, ERR_NOSUCHCHANNEL(user.getReplyName(), user.getNickname(), channel_name));
        return ;
    }
    if (!user.isOnChan(channel_name))
    {
        reply(user, ERR_NOTONCHANNEL(user.getReplyName(), user.getNickname(), channel_name));
        return ;
    }
    if (!chan->userIsOp(user.getNickname()))
    {
        reply(user, ERR_NOPRIVILEGES(user.getReplyName()));
        return ;
    }
    
    if (!isUserWNickname(nickname))
    {
        reply(user, ERR_USERNOTINCHANNEL(user.getReplyName(), user.getNickname(), nickname, channel_name));
        return ;
    }
    if (!isUserOnChan(nickname, channel_name))
    {
        reply(user, ERR_USERNOTINCHANNEL(user.getReplyName(), user.getNickname(), nickname, channel_name));
        return ;
    }
    User    *target = getUserWithNickname(nickname);
    if (message._argsNb == 3)
    {
        sendChanUsers(channel_name, user.getReplyName() + " KICK " + channel_name + " " + nickname + "\n");
        chan->kickUser(target);
        return ;
    }
    if (message._argsNb > 3 && message._arguments[0] != "IRC_NOUSHMAKS")
    {
        sendChanUsers(channel_name, user.getReplyName() + " KICK " + channel_name + " " + nickname + " :" + get_suffix(&message._arguments[2]) + "\n");
        chan->kickUser(target);
        return ;
    }
    else
    {
        sendChanUsers(channel_name,  user.getReplyName() + " KICK " + channel_name + " " + nickname + " :" + get_suffix(&message._arguments[3]) + "\n");
        chan->kickUser(target);
        return ;
    }
}

