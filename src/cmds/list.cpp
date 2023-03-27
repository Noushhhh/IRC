/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:57:59 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/27 16:29:41 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	Server::List(User &user, Message &message)
{
    if (!user.getRegistered())
    {
        reply(user, ERR_NOTREGISTERED(user.getReplyName(), user.getNickname()));
        return ;
    } 
    
    if (message._argsNb < 1)
        return ;
    if (getChanList()->empty())
    {
        reply(user, RPL_LISTEND(user.getReplyName(), user.getNickname()));
        return ;
    }
    std::stringstream chan_size;
    if (message._argsNb == 1)
    {
        for (_channelsListIt = _channelsList.begin(); _channelsListIt != _channelsList.end(); _channelsListIt++)
        {
            if (_channelsListIt->getSecrecyStatus() == true)
                _channelsListIt++;
             chan_size << _channelsListIt->getUsersList().size();
            reply(user, RPL_LIST(user.getReplyName(), user.getNickname(), _channelsListIt->getName(), chan_size.str(), _channelsListIt->getTopic()));
            chan_size.str("");
        }
        reply(user, RPL_LISTEND(user.getReplyName(), user.getNickname()));
        return ;
    }

    for (size_t i = 0; i != (message._argsNb - 1); i++)
    {
        _channelsListIt = getChanItWithName(message._arguments[i]);
        if (_channelsListIt->getSecrecyStatus() == true)
            _channelsListIt++;
        chan_size << _channelsListIt->getUsersList().size();
        reply(user, RPL_LIST(user.getReplyName(), user.getNickname(), _channelsListIt->getName(), chan_size.str(), _channelsListIt->getTopic()));
        chan_size.str("");
        
    }
    reply(user, RPL_LISTEND(user.getReplyName(), user.getNickname()));
    reply(user, RPL_LIST(user.getReplyName(), user.getNickname(), _channelsListIt->getName(), chan_size.str(), _channelsListIt->getTopic()));
    return ;
}
