/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:57:59 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/27 15:42:07 by aandric          ###   ########.fr       */
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
            _rplMsg = RPL_LIST(user.getReplyName(), user.getNickname(), _channelsListIt->getName(), chan_size.str(), _channelsListIt->getTopic());
            reply(user, _rplMsg);
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
        _rplMsg = RPL_LIST(user.getReplyName(), user.getNickname(), _channelsListIt->getName(), chan_size.str(), _channelsListIt->getTopic());
        send(user.getSockfd(), _rplMsg.c_str(), _rplMsg.length(), 0);
        chan_size.str("");
        
    }
    reply(user, RPL_LISTEND(user.getReplyName(), user.getNickname()));
    reply(user, _rplMsg);
    return ;
}
