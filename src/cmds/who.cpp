/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:05:55 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/21 13:47:47 by mgolinva         ###   ########.fr       */
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
    // std::cout << " IN WHO messag[0] = " << message.getArguments()[0] << " IN WHO messag[1] = " << message.getArguments()[1] << std::endl;
    // std::string chan_name = message.getArguments()[0];
    // if (!isChannel(message.getArguments()[0]))
    // {
    //     reply (user, ERR_NOSUCHCHANNEL(user.getReplyName(), chan_name));
    //     return ;
    // }
    
    // chan = getChannelWithName(chan_name);
    
    // if (chan->userIsOp(user.getNickname()))
    //     flags = "+o";
    // reply (user, RPL_WHOREPLY(user.getReplyName(), chan_name, user.getUsername(), HOST, SERVER, user.getNickname(), flags, user.getRealname())); 
}