/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:01 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/06 09:41:09 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

#define MODESCHARSET "ovaimnqpsrtklb+-"

bool    isValidMode(std::string modes)
{
    ssize_t modes_size = modes.size();
    if ((modes_size >= 1)
    && (modes[0] != '+' || modes[0] != '-'))
        return (false);
    for (ssize_t i = 0; i < modes_size; i++)
    {
        if (isCharset(modes[i], MODESCHARSET) != true)
            return (false);
        if ((modes[i] == '+' || modes[i] == '-')
        && (i + 1 < modes_size)
        && (modes[i + 1] == '+' || modes[i + 1] == '-'))
            return (false);
    }
    return (true);
}

bool    modesSet(ssize_t argsNB, std::string modes, std::string modesparams,
std::list< Channel >::iterator channel)
{
    bool    addMode = false;
    bool    removeMode = false;
    ssize_t modes_size = modes.size();


    if (isValidMode(modes) == false)
    {
        // send err msg and return
        // wrong mode format
    }
    for (int i = 1; i < modes_size; i ++)
    {
        if (modes[i] == '+')
        {
            addMode = true;
            removeMode = false;
        }
        else if (modes[i] == '-')
        {
            addMode = false;
            removeMode = true;
        }
        switch (modes[i])
        {
            case  'k':
                /* code */
                break;
            case :
                /* code */
                break;
            case :
                /* code */
                break;
            case :
                /* code */
                break;
            case :
                /* code */
                break;
            case :
                /* code */
                break;
            case :
                /* code */
                break;
            
            default:
                break;
        }
    }
}

bool	Server::Mode(User &user, Message &message)
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
        return (false);
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
        return (false);
    }
    if (user.isOnChan(user.getNickname()) == false)
    {
        err_buff = ERR_USERNOTINCHANNEL(user.getNickname(), channel->getName());
        send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
        return (false);
    }
    if (channel->userIsOp(user.getNickname()) == false)
    {
        err_buff = ERR_CHANOPRIVSNEEDED(channel->getName());
        send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
        return (false);
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
    message.
    // else send mod info

    return (true);
}
