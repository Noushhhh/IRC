/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_pong.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:18 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/16 10:35:50 by aandric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	Server::Ping(User &user, Message &message)
{
    if (message.getArgsNb() != 2)
    {
        reply(user, ERR_NEEDMOREPARAMS(message.getCmd()));
        return ;
    }
    message.getIt() = message.getSplitMessage().begin() + 1;
    user.setPing(*message.getIt());
    std::string pong_msg = "PONG IRC_NOUSHMAKS " + user.getPing();
    reply(user, pong_msg);
}
