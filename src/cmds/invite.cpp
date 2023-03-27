/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:57:47 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/27 15:23:20 by aandric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	Server::Invite(User &user, Message &message)
{
    if (!user.getRegistered())
    {
        reply(user, ERR_NOTREGISTERED(user.getReplyName(), user.getNickname()));
        return ;
    } 

    if (message._argsNb != 3)
    {
        reply(user, ERR_NEEDMOREPARAMS(user.getReplyName(), user.getNickname(), message._cmd));
        return ;
    }

    std::string nickname = message._arguments[0];
    std::string channel = message._arguments[1];
    if (channel.find("#") != 0) // check if right channel format
    {
        reply(user, ERR_NOSUCHCHANNEL(user.getReplyName(), user.getNickname(), channel));
        return ;
    }
    if (!isUserWNickname(nickname)) // check if nickname exists
    {
        reply(user, ERR_NOSUCHNICK(user.getReplyName(), user.getNickname(), nickname));
        return ;
    }
    if (!isChannel(channel)) // check if channel exists
     {
        reply(user, ERR_NOSUCHCHANNEL(user.getReplyName(), user.getNickname(), channel));
        return ;
    }
    else if (!_channelsListIt->isUserInChannel(user))  // check if user is on channel 
    {
        reply(user, ERR_NOTONCHANNEL(user.getReplyName(), user.getNickname(), channel));
        return ;
    }
    else if (_channelsListIt->isUserInChannelNickname(nickname)) // check if user already on channel 
    {
        reply(user, ERR_USERONCHANNEL(user.getReplyName(), channel, nickname));
        return ;
    }
    else
    {
        Channel *chan = getChannelWithName(channel);
        User *target = getUserWithNickname(nickname);

        target->getJoinedChans().push_back(chan);
        chan->getUsersList().push_back(target);

        reply(user, RPL_INVITING(user.getReplyName(), user.getNickname(), nickname, channel));
        reply(*target, user.getReplyName() + " INVITE " + nickname + " " + channel + "\n");
        joinRPL(*chan, *target);
        return ;
    }
}
