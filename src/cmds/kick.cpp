/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:57:55 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/06 16:27:31 by aandric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	Server::Kick(User &user, Message &message)
{
    if (message._argsNb < 4)
    {
        _errMsg = ERR_NEEDMOREPARAMS(message._cmd);
        send(user.getSockfd(), _errMsg.c_str(), _errMsg.length(), 0);
        return ;
    }
    std::string channel_name = message._arguments[0];
    if (channel_name.find("#") != 0)
    {
        _errMsg = ERR_NOSUCHCHANNEL(channel_name);
        send(user.getSockfd(), _errMsg.c_str(), _errMsg.length(), 0);
        return ;
    }
    else
        channel_name = channel_name.substr(1);
    if (!isChannel(channel_name))
    {
        _errMsg = ERR_NOSUCHCHANNEL(channel_name);
        send(user.getSockfd(), _errMsg.c_str(), _errMsg.length(), 0);
        return ;
    }
    if (!user.isOnChan(channel_name))
    {
        _errMsg = ERR_NOTONCHANNEL(channel_name);
        send(user.getSockfd(), _errMsg.c_str(), _errMsg.length(), 0);
        return ;
    }
    std::string nickname = message._arguments[1];
    if (!isUserWNickname(nickname))
    {
        _errMsg = ERR_NOTONCHANNEL(channel_name);
        send(user.getSockfd(), _errMsg.c_str(), _errMsg.length(), 0);
        return ;
    }
    if (!isUserOnChan(nickname, channel_name))
    {
        _errMsg = ERR_NOTONCHANNEL(channel_name);
        send(user.getSockfd(), _errMsg.c_str(), _errMsg.length(), 0);
        return ;
    }
    if (message._argsNb == 3)
    {
        //kick user from chan
        _rplMsg = user.getNickname() + " @ IRC_MAXANA KICK #" + channel_name + nickname;
        send(user.getSockfd(), _errMsg.c_str(), _errMsg.length(), 0);
        return ;
    }
    if (message._argsNb > 3)
    {
        _rplMsg = "";
        for (int i = 3; i != message._argsNb; i++) // check if _argsNb one argument = 1 || one argument = 0
            _rplMsg = _rplMsg + message._arguments[i]; // build reply message with users' arguments
        _rplMsg = user.getNickname() + " @ IRC_MAXANA KICK #" + channel_name + nickname;
        send(user.getSockfd(), _errMsg.c_str(), _errMsg.length(), 0);
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
