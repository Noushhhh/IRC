/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:21 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/24 10:34:41 by aandric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	Server::PrivMsg(User &user, Message &message)
{
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

// PRIVMSG message
//      Command: PRIVMSG
//   Parameters: <target>{,<target>} <text to be sent>
// The PRIVMSG command is used to send private messages between users, as well as to send messages to channels. <target> is the nickname of a client or the name of a channel.

// If <target> is a channel name and the client is banned and not covered by a ban exception, the message will not be delivered and the command will silently fail. Channels with the moderated mode active may block messages from certain users. Other channel modes may affect the delivery of the message or cause the message to be modified before delivery, and these modes are defined by the server software and configuration being used.

// If a message cannot be delivered to a channel, the server SHOULD respond with an ERR_CANNOTSENDTOCHAN (404) numeric to let the user know that this message could not be delivered.

// If <target> is a channel name, it may be prefixed with one or more channel membership prefix character (@, +, etc) and the message will be delivered only to the members of that channel with the given or higher status in the channel. Servers that support this feature will list the prefixes which this is supported for in the STATUSMSG RPL_ISUPPORT parameter, and this SHOULD NOT be attempted by clients unless the prefix has been advertised in this token.

// If <target> is a user and that user has been set as away, the server may reply with an RPL_AWAY (301) numeric and the command will continue.

// The PRIVMSG message is sent from the server to client to deliver a message to that client. The <source> of the message represents the user or server that sent the message, and the <target> represents the target of that PRIVMSG (which may be the client, a channel, etc).

// When the PRIVMSG message is sent from a server to a client and <target> starts with a dollar character ('$', 0x24), the message is a broadcast sent to all clients on one or multiple servers.

// Numeric Replies:

// ERR_NOSUCHNICK (401)
// ERR_NOSUCHSERVER (402)
// ERR_CANNOTSENDTOCHAN (404)
// ERR_TOOMANYTARGETS (407)
// ERR_NORECIPIENT (411)
// ERR_NOTEXTTOSEND (412)
// ERR_NOTOPLEVEL (413)
// ERR_WILDTOPLEVEL (414)
// RPL_AWAY (301)
// There are strange "X@Y" target rules and such which are noted in the examples of the original PRIVMSG RFC section. We need to check to make sure modern servers actually process them properly, and if so then specify them.
// Command Examples:

//   PRIVMSG Angel :yes I'm receiving it !
//                                   ; Command to send a message to Angel.

//   PRIVMSG %#bunny :Hi! I have a problem!
//                                   ; Command to send a message to halfops
//                                   and chanops on #bunny.

//   PRIVMSG @%#bunny :Hi! I have a problem!
//                                   ; Command to send a message to halfops
//                                   and chanops on #bunny. This command is
//                                   functionally identical to the above
//                                   command.
// Message Examples:

//   :Angel PRIVMSG Wiz :Hello are you receiving this message ?
//                                   ; Message from Angel to Wiz.

//   :dan!~h@localhost PRIVMSG #coolpeople :Hi everyone!
//                                   ; Message from dan to the channel
//                                   #coolpeople