/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:57:55 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/21 14:27:08 by aandric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	Server::Kick(User &user, Message &message)
{
    if (message._argsNb < 3)
    {
        reply(user, ERR_NEEDMOREPARAMS(user.getReplyName(), message._cmd));
        return ;
    }
    std::string channel_name = message._arguments[0];
    Channel *chan = getChannelWithName(channel_name);
    if (!chan->userIsOp(user.getNickname()))
    {
        reply(user, ERR_NOPRIVILEGES(user.getReplyName()));
        return ;
    }
    if (!isChannel(channel_name))
    {
        reply(user, ERR_NOSUCHCHANNEL(user.getReplyName(), channel_name));
        return ;
    }
    if (!user.isOnChan(channel_name))
    {
        reply(user, ERR_NOTONCHANNEL(user.getReplyName(), channel_name));
        return ;
    }
    std::string nickname = message._arguments[1];
    if (!isUserWNickname(nickname))
    {
        reply(user, ERR_USERNOTINCHANNEL(user.getReplyName(), nickname, channel_name));
        return ;
    }
    if (!isUserOnChan(nickname, channel_name))
    {
        reply(user, ERR_NOTONCHANNEL(user.getReplyName(), channel_name));
        return ;
    }
    User    *target = getUserWithNickname(nickname);
    if (message._argsNb == 3)
    {
        _rplMsg = user.getReplyName() + " KICK " + channel_name + " " + nickname + "\n";
        sendToChanUsers(channel_name, _rplMsg);
        //kick user from chan
        chan->kickUser(target);
        return ;
    }
    if (message._argsNb > 3)
    {
        _rplMsg = "";
        _rplMsg = user.getReplyName() + " KICK " + channel_name + " " + nickname + " :" + get_suffix(&message._arguments[2]) + "\n";
        sendToChanUsers(channel_name, _rplMsg);
        chan->kickUser(target);
        //kick user from chan
        return ;
    }
}

// KICK message
//       Command: KICK
//    Parameters: <channel> <user> *( "," <user> ) [<comment>]
// The KICK command can be used to request the forced removal of a user from a channel. It causes the <user> to be removed from the <channel> by force. If no comment is given, the server SHOULD use a default message instead.

// The server MUST NOT send KICK messages with multiple users to clients. This is necessary to maintain backward compatibility with existing client software.

// Servers MAY limit the number of target users per KICK command via the TARGMAX parameter of RPL_ISUPPORT, and silently drop targets if the number of targets exceeds the limit.

// Numeric Replies:

// ERR_NEEDMOREPARAMS (461)
// ERR_NOSUCHCHANNEL (403)
// ERR_CHANOPRIVSNEEDED (482)
// ERR_USERNOTINCHANNEL (441)
// ERR_NOTONCHANNEL (442)
// Deprecated Numeric Reply:

// ERR_BADCHANMASK (476)
// Examples:

//    KICK #Finnish Matthew           ; Command to kick Matthew from
//                                    #Finnish

//    KICK &Melbourne Matthew         ; Command to kick Matthew from
//                                    &Melbourne

//    KICK #Finnish John :Speaking English
//                                    ; Command to kick John from #Finnish
//                                    using "Speaking English" as the
//                                    reason (comment).

//    :WiZ!jto@tolsun.oulu.fi KICK #Finnish John
//                                    ; KICK message on channel #Finnish
//                                    from WiZ to remove John from channel
