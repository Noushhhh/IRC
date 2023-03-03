/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:01 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/03 14:48:43 by aandric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

#define MODESCHARSET "ovaimnqpsrtklb"

bool    isValidMode(std::string modes)
{
    ssize_t modes_size = modes.size();
    for (ssize_t i = 0; i < modes_size; i++)
    {
        if (isCharset(modes[i], MODESCHARSET) != true)
            return (false);
    }
    return (true);
}

bool    modesSet(ssize_t argsNB, std::string modes, std::string modesparams,
std::list< Channel >::iterator channel)
{
    bool    addMode = false;
    bool    removeMode = false;
    (void) addMode;
    (void) removeMode;
    (void) argsNB;
    (void) modes;
    (void) modesparams;
    (void) channel;

    if (modes[0] == '+')
        addMode = true;
    else if (modes[0] == '-')
        removeMode = true;
    else
    {
        //send err msg and return
    }
    if (isValidMode(modes) == false)
    {
        // send err msg and return
    }
    //if ()
    return (true);
}

void	Server::Mode(User &user, Message &message)
{
    (void) user;
    (void) message;
    ssize_t                                 argsNB = 0;
    std::string                             err_buff;
    std::vector< std::string >::iterator    msgEnd = message._splitMessage.end();
    std::list< Channel >::iterator          channel;
    std::string                             modes;
    std::string                             modeparams;

    message._it = message._splitMessage.begin();
    while (message._it != msgEnd)
    {
        message._it ++;
        argsNB ++;
    }

    // if no args

    if (argsNB == 1)
    {
        err_buff = ERR_NEEDMOREPARAMS(std::string("MODE"));
        send(user.getSockfd(), &err_buff, err_buff.length(), 0);
        return ;
    }
    try
    {
        message._it = message._splitMessage.begin();
        message._it ++; // 2nd arg is supposed to be chan name
        channel = getChanWithName((*message._it));
    }
    catch(const Channel::BadNameException& e)
    {
        err_buff = (*message._it);
        err_buff.append(e.badName());
        send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
        return ;
    }
    if (user.isOnChan(user.getNickname()) == false)
    {
        err_buff = ERR_USERNOTINCHANNEL(user.getNickname(), channel->getName());
        send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
        return ;
    }
    if (channel->userIsOp(user.getNickname()) == false)
    {
        err_buff = ERR_CHANOPRIVSNEEDED(channel->getName());
        send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
        return ;
    }
    
    if (argsNB == 2)
    {
        //display mode query info
    }
    else if (argsNB == 3)
    {
        message._it ++; // 3rd arg is supposed to be modes
        modes = *(message._it);
    }
    else if (argsNB == 4)
    {
        message._it ++; // 4rd arg is supposed to be modes params
        modeparams = *(message._it);
    }
    else
    {
        err_buff = ": Too many arguments in your MODE command call\n";
        send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
    }
    //message.
    // else send mod info

    return ;
}
