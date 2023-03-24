/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:09 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/24 16:11:11 by mgolinva         ###   ########.fr       */
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

    if (isUserWNickname(nickname))
    {
        std::string try_nickname; 
        for (int i = 0; isUserWNickname(nickname); i++)
        {
            std::stringstream ss;
            ss << i;
            try_nickname = nickname + ss.str();
            ss << "";
            if (!isUserWNickname(try_nickname))
            {
                message._arguments[0] = try_nickname;
                break ;
            }
        }
        Nick(user, message);
        return ;
    }

    if (user.getRegistered() == true)
    {
        _rplMsg = user.getReplyName() + " NICK " + nickname + "\n";
        user.setNickname(nickname);
        for (_channelsListIt = _channelsList.begin(); _channelsListIt != _channelsList.end(); _channelsListIt++)
        {
            if (_channelsListIt->getQuietStatus())
                _channelsListIt++;
            sendChanUsers(_channelsListIt->getName(), _rplMsg);
        }
        reply(user, _rplMsg);
        return ;
    }
    else
    {
        _rplMsg = user.getReplyName() + " NICK " + nickname + "\n";
        user.setNickname(nickname);
        reply(user, _rplMsg);
        return ;
    }

}

// TO DO : reachable leaks on : _rplMsg = user.getReplyName() + " NICK " + nickname + "\n";

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

