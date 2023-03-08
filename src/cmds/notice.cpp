/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:12 by mgolinva          #+#    #+#             */
/*   Updated: 2023/02/14 14:59:07 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

// NOTICE message
//      Command: NOTICE
//   Parameters: <target>{,<target>} <text to be sent>
// The NOTICE command is used to send notices between users, as well as to send notices to channels. <target> is interpreted the same way as it is for the PRIVMSG command.

// The NOTICE message is used similarly to PRIVMSG. The difference between NOTICE and PRIVMSG is that automatic replies must never be sent in response to a NOTICE message. This rule also applies to servers – they must not send any error back to the client on receipt of a NOTICE command. The intention of this is to avoid loops between a client automatically sending something in response to something it received. This is typically used by ‘bots’ (a client with a program, and not a user, controlling their actions) and also for server messages to clients.

// One thing for bot authors to note is that the NOTICE message may be interpreted differently by various clients. Some clients highlight or interpret any NOTICE sent to a channel in the same way that a PRIVMSG with their nickname gets interpreted. This means that users may be irritated by the use of NOTICE messages rather than PRIVMSG messages by clients or bots, and they are not commonly used by client bots for this reason.

// User-Based Queries
// WHO message
//      Command: WHO
//   Parameters: <mask>
// This command is used to query a list of users who match the provided mask. The server will answer this command with zero, one or more RPL_WHOREPLY, and end the list with RPL_ENDOFWHO.

// The mask can be one of the following:

// A channel name, in which case the channel members are listed.
// An exact nickname, in which case a single user is returned.
// A mask pattern, in which case all visible users whose nickname matches are listed. Servers MAY match other user-specific values, such as the hostname, server, real name or username. Servers MAY not support mask patterns and return an empty list.
// Visible users are users who aren’t invisible (user mode +i) and who don’t have a common channel with the requesting client. Servers MAY filter or limit visible users replies arbitrarily.

// Numeric Replies:

// RPL_WHOREPLY (352)
// RPL_ENDOFWHO (315)
// ERR_NOSUCHSERVER (402)
// See also:

// IRCv3 multi-prefix Extension
// WHOX
// Examples
// Command Examples:

//   WHO emersion        ; request information on user "emersion"
//   WHO #ircv3          ; list users in the "#ircv3" channel
// Reply Examples:

//   :calcium.libera.chat 352 dan #ircv3 ~emersion sourcehut/staff/emersion calcium.libera.chat emersion H :1 Simon Ser
//   :calcium.libera.chat 315 dan emersion :End of WHO list
//                                   ; Reply to WHO emersion

//   :calcium.libera.chat 352 dan #ircv3 ~emersion sourcehut/staff/emersion calcium.libera.chat emersion H :1 Simon Ser
//   :calcium.libera.chat 352 dan #ircv3 ~val limnoria/val calcium.libera.chat val H :1 Val
//   :calcium.libera.chat 315 dan #ircv3 :End of WHO list
//                                   ; Reply to WHO #ircv3