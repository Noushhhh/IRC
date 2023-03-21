/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:09 by mgolinva          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/21 14:35:59 by aandric          ###   ########.fr       */
=======
/*   Updated: 2023/03/21 14:31:38 by aandric          ###   ########.fr       */
>>>>>>> 3ca188e0658c5386c6e57aea8f80de217c5d1f03
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	Server::Nick(User &user, Message &message)
{
	if (message._argsNb < 2)
	{
        reply(user, ERR_NONICKNAMEGIVEN(user.getReplyName(), user.getNickname()));
		return ;
	}
    std::string nickname = message._arguments[0];
	for (_usersListIt = _usersList.begin(); _usersListIt != _usersList.end(); _usersListIt++)
	{
		if (isUserWNickname(nickname))
        {
            reply(user, ERR_NICKNAMEINUSE(user.getReplyName(), nickname));
            return ;
        }
	}
    for (size_t i = 0; i < nickname.length(); i++)
    {
        if (nickname == "anonymous")
        {
            reply(user, ERR_ERRONEUSNICKNAME(user.getReplyName(), nickname));
            return ;
        }
        if (!std::isprint(static_cast <unsigned char> (nickname[i])))
        {
            reply(user, ERR_ERRONEUSNICKNAME(user.getReplyName(), nickname));
            return ;
        }
    }
    if (user.getRegistered() == false)
    {
        _rplMsg = user.getReplyName() + " NICK " + nickname + "\n";
        user.setNickname(nickname);
<<<<<<< HEAD
=======
        // reply(user, _rplMsg);
>>>>>>> 3ca188e0658c5386c6e57aea8f80de217c5d1f03
        reply(user, _rplMsg);
        return ;
    }
    else
    {
<<<<<<< HEAD
        _rplMsg = user.getReplyName() + " NICK " + nickname +'\n';
=======
        //_rplMsg = user.getNickname() + " changed nickname to: " + nickname + "\n";
        _rplMsg = user.getReplyName() + " NICK " + nickname +'\n';
        // reply(user, _rplMsg);
>>>>>>> 3ca188e0658c5386c6e57aea8f80de217c5d1f03
        for (_channelsListIt = _channelsList.begin(); _channelsListIt != _channelsList.end(); _channelsListIt++)
        {
            if (_channelsListIt->getQuietStatus())
                _channelsListIt++;
            sendToChanUsers(_channelsListIt->getName(), _rplMsg);
        }
        user.setNickname(nickname);
        reply(user, _rplMsg);
        return ;
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

