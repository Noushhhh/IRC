/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:16 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/01 12:04:48 by aandric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	Server::Pass(User &user, Message &message)
{
	if (message._argsNb < 2)
	{
		_errMsg = ERR_NEEDMOREPARAMS(); // "PASS" in params ?
		send(user.getSockfd(), _errMsg.c_str(), _errMsg.length(), 0);
		return ;
	}
	if (user.getPassword().empty())
	{
		message._it = message._splitMessage.begin() + 1;
		user.setPassword(*message._it);
		return ;
	}
	else
	{
		_errMsg = ERR_ALREADYREGISTERED;
		send(user.getSockfd(), _errMsg.c_str(), _errMsg.length(), 0);
		return ;
	}
	return ;
}
