/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:01 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/16 10:34:32 by aandric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

#define MODESCHARSET "ovaimnqpsrtklb+-"


bool    isValidMode(User &user, std::string modes)
{
    ssize_t modes_size = modes.size();
    std::string err_msg;

    if ((modes[0] != '+' && modes[0] != '-')
    || (modes_size == 1))
    {
        reply(user, ": no modes were specified\n");
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
            reply(user, " : too many subsquent '+' & '-' symbols\n");
            return (false);
        }
    }
    return (true);
}

bool    Server::modesSet(User &user, std::string modes, std::string *modesparams,
std::list< Channel >::iterator &channel)
{
    int         addOrRemoveMode = REMOVE;
    int         paramCt = 0;
    ssize_t     modesparams_size = ft_arraySize(modesparams);
    ssize_t     modes_size = modes.size();

    if (isValidMode(user, modes) == false)
        return (false);
    for (int i = 0; i < modes_size; i ++)
    {
        if (modes[i] == '+')
        {
            addOrRemoveMode = ADD;
        }
        else if (modes[i] == '-')
            addOrRemoveMode = REMOVE;
        while (i > 0 && i < modes_size && modes[i] == modes[i - 1])
            i ++;
        switch (modes[i])
        {
            case    'k': // change pswd
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
                channel->setModerationMode(*this, user, addOrRemoveMode);
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

            case    'v': // add/remove from muted user list
                if(channel->getUserItInList(channel->getUsersList(), modesparams[paramCt]) == channel->getUsersList().end())
                    reply(user, ERR_USERNOTINCHANNEL(modesparams[paramCt], channel->getName())); //TO DO
                else if (paramCt < modesparams_size)
                {
                    channel->setMutedList(user, *channel->getUserItInList(channel->getUsersList(), modesparams[paramCt]), addOrRemoveMode);
                    paramCt ++;
                }
                else
                    reply(user, ": MODE +-v: needs an argument defining the user to add or remove from the muted users list\n");
                break;

            case    'b': // add/remove from banned userlist
                if(addOrRemoveMode == ADD && channel->getUserItInList(channel->getUsersList(), modesparams[paramCt]) == channel->getUsersList().end())
                    reply(user, ERR_USERNOTINCHANNEL(modesparams[paramCt], channel->getName()));
                else if(addOrRemoveMode == REMOVE && channel->getUserItInList(channel->getBanList(), modesparams[paramCt]) == channel->getBanList().end())
                    reply(user, RPL_NOTBANNED(modesparams[paramCt], channel->getName())); //TO DO
                else
                {
                    if (paramCt < modesparams_size && addOrRemoveMode == REMOVE)
                    {
                        channel->setBanList(*this, user, *channel->getUserItInList(channel->getBanList(), modesparams[paramCt]), addOrRemoveMode);
                        paramCt ++;
                    }
                    else if (paramCt < modesparams_size && addOrRemoveMode == ADD)
                    {
                        channel->setBanList(*this, user, *channel->getUserItInList(channel->getUsersList(), modesparams[paramCt]), addOrRemoveMode);
                        paramCt ++;
                    }
                    else
                        reply(user, ": MODE +-b: needs an argument defining the user to add or remove from the banned users list\n");
                }
                break;

            case    'o': // add/remove from op list
                if(channel->getUserItInList(channel->getUsersList(), modesparams[paramCt]) == channel->getUsersList().end())
                    reply(user, ERR_USERNOTINCHANNEL(modesparams[paramCt], channel->getName())); //TO DO
                else if (paramCt < modesparams_size)
                {
                    channel->setOpList(user, *channel->getUserItInList(channel->getUsersList(), modesparams[paramCt]), addOrRemoveMode);
                    paramCt ++;
                }
                else
                    reply(user, "MODE +-b: needs an argument defining the user to add or remove from the banned users list\n");
                break;          
            default:
                break;
        }
       
    }
    //if ()
    return (true);
}

void    modeQueryReply(Channel &channel, User &user)
{
    std::stringstream strs;
    strs << channel.getUsersLimit();

    (channel.getPswdStatus() == true ? reply(user, channel.getName().append(": is password protected\n")) : reply(user, channel.getName().append(": is not password protected\n")));
    (channel.getInviteStatus() == true ? reply(user, channel.getName().append(": is invite only\n")) : reply(user, channel.getName().append(": is not invite only\n")));
    (channel.getModerationStatus() == true ? reply(user, channel.getName().append(": is moderated\n")) : reply(user, channel.getName().append(": is not moderated\n")));
    (channel.getQuietStatus() == true ? reply(user, channel.getName().append(": is quiet\n")) : reply(user, channel.getName().append(": is not quiet\n")));
    (channel.getOutsideMsgStatus() == true ? reply(user, channel.getName().append(": cannot receive outside messages\n")) : reply(user, channel.getName().append(": can receive outside messages\n")));
    (channel.getPrivacyStatus() == true ? reply(user, channel.getName().append(": is private\n")) : reply(user, channel.getName().append(": is not private\n")));
    (channel.getSecrecyStatus() == true ? reply(user, channel.getName().append(": is secret\n")) : reply(user, channel.getName().append(": is not secret\n")));
    (channel.getTopicStatus() == true ? reply(user, channel.getName().append(": topic's can only be set by ChanOp\n")) : reply(user, channel.getName().append(": topic's can be set by everyone\n")));
    (channel.getUsersLimitStatus() == true ? reply(user, channel.getName().append(": has a max amount of connected user of : ").append(strs.str()).append("\n")) : reply(user, channel.getName().append(": has no user limit\n")));
}

void	Server::Mode(User &user, Message &message)
{
    (void) user;
    (void) message;
    int                                     i = 0;
    ssize_t                                 argsNB = 0;
    std::string                             err_buff;
    std::vector< std::string >::iterator    msgEnd = (message.getSplitMessage()).end();
    std::list< Channel >::iterator          channel;
    std::string                             modes;
    std::string                             *modeparams = NULL;

    message.getIt() = (message.getSplitMessage()).begin();
    while (message.getIt() != msgEnd)
    {
        message.getIt() ++;
        argsNB ++;
    }
    modeparams = new std::string[argsNB];

    // if no args

    if (argsNB == 1) // if (argsNB < 2)
    {
        err_buff = ERR_NEEDMOREPARAMS(std::string("MODE"));
        send(user.getSockfd(), &err_buff, err_buff.length(), 0);
        return ;
    }
    try
    {
        message.getIt() = (message.getSplitMessage()).begin(); // delete
        message.getIt() ++; // 2nd arg is supposed to be chan name // delete
        channel = getChanItWithName((*message.getIt())); // delete
        // channel = getChanItWithName((message.getArguments())[1]); // 2nd arg is supposed to be chan name // | and delete the 3 lines above
    }
    catch(const Channel::BadNameException& e)
    {
        err_buff = (*message.getIt()); //  err_buff = (message.getArguments())[1];
        err_buff.append(e.badName()); // delete 
        send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
        return ;
    }
    if (user.isOnChan(channel->getName()) == false)
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
        modeQueryReply(*channel, user);
        return ;
        //display mode query info
    }
    else if (argsNB == 3)
    {
        message.getIt() ++; // 3rd arg is supposed to be modes
        modes = *(message.getIt());
        modesSet(user, modes, modeparams, channel);
    }
    else if ( argsNB > 3)
    {
        message.getIt() ++; // 3rd arg is supposed to be modes
        modes = *(message.getIt());
        while (++message.getIt() != msgEnd)
        {
            modeparams[i] = *(message.getIt()); // modeparams[i] = (message.getArguments())[3]; // 4rd arg and so forth are supposed to be modes params
            i ++;
        }
        modesSet(user, modes, modeparams, channel);
    }
    //message.
    // else send mod info

    return ;
}
