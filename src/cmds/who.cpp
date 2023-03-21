/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:05:55 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/21 17:44:02 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void    Server::Who(User &user, Message &message)
{
    (void) user;
    (void) message;
    // Channel     *chan = NULL;
    // std::string flags = "";

    // if (message.getArgsNb() != 2)
    // {
    //     reply (user, ERR_NEEDMOREPARAMS(user.getReplyName(), "WHO"));
    //     return ;
    // }
    // std::string chan_name = message.getArguments()[0];
    // if (!isChannel(message.getArguments()[0]))
    // {
    //     reply (user, ERR_NOSUCHCHANNEL(user.getReplyName(), chan_name));
    //     return ;
    // }
    
    // chan = getChannelWithName(chan_name);
    
    // if (chan->userIsOp(user.getNickname()))
    //     flags = "+o";
    // std::list< User *>::iterator end = chan->getUsersList().end();
    // for (std::list< User *>::iterator it = chan->getUsersList().begin(); it != end; it ++)
    // {
    //     sendToChanUsers(chan->getName() ,RPL_NAMEREPLY(user.getReplyName(), "@", chan->getName(), (*it)->getNickname()));
    //     sendToChanUsers(chan->getName() ,RPL_WHOREPLY(user.getReplyName(), chan_name, (*it)->getUsername(), HOST, SERVER, (*it)->getNickname(), flags, user.getRealname())); 
    // }
}