/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:57:47 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/17 10:59:37 by aandric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	Server::Invite(User &user, Message &message)
{
    if (message._argsNb != 3)
    {
        reply(user, ERR_NEEDMOREPARAMS(message._cmd));
        return ;
    }
    std::string nickname = message._arguments[0];
    std::string channel = message._arguments[1]; // check if possible tomake a function that does 3 checks below code cleaner
    if (message._arguments[1].find("#") != 0) // check if right channel format
    {
        reply(user, ERR_NOSUCHCHANNEL(channel));
        return ;
    }
    if (!isUserWNickname(nickname)) // check if nickname exists
    {
        reply(user, ERR_NOTONCHANNEL(nickname));
        return ;
    }
    if (!isChannel(channel)) // check if channel exists
     {
        reply(user, ERR_NOSUCHCHANNEL(channel));
        return ;
    }
    else if (!_channelsListIt->isUserInChannel(user))  // check if user is on channel 
    {
        reply(user, ERR_NOTONCHANNEL(user.getNickname()));
        return ;
    }
    else if (_channelsListIt->isUserInChannelNickname(nickname)) // check if user already on channel 
    {
        reply(user, ERR_USERONCHANNEL(channel, nickname));
        return ;
    }
    else
    {
        _rplMsg = RPL_INVITING(channel, nickname);
        reply(user, RPL_INVITING(channel, nickname));
        Channel *chan = getChannelWithName(channel);
        User *target = getUserWithNickname(nickname); // update when merge with max function list user

        chan->getUsersList().push_back(target);

        send(target->getSockfd(), _rplMsg.c_str(), _rplMsg.length(), 0);
        return ;
    }
}
// INVITE message
//      Command: INVITE
//   Parameters: <nickname> <channel>
// The INVITE command is used to invite a user to a channel. The parameter <nickname> is the nickname of the person to be invited to the target channel <channel>.

// The target channel SHOULD exist (at least one user is on it). Otherwise, the server SHOULD reject the command with the ERR_NOSUCHCHANNEL numeric.

// Only members of the channel are allowed to invite other users. Otherwise, the server MUST reject the command with the ERR_NOTONCHANNEL numeric.

// Servers MAY reject the command with the ERR_CHANOPRIVSNEEDED numeric. In particular, they SHOULD reject it when the channel has invite-only mode set, and the user is not a channel operator.

// If the user is already on the target channel, the server MUST reject the command with the ERR_USERONCHANNEL numeric.

// When the invite is successful, the server MUST send a RPL_INVITING numeric to the command issuer, and an INVITE message, with the issuer as <source>, to the target user. Other channel members SHOULD NOT be notified.

// Numeric Replies:

// RPL_INVITING (341)
// ERR_NEEDMOREPARAMS (461)
// ERR_NOSUCHCHANNEL (403)
// ERR_NOTONCHANNEL (442)
// ERR_CHANOPRIVSNEEDED (482)
// ERR_USERONCHANNEL (443)
// Command Examples:

//   INVITE Wiz #foo_bar    ; Invite Wiz to #foo_bar
// Message Examples:

//   :dan-!d@localhost INVITE Wiz #test    ; dan- has invited Wiz
//                                         to the channel #test
// See also:

// IRCv3 invite-notify Extension
// Invite list
// Servers MAY allow the INVITE with no parameter, and reply with a list of channels the sender is invited to as RPL_INVITELIST (336) numerics, ending with a RPL_ENDOFINVITELIST (337) numeric.

// Some rare implementations use numerics 346/347 instead of 336/337 as `RPL_INVITELIST`/`RPL_ENDOFINVITELIST`. You should check the server you are using implements them as expected.

// 346/347 now generally stands for `RPL_INVEXLIST`/`RPL_ENDOFINVEXLIST`, used for invite-exception list.