/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:25 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/27 15:42:47 by aandric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	Server::Topic(User &user, Message &message)
{
    if (!user.getRegistered())
    {
        reply(user, ERR_NOTREGISTERED(user.getReplyName(), user.getNickname()));
        return ;
    } 
    
    if (message._argsNb < 2)
    {
        reply (user, ERR_NEEDMOREPARAMS(user.getReplyName(), user.getNickname(), message._cmd));
        return ;
    }
    std::string channel_name = message._arguments[0];
    if (!isChannel(channel_name))
    {
        reply(user, ERR_NOSUCHCHANNEL(user.getReplyName(), user.getNickname(), channel_name));
        return ;
    }
    Channel *channel = getChannelWithName(channel_name);
    if (!channel->isUserInChannel(user))
    {
        reply(user, ERR_NOTONCHANNEL(user.getReplyName(), user.getNickname(), channel_name));
        return ;
    }

    if (message._argsNb == 2) // if user asks for topic of channel
    {
        if (channel->getTopic().empty())
        {
            reply(user, RPL_NOTOPIC(user.getReplyName(), user.getNickname(), channel_name));
            return ;
        }
        else
        {
            reply(user, RPL_TOPIC(user.getReplyName(), user.getNickname(), channel_name, channel->getTopic()));
            return ;
        }
    }
    
    if (message._argsNb > 2) // if user wants to set new topic 
    {
        std::string new_topic = get_suffix(&message._arguments[1]);
        new_topic = new_topic.substr(0);
        if (channel->getTopicStatus() == false || channel->userIsOp(user.getNickname()) == true) // check if user has the rights to set new topic
        {
            getChannelWithName(channel_name)->setTopic(new_topic);
            channel->sendToUsers(RPL_TOPIC(user.getReplyName(), user.getNickname(), channel_name, new_topic));
            return ;
        }
        else
        {
            reply(user, ERR_CHANOPRIVSNEEDED(user.getReplyName(), channel_name));
            return ;
        }
    }
}
