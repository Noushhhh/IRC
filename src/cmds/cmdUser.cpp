/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdUser.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:57:38 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/22 14:47:18 by aandric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

std::vector< struct pollfd >::iterator &Server::findPollFd(int fd)
{
    
    std::vector< struct pollfd >::iterator *it = NULL; 
    std::vector< struct pollfd >::iterator end = _pollFds.end();

    *it = _pollFds.begin();
    std::cout << "yo" << std::endl;

    while ((*it) != end)
    {
        if ((*it)->fd == fd)
            return (*it);
        it ++;
    }
    return (*it);
}


void	Server::cmdUser(User &user, Message &message)
{
    if (message._argsNb < 5)
    {
        reply(user, ERR_NEEDMOREPARAMS(user.getReplyName(), message._cmd));
        return ;
	}
    if (user.getRegistered() == true)
    {
        reply(user, ERR_ALREADYREGISTERED(user.getReplyName()));
        return ;
    }
    user.setUsername(message._arguments[0]);
    if (message._arguments[1].length() != 1 || !((message._arguments[1]).find_first_not_of("012345678")) || message._arguments[2] != "*")
    {
        reply(user, "wrong format for user mode: try: '0 *'\n");
        return ;
    }
    if (message._arguments[4].find(":") == 0)
    {
        std::string realname = get_suffix(&message._arguments[4]);
        realname = message._arguments[4].substr(1);
        user.setRealname(realname);
    }
    if (user.getPassword() == this->getPassword())
    {
        user.setRegistered();
        reply(user, RPL_WELCOME(user.getReplyName(), user.getNickname()));
        return ;
    }
    else
    {
        reply(user, ERR_PASSWDMISMATCH(user.getReplyName()));
        // closeUser(findPollFd(user.getSockfd()));
        closeUser();
        return ;
    }
}

//      Command: USER
//   Parameters: <username> 0 * <realname>
// The USER command is used at the beginning of a connection to specify the username and realname of a new user.

// It must be noted that <realname> must be the last parameter because it may contain SPACE (' ', 0x20) characters, and should be prefixed with a colon (:) if required.

// Servers MAY use the Ident Protocol to look up the ‘real username’ of clients. If username lookups are enabled and a client does not have an Identity Server enabled, the username provided by the client SHOULD be prefixed by a tilde ('~', 0x7E) to show that this value is user-set.

// The maximum length of <username> may be specified by the USERLEN RPL_ISUPPORT parameter. If this length is advertised, the username MUST be silently truncated to the given length before being used. The minimum length of <username> is 1, ie. it MUST NOT be empty. If it is empty, the server SHOULD reject the command with ERR_NEEDMOREPARAMS (even if an empty parameter is provided); otherwise it MUST use a default value instead.

// The second and third parameters of this command SHOULD be sent as one zero ('0', 0x30) and one asterisk character ('*', 0x2A) by the client, as the meaning of these two parameters varies between different versions of the IRC protocol.

// Clients SHOULD use the nickname as a fallback value for <username> and <realname> when they don’t have a meaningful value to use.

// If a client tries to send the USER command after they have already completed registration with the server, the ERR_ALREADYREGISTERED reply should be sent and the attempt should fail.

// If the client sends a USER command after the server has successfully received a username using the Ident Protocol, the <username> parameter from this command should be ignored in favour of the one received from the identity server.

// Numeric Replies:

// ERR_NEEDMOREPARAMS (461)
// ERR_ALREADYREGISTERED (462)

// Command Examples:

//   USER guest 0 * :Ronnie Reagan
//                               ; No ident server
//                               ; User gets registered with username
//                               "~guest" and real name "Ronnie Reagan"

//   USER guest 0 * :Ronnie Reagan
//                               ; Ident server gets contacted and
//                               returns the name "danp"
//                               ; User gets registered with username
//                               "danp" and real name "Ronnie Reagan"
