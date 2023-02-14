/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:09 by mgolinva          #+#    #+#             */
/*   Updated: 2023/02/14 14:59:05 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

bool	Server::Nick(User &user, Message &message)
{
	if (message._argsNb < 2)
	{
		send(user.getSockfd(), ERR_NONICKNAMEGIVEN, 19, 0);  // how to automatize size of reply ?
		return false;
	}
    message._it = message._splitMessage.begin() + 1;
    std::string nickname = *message._it;
	for (_usersListIt = _usersList.begin(); _usersListIt != _usersList.end(); _usersListIt++)
	{
		if (_usersListIt->getNickname() == nickname)
        {
            std::cout << ERR_ERRONEUSNICKNAME(nickname) << std::endl; // how to automatize size of reply ?
            return false ;
        }
	}
	
	// std::list<User>::const_iterator it;
	// it = std::find()

	// for (std::list::const_iterator it = 0; it != this._channelList.size() )
	return true ;
}

#define	ERR_NOSUCHNICK(nick)        nick + " :No such nick" // 401
#define ERR_NONICKNAMEGIVEN		    " :No nickname given" //431
#define ERR_ERRONEUSNICKNAME(nick)  nick + " :Erroneous nickname" //432 when a nick contains invalid char
#define ERR_NICKNAMEINUSE(nick)     nick + " :Nickname is in use" // 433