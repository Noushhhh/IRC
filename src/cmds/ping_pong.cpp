/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_pong.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:18 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/14 09:26:30 by aandric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	Server::Ping(User &user, Message &message)
{
    if (message._argsNb != 2)
    {
        reply(user, ERR_NEEDMOREPARAMS(message._cmd));
        return ;
    }
    message._it = message._splitMessage.begin() + 1;
    user.setPing(*message._it);
    std::string pong_msg = "PONG IRC_NOUSHMAKS " + user.getPing();
    reply(user, pong_msg);
}
