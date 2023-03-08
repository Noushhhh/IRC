/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:09 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/08 14:06:15 by aandric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	Server::Nick(User &user, Message &message)
{
	if (message._argsNb < 2)
	{
        _errMsg= ERR_NONICKNAMEGIVEN;
		send(user.getSockfd(), _errMsg.c_str(), _errMsg.length(), 0);
		return ;
	}
    std::string nickname = message._arguments[0];
	for (_usersListIt = _usersList.begin(); _usersListIt != _usersList.end(); _usersListIt++)
	{
		if (isUserWNickname(nickname))
        {
            _errMsg = ERR_NICKNAMEINUSE(nickname);
            send(user.getSockfd(), _errMsg.c_str(), _errMsg.length(), 0);
            return ;
        }
	}
    for (size_t i = 0; i < nickname.length(); i++)
    {
        if (!isprint(nickname[i]))
        {
            _errMsg = ERR_ERRONEUSNICKNAME(nickname);
            send(user.getSockfd(), _errMsg.c_str(), _errMsg.length(), 0);
            return ;
        }
    }
    if (!user.getRegistered())
    {
        user.setNickname(nickname);
        _rplMsg = "New nick in use: " + nickname + "\n";
        send(user.getSockfd(), _rplMsg.c_str(), _rplMsg.length(), 0);
    }
    else
    {
        _rplMsg = user.getNickname() + "changed his nickname to: " + nickname + "\n";
        user.setNickname(nickname);
        send(user.getSockfd(), _rplMsg.c_str(), _rplMsg.length(), 0);
    }
}

// NICK message
//      Command: NICK
//   Parameters: <nickname>
// The NICK command is used to give the client a nickname or change the previous one.

// If the server receives a NICK command from a client where the desired nickname is already in use on the network, it should issue an ERR_NICKNAMEINUSE numeric and ignore the NICK command.

// If the server does not accept the new nickname supplied by the client as valid (for instance, due to containing invalid characters), it should issue an ERR_ERRONEUSNICKNAME numeric and ignore the NICK command.

// If the server does not receive the <nickname> parameter with the NICK command, it should issue an ERR_NONICKNAMEGIVEN numeric and ignore the NICK command.

// The NICK message may be sent from the server to clients to acknowledge their NICK command was successful, and to inform other clients about the change of nickname. In these cases, the <source> of the message will be the old nickname [ [ "!" user ] "@" host ] of the user who is changing their nickname.

// Numeric Replies:

// ERR_NONICKNAMEGIVEN (431)
// ERR_ERRONEUSNICKNAME (432)
// ERR_NICKNAMEINUSE (433)
// ERR_NICKCOLLISION (436)
// Command Example:

//   NICK Wiz                  ; Requesting the new nick "Wiz".
// Message Examples:

//   :WiZ NICK Kilroy          ; WiZ changed his nickname to Kilroy.

//   :dan-!d@localhost NICK Mamoped
//                             ; dan- changed his nickname to Mamoped.

