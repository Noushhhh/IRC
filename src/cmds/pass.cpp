/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:16 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/27 15:23:59 by aandric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	Server::Pass(User &user, Message &message)
{
	if (message._argsNb < 2)
	{
		reply(user, ERR_NEEDMOREPARAMS(user.getReplyName(), user.getNickname(), message._cmd));
		return ;
	}
	if (user.getRegistered() == true)
	{
		reply(user, ERR_ALREADYREGISTERED(user.getReplyName(), user.getNickname()));
		return ;
	}
	else
		user.setPassword(message._arguments[0]);
}

