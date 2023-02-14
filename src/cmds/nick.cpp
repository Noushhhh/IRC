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
		send(user.getSockfd(), "ERR_NONICKNAMEGIVEN", 19, 0); 
		return false;
	}
	std::string nickname = *message._splitMessage.(begin() + 1);
	for (_usersListIt = _usersList.begin(); _usersListIt != _usersList.end(); _usersListIt++)
	{
		if (_usersListIt->getNickname() == message._splitMessage.begin() + 1)
	}
	// ERR_ERRONEUSNICKNAME
	// std::list<User>::const_iterator it;
	// it = std::find()

	// for (std::list::const_iterator it = 0; it != this._channelList.size() )
	return true ;
}