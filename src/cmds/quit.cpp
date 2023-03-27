/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:23 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/27 15:42:42 by aandric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	Server::Quit(User &user, Message &message)
{
    std::string quit_msg;
    if (message._argsNb < 2)
    {
        reply (user, ERR_NEEDMOREPARAMS(user.getReplyName(), user.getNickname(), message._cmd));
        return ;
    }
    quit_msg = user.getReplyName() + " QUIT :Quit ";
    if (message._argsNb > 1)
         quit_msg = quit_msg + get_suffix(&message._arguments[0]);
    quit_msg += "\n";
    for (std::list <Channel *>::iterator cit = user.getJoinedChans().begin(); cit != user.getJoinedChans().end(); cit++)
        (*cit)->sendToUsersExcept(user.getNickname(), quit_msg); // send to all users of chans
    closeUser();
}
