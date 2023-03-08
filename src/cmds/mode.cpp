/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:01 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/08 11:36:43 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

#define MODESCHARSET "ovaimnqpsrtklb+-"


bool    isValidMode(User &user, std::string modes)
{
    ssize_t modes_size = modes.size();
    std::string err_msg;

    if (modes[0] != '+' && modes[0] != '-')
    {
        std::cout << "test : " << modes[0] << std::endl;
        return (false);
    }
    for (ssize_t i = 0; i < modes_size; i++)
    {
        if (isCharset(modes[i], MODESCHARSET) != true)
        {
            // err_msg.push_back(modes[i]);
            reply(user, err_msg.append(" : is an invalid mode argument\n"));
            return (false);
        }
        // if there are more than 1 consectuv '+' or '-'
        if ((modes[i] == '+' || modes[i] == '-')
        && (i + 1 < modes_size)
        && (modes[i + 1] == '+' || modes[i + 1] == '-'))
        {
            reply(user, " : wether you are adding or removing mode is unclear\n");
            return (false);
        }
    }
    return (true);
}

bool    modesSet(User &user, std::string modes, std::string *modesparams,
std::list< Channel >::iterator &channel)
{
    std::string err_buff;
    int         addOrRemoveMode = REMOVE;
    int         paramCt =  0; //3 is the start of modesparam that is given as arg to MODE cmd
    ssize_t     modesparams_size = ft_arraySize(modesparams);
    ssize_t     modes_size = modes.size();

    if (isValidMode(user, modes) == false)
    {
    std::cout << "modes : " << modes << " modesparams : " << *modesparams << " : MICHEL\n";
        return (false);
    }
    for (int i = 0; i < modes_size; i ++)
    {
        if (modes[i] == '+')
        {
            addOrRemoveMode = ADD;
        }
        else if (modes[i] == '-')
            addOrRemoveMode = REMOVE;
        std::cout << (addOrRemoveMode == true ? "ADD" : "REMOVE") << std::endl;
        switch (modes[i])
        {
            case    'k': // change pswd
                std::cout << "paramCT = " << paramCt << " modesparams_size : " << modesparams_size << std::endl;
                if (addOrRemoveMode == ADD && paramCt < modesparams_size)
                {
                    channel->setPswd(user, modesparams[paramCt], addOrRemoveMode);
                    paramCt ++;
                }
                else if (addOrRemoveMode == REMOVE)
                    channel->setPswd(user, std::string("") , addOrRemoveMode);
                else
                    reply(user, "MODE +k: needs an argument defining the new key phrase\n");
                break;

            case    'i': // invite mode
                channel->setInviteMode(user, addOrRemoveMode);
                break;

            case    'm': // moderated mode
                channel->setModerationMode(user, addOrRemoveMode);
                break;

            case    'q': // quiet mode
                channel->setQuietMode(user, addOrRemoveMode);
                break;

            case    'n': // No outside message mode
                channel->setOutsideMsgMode(user, addOrRemoveMode);
                break;

            case    'p': // Private mode
                channel->setPrivateMode(user, addOrRemoveMode);
                break;

            case    's': // secret mode
                channel->setSecretMode(user, addOrRemoveMode);
                break;

            case    't': // TOPIC can only be used by chanop
                channel->setTopicMode(user, addOrRemoveMode);
                break;

            case    'v': // add/remove from muted user list
                if (paramCt < modesparams_size)
                    channel->setMutedList(user, *channel->getUserItInList(channel->getUsersList(), modesparams[paramCt]), addOrRemoveMode);
                else
                    reply(user, "MODE +-v: needs an argument defining the user to add or remove from the muted users list\n");
                break;

            case    'b': // add/remove from banned userlist
                if (paramCt < modesparams_size)
                    channel->setBanList(user, *channel->getUserItInList(channel->getUsersList(), modesparams[paramCt]), addOrRemoveMode);
                else
                    reply(user, "MODE +-b: needs an argument defining the user to add or remove from the banned users list\n");
                break;

            case    'l': // set channel's user limit
                if (addOrRemoveMode == ADD && paramCt < modesparams_size)
                {
                    channel->setUsersLimit(user, modesparams[paramCt], addOrRemoveMode);
                    paramCt ++;
                }
                else if (addOrRemoveMode == REMOVE)
                    channel->setUsersLimit(user, std::string("0"), addOrRemoveMode);
                else
                    reply (user, "MODE +l: needs an argument defining the maximum number of user that can simultaneously be on a channel\n");
                break;

            case    'o': // add/remove from op list
                if (paramCt < modesparams_size)
                    channel->setOpList(user, *channel->getUserItInList(channel->getUsersList(), modesparams[paramCt]), addOrRemoveMode);
                else
                    reply(user, "MODE +-b: needs an argument defining the user to add or remove from the banned users list\n");
                break;          
            default:
                break;
        }
        // while (i > 1 && i < modes_size && modes[i] == modes[i - 1])
        //     i ++;
    }
    //if ()
    return (true);
}

bool	Server::Mode(User &user, Message &message)
{
    (void) user;
    (void) message;
    int                                     i = 0;
    ssize_t                                 argsNB = 0;
    std::string                             err_buff;
    std::vector< std::string >::iterator    msgEnd = message._splitMessage.end();
    std::list< Channel >::iterator          channel;
    std::string                             modes;
    std::string                             *modeparams = NULL;

    message._it = message._splitMessage.begin();
    while (message._it != msgEnd)
    {
        message._it ++;
        argsNB ++;
    }

    modeparams = new std::string[argsNB];

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
    if (user.isOnChan(channel->getName()) == false)
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
        std::cout << "MODE QUERY" << std::endl; // TO DO
        return (true);
        //display mode query info
    }
    else if (argsNB == 3)
    {
        message._it ++; // 3rd arg is supposed to be modes
        modes = *(message._it);
        modesSet(user, modes, modeparams, channel);
    }
    else if ( argsNB > 3)
    {
        message._it ++; // 3rd arg is supposed to be modes
        modes = *(message._it);
        while (message._it != msgEnd)
        {
            message._it ++; // 4rd arg and so forth are supposed to be modes params
            modeparams[i] = *(message._it);
            i ++;
        }
        modesSet(user, modes, modeparams, channel);
    }
    //message.
    // else send mod info

    return (true);
}
