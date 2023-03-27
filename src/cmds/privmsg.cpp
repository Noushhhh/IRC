/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:21 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/27 15:24:16 by aandric          ###   ########.fr       */
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
        reply(user, ERR_NEEDMOREPARAMS(user.getReplyName(), user.getNickname(), message._cmd));
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
            priv_msg = user.getReplyName() + " PRIVMSG " + target + " " + priv_msg + "\n";
            sendChanUsersExcept(user.getNickname(), target, priv_msg);
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
        priv_msg = user.getReplyName() + " PRIVMSG " + target + " " + priv_msg + "\n";
		send(getUserWithNickname(target)->getSockfd(), priv_msg.c_str(), priv_msg.length(), 0); // send priv message to the target
        return ;
    }

    else
    {
        reply(user, ERR_NOSUCHNICK(user.getReplyName(), user.getNickname(), target));
    }
}

