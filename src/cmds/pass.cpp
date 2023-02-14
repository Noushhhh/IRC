/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:16 by mgolinva          #+#    #+#             */
/*   Updated: 2023/02/14 14:59:10 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

bool	Server::Pass(User &user, Message &message)
{
	if (message._argsNb < 2)
	{
		send(user.getSockfd(), "ERR_NEEDMOREPARAMS", 18, 0); 
		return false;
	}
	if (user.getPassword().empty())
	{
		message._it = message._splitMessage.begin() + 1;
		user.setPassword(*message._it);
		return true;
	}
	else
	{
		send(user.getSockfd(), "ERR_ALREADYREGISTRED", 20, 0); 
		return false;
	}
	return true ;
}
