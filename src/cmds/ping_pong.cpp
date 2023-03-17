/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_pong.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:18 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/17 09:35:02 by aandric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	Server::Ping(User &user, Message &message)
{
    // if (message._argsNb < 2)
    // {
    //     reply(user, ERR_NEEDMOREPARAMS(message._cmd));
    //     return ;
    // }
    user.setPing(message._arguments[0]);
    reply(user, user.getPing() + "\n");
}
