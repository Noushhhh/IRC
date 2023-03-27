/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:14 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/27 15:42:22 by aandric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	Server::Part(User &user, Message &message)
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
    std::string chan_name = message._arguments[0];
    if (!isChannel(chan_name))
    {
        reply(user, ERR_NOSUCHCHANNEL(user.getReplyName(), user.getNickname(), chan_name));
        return ;
    }
    Channel *channel = getChannelWithName(chan_name);
    if (!channel->isUserInChannel(user)) // check if user in channel
    {
        reply(user, ERR_NOTONCHANNEL(user.getReplyName(), user.getNickname(), chan_name));
        return ;
    }
    _rplMsg = user.getReplyName() + " PART " + chan_name + "\n";
    sendChanUsers(chan_name, _rplMsg);
    channel->kickUser(&user);
}
