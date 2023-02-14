/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:57:52 by mgolinva          #+#    #+#             */
/*   Updated: 2023/02/14 17:53:42 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"
#include "../../includes/Channel.hpp"

bool	Server::Join(User &user, Message &message)
{
	std::string err_buff;
    if (message._splitMessage.size() == 1)
    {
        err_buff = ERR_NEEDMOREPARAMS(std::string("JOIN"));
        send(user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
        return (false);
    }
    if (message._splitMessage.size() > 3)
    {
        err_buff = ERR_TOOMANYTARGETS(std::string("JOIN"));
        send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
        return (false);
    }
    message._it = message._splitMessage.begin();
    if (message._splitMessage.size() == 2 && *(message._it + 1) == "0")
    {
        // leave all chan joined
    }
    (void) user;
    // for (_cIt = _channelsList.begin(); _cIt != _channelsList.end(); _cIt ++)
    // {
    //     if ()
    // }
    // Channel newChan()
    return (true);
}
