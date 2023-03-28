/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 09:23:12 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/28 10:39:16 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void    Server::Notice(User &user, Message &message)
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

    std::string target = message._arguments[0];
    
    if (message._argsNb < 3)
    {
        reply(user, ERR_NOTEXTTOSEND(user.getReplyName(), target));
        return ;
    }
    
    std::string priv_msg = get_suffix(&message._arguments[1]);
    Channel *chan = NULL;

    if ((target.find("#") == 0)) // supposed to be channel
    {
        std::string *channels = cppsplit(target, ',');
        for (size_t i = 0; i < ft_arraySize(channels); i ++)
        {
            chan = getChannelWithName(channels[i]);
            if (isChannel(channels[i])) // check that channel name valid
            {
                if (chan->userIsBanned(user.getNickname()))
                    ;
                else if (chan->userIsMuted(user.getNickname()))
                    ;
                else if (chan->getOutsideMsgStatus() == true && user.isOnChan(chan->getName()) == false)
                    reply(user, ERR_CANNOTSENDTOCHAN(user.getReplyName(), channels[i]));
                sendChanUsersExcept(user.getNickname(), channels[i], user.getReplyName() + " NOTICE " + channels[i] + " " + priv_msg + "\n");
            }
            else
                reply(user, ERR_NOSUCHCHANNEL(user.getReplyName(), user.getNickname(), target));
        }
        delete[] channels;
        return ;
    }
    else if (isUserWNickname(target)) // else check if message to user
    {
        reply(*getUserWithNickname(target), user.getReplyName() + " NOTICE " + target + " " + priv_msg + "\n");
        return ;
    }

    else
    {
        reply(user, ERR_NOSUCHNICK(user.getReplyName(), user.getNickname(), target));
    }
}