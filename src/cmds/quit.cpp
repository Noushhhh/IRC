/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:23 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/10 16:37:40 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	Server::Quit(User &user, Message &message)
{
    std::string quit_msg;
    if (message._argsNb < 2)
    {
        _errMsg = ERR_NEEDMOREPARAMS(message._cmd);
        send(user.getSockfd(), _errMsg.c_str(), _errMsg.length(), 0);
        return ;
    }
    quit_msg = quit_msg = user.getNickname() + "@IRC_NOUSHMAKS QUIT '\n'";
    if (message._argsNb > 2)
         quit_msg = quit_msg + get_suffix(&message._arguments[1]);
    std::list <Channel *>::iterator cit = user.getJoinedChans().begin();
    while (cit != user.getJoinedChans().begin())
    {
        (*cit)->sendToUsers(quit_msg); // send to all users of chans in which user was
        cit++;
    }
    // function to close user
}

// QUIT message
//     Command: QUIT
//  Parameters: [<reason>]feat
// The QUIT command is used to terminate a client’s connection to the server. The server acknowledges this by replying with an ERROR message and closing the connection to the client.

// This message may also be sent from the server to a client to show that a client has exited from the network. This is typically only dispatched to clients that share a channel with the exiting user. When the QUIT message is sent to clients, <source> represents the client that has exited the network.

// When connections are terminated by a client-sent QUIT command, servers SHOULD prepend <reason> with the ASCII string "Quit: " when sending QUIT messages to other clients, to represent that this user terminated the connection themselves. This applies even if <reason> is empty, in which case the reason sent to other clients SHOULD be just this "Quit: " string. However, clients SHOULD NOT change behaviour based on the prefix of QUIT message reasons, as this is not required behaviour from servers.

// When a netsplit (the disconnecting of two servers) occurs, a QUIT message is generated for each client that has exited the network, distributed in the same way as ordinary QUIT messages. The <reason> on these QUIT messages SHOULD be composed of the names of the two servers involved, separated by a SPACE (' ', 0x20). The first name is that of the server which is still connected and the second name is that of the server which has become disconnected. If servers wish to hide or obscure the names of the servers involved, the <reason> on these messages MAY also be the literal ASCII string "*.net *.split" (i.e. the two server names are replaced with "*.net" and "*.split"). Software that implements the IRCv3 batch Extension should also look at the netsplit and netjoin batch types.

// If a client connection is closed without the client issuing a QUIT command to the server, the server MUST distribute a QUIT message to other clients informing them of this, distributed in the same was an ordinary QUIT message. Servers MUST fill <reason> with a message reflecting the nature of the event which caused it to happen. For instance, "Ping timeout: 120 seconds", "Excess Flood", and "Too many connections from this IP" are examples of relevant reasons for closing or for a connection with a client to have been closed.

// Numeric Replies:

// None
// Command Example:

//   QUIT :Gone to have lunch         ; Client exiting from the network
// Message Example:

//   :dan-!d@localhost QUIT :Quit: Bye for now!
//                                    ; dan- is exiting the network with
//                                    the message: "Quit: Bye for now!"