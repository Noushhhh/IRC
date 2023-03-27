/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:21 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/27 16:29:58 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	Server::PrivMsg(User &user, Message &message)
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
    if (message._argsNb < 3)
    {
        reply(user, ERR_NOTEXTTOSEND(user.getReplyName()));
        return ;
    }
    std::string target = message._arguments[0];
    std::string priv_msg = get_suffix(&message._arguments[1]);
    if (priv_msg[0] != ':')
    {
        reply(user, ERR_NOTEXTTOSEND(user.getReplyName()));
        return ;
    }
    Channel *chan = getChannelWithName(target);
    if ((target.find("#") == 0)) // supposed to be channel
    {
        if (isChannel(target)) // check that channel name valid
        {
            if (chan->userIsBanned(user.getNickname()))
                return ;
            else if (chan->userIsMuted(user.getNickname()))
                return ;
            else if (chan->getOutsideMsgStatus() == true && user.isOnChan(chan->getName()) == false)
            {
                reply(user, ERR_CANNOTSENDTOCHAN(user.getReplyName(), target));
                return ;
            }
            sendChanUsersExcept(user.getNickname(), target, user.getReplyName() + " PRIVMSG " + target + " " + priv_msg + "\n");
        }

        else
        {
            reply(user, ERR_NOSUCHCHANNEL(user.getReplyName(), user.getNickname(), target));
            return ;
        }
        return ;
    }
    else if (isUserWNickname(target)) // else check if message to user
    {
        reply(*getUserWithNickname(target), user.getReplyName() + " PRIVMSG " + target + " " + priv_msg + "\n");
        return ;
    }

    else
    {
        reply(user, ERR_NOSUCHNICK(user.getReplyName(), user.getNickname(), target));
    }
}

