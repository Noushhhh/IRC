/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:09 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/27 16:33:24 by mgolinva         ###   ########.fr       */
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
        user.setNickname(nickname);
        for (_channelsListIt = _channelsList.begin(); _channelsListIt != _channelsList.end(); _channelsListIt++)
        {
            if (_channelsListIt->getQuietStatus())
                _channelsListIt++;
            sendChanUsers(_channelsListIt->getName(), user.getReplyName() + " NICK " + nickname + "\n");
        }
        reply(user, user.getReplyName() + " NICK " + nickname + "\n");
        return ;
    }
    else
    {
        user.setNickname(nickname);
        reply(user, user.getReplyName() + " NICK " + nickname + "\n");
        return ;
    }

}
