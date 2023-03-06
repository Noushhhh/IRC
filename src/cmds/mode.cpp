/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:01 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/06 16:05:56 by mgolinva         ###   ########.fr       */
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
        // if there are more than 1 consectuv '+' or '-'
        if ((modes[i] == '+' || modes[i] == '-')
        && (i + 1 < modes_size)
        && (modes[i + 1] == '+' || modes[i + 1] == '-'))
            return (false);
    }
    return (true);
}

bool    modesSet(User &user, std::string modes, std::string *modesparams,
std::list< Channel >::iterator channel)
{
    std::string err_buff;
    int         addOrRemoveMode = REMOVE;
    int         paramCt =  3; //3 is the start of modesparam that is given as arg to MODE cmd
    ssize_t     modesparams_size = ft_arraySize(modesparams);
    ssize_t     modes_size = modes.size();

    if (isValidMode(modes) == false)
    {
        // send err msg and return
        // wrong mode format
    }
    for (int i = 1; i < modes_size; i ++)
    {
        if (modes[i] == '+')
            addOrRemoveMode = ADD;
        else if (modes[i] == '-')
            addOrRemoveMode = REMOVE;
        switch (modes[i])
        {
            case    'k': // change pswd
                if (addOrRemoveMode == ADD && paramCt < modesparams_size)
                {
                    channel->setPswd(modesparams[paramCt], addOrRemoveMode);
                    paramCt ++;
                }
                else if (addOrRemoveMode == REMOVE)
                    channel->setPswd(std::string("") , addOrRemoveMode);
                else
                {
                    err_buff = "MODE +k: needs an argument defining the new key phrase\n";
        		    send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
                }
                break;
            case    'i': // invite mode
                channel->setInviteMode(addOrRemoveMode);
                break;
            case    'm': // moderated mode
                channel->setModerationMode(addOrRemoveMode);
                break;
            case    'q': // quiet mode
                channel->setQuietMode(addOrRemoveMode);
                break;
            case    'n': // No outside message mode
                channel->setOutsideMsgMode(addOrRemoveMode);
                break;
            case    'p': // Private mode
                channel->setPrivateMode(addOrRemoveMode);
                break;
            case    's': // secret mode
                channel->setSecretMode(addOrRemoveMode);
                break;
            case    't': // TOPIC can only be used by chanop
                channel->setTopicMode(addOrRemoveMode);
                break;
            case    'v': // add/remove from muted user list
                if (paramCt < modesparams_size)
                    channel->setMutedList(user, *channel->getUserItInList(channel->getUsersList(), modesparams[paramCt]), addOrRemoveMode);
                else
                {
                    err_buff = "MODE +-v: needs an argument defining the user to add or remove from the muted users list\n";
        		    send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
                }
                break;
            case    'b': // add/remove from banned userlist
                if (paramCt < modesparams_size)
                    channel->setBanList(user, *channel->getUserItInList(channel->getUsersList(), modesparams[paramCt]), addOrRemoveMode);
                else
                {
                    err_buff = "MODE +-b: needs an argument defining the user to add or remove from the banned users list\n";
        		    send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
                }
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
                {
                    err_buff = "MODE +l: needs an argument defining the maximum number of user that can simultaneously be on a channel\n";
        		    send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
                }
                break;
            case    'o': // add/remove from op list
                if (paramCt < modesparams_size)
                    channel->setOpList(user, *channel->getUserItInList(channel->getUsersList(), modesparams[paramCt]), addOrRemoveMode);
                else
                {
                    err_buff = "MODE +-b: needs an argument defining the user to add or remove from the banned users list\n";
        		    send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
                }
                break;          
            default:
                break;
        }
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

    while (message._it != msgEnd)
    {
        message._it ++; // 4rd arg and so forth are supposed to be modes params
        modeparams[i] = *(message._it);
        i ++;
    }
    //message.
    // else send mod info

    return (true);
}
