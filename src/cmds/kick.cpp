/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:57:55 by mgolinva          #+#    #+#             */
/*   Updated: 2023/02/14 14:58:56 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

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
// Server Queries and Commands
// MOTD message
//      Command: MOTD
//   Parameters: [<target>]
// The MOTD command is used to get the “Message of the Day” of the given server. If <target> is not given, the MOTD of the server the client is connected to should be returned.

// If <target> is a server, the MOTD for that server is requested. If <target> is given and a matching server cannot be found, the server will respond with the ERR_NOSUCHSERVER numeric and the command will fail.

// If the MOTD can be found, one RPL_MOTDSTART numeric is returned, followed by one or more RPL_MOTD numeric, then one RPL_ENDOFMOTD numeric.

// If the MOTD does not exist or could not be found, the ERR_NOMOTD numeric is returned.

// Numeric Replies:

// ERR_NOSUCHSERVER (402)
// ERR_NOMOTD (422)
// RPL_MOTDSTART (375)
// RPL_MOTD (372)
// RPL_ENDOFMOTD (376)
