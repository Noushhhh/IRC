/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:14 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/24 16:11:25 by mgolinva         ###   ########.fr       */
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

// PART message
//      Command: PART
//   Parameters: <channel>{,<channel>} [<reason>]
// The PART command removes the client from the given channel(s). On sending a successful PART command, the user will receive a PART message from the server for each channel they have been removed from. <reason> is the reason that the client has left the channel(s).

// For each channel in the parameter of this command, if the channel exists and the client is not joined to it, they will receive an ERR_NOTONCHANNEL (442) reply and that channel will be ignored. If the channel does not exist, the client will receive an ERR_NOSUCHCHANNEL (403) reply and that channel will be ignored.

// This message may be sent from a server to a client to notify the client that someone has been removed from a channel. In this case, the message <source> will be the client who is being removed, and <channel> will be the channel which that client has been removed from. Servers SHOULD NOT send multiple channels in this message to clients, and SHOULD distribute these multiple-channel PART messages as a series of messages with a single channel name on each. If a PART message is distributed in this way, <reason> (if it exists) should be on each of these messages.

// Numeric Replies:

// ERR_NEEDMOREPARAMS (461)
// ERR_NOSUCHCHANNEL (403)
// ERR_NOTONCHANNEL (442)
// Command Examples:

//   PART #twilight_zone             ; leave channel "#twilight_zone"

//   PART #oz-ops,&group5            ; leave both channels "&group5" and
//                                   "#oz-ops".
// Message Examples:

//   :dan-!d@localhost PART #test    ; dan- is leaving the channel #test