/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:01 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/29 15:48:56 by mgolinva         ###   ########.fr       */
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
                    reply(user, ERR_USERNOTINCHANNEL(user.getReplyName(), user.getNickname(), modesparams[paramCt], channel->getName()));
                else if (paramCt < modesparams_size)
                {
                    channel->setMutedList(user, *channel->getUserItInList(channel->getUsersList(), modesparams[paramCt]), addOrRemoveMode);
                    paramCt ++;
                }
                break;

            case    'b': // add/remove from banned userlist
                if(addOrRemoveMode == ADD && channel->getUserItInList(channel->getUsersList(), modesparams[paramCt]) == channel->getUsersList().end())
                    reply(user, ERR_USERNOTINCHANNEL(user.getReplyName(), user.getNickname(), modesparams[paramCt], channel->getName()));
                else if(addOrRemoveMode == REMOVE && channel->getUserItInList(channel->getBanList(), modesparams[paramCt]) == channel->getBanList().end())
                    reply (user, ERR_NOSUCHNICK(user.getReplyName(), user.getNickname(), modesparams[paramCt]));
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
                }
                break;

            case    'o': // add/remove from op list
                if(channel->getUserItInList(channel->getUsersList(), modesparams[paramCt]) == channel->getUsersList().end())
                    reply(user, ERR_USERNOTINCHANNEL(user.getReplyName(), user.getNickname(), modesparams[paramCt], channel->getName()));
                else if (paramCt < modesparams_size)
                {
                    channel->setOpList(user, *channel->getUserItInList(channel->getUsersList(), modesparams[paramCt]), addOrRemoveMode);
                    paramCt ++;
                }
                break;          
            default:
                break;
        }
       
    }
    //if ()
    return (true);
}

void	Server::Mode(User &user, Message &message)
{
    if (!user.getRegistered())
    {
        reply(user, ERR_NOTREGISTERED(user.getReplyName(), user.getNickname()));
        return ;
    }   
    
    // (void) user;
    (void) message;
    int                                     i = 0;
    ssize_t                                 argsNB = 0;
    std::string                             err_buff;
    std::vector< std::string >::iterator    msgEnd = (message._splitMessage).end();
    std::list< Channel >::iterator          channel;
    std::string                             modes;
    std::string                             *modeparams = NULL;

    message._it = (message._splitMessage).begin();
    while (message._it != msgEnd)
    {
        message._it ++;
        argsNB ++;
    }

    // if no args

    if (argsNB == 1) // if (argsNB < 2)
    {
        reply (user, ERR_NEEDMOREPARAMS(user.getReplyName(), user.getNickname(), message._cmd));
        return ;
    }


    message._it = (message._splitMessage).begin(); // delete
    message._it ++; // 2nd arg is supposed to be chan name // delete
    channel = getChanItWithName((*message._it)); // delete
    
    if (channel == _channelsList.end())
    {
        reply(user, ERR_NOSUCHCHANNEL(user.getReplyName(), user.getNickname(), *message._it));
        return ;
    }

    if (channel->isUserInChannel(user) == false)
    {
        err_buff = ERR_NOTONCHANNEL(user.getReplyName(), user.getNickname(), channel->getName());
        send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
        return ;
    }
    
    if (argsNB == 2)
    {
        reply (user, RPL_CHANNELMODEIS(user.getReplyName(), channel->getName(), user.getNickname(), channel->modeIs()));
        return ;
    }

    if (channel->userIsOp(user.getNickname()) == false)
    {
        err_buff = ERR_CHANOPRIVSNEEDED(user.getReplyName(), channel->getName());
        send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
        return ;
    }

    modeparams = new std::string[argsNB];
    
    if (argsNB == 3)
    {
        message._it ++; // 3rd arg is supposed to be modes
        modes = *(message._it);
        modesSet(user, modes, modeparams, channel);
    }
    else if ( argsNB > 3)
    {
        message._it ++; // 3rd arg is supposed to be modes
        modes = *(message._it);
        while (++message._it != msgEnd)
        {
            modeparams[i] = *(message._it); // modeparams[i] = message._arguments[3]; // 4rd arg and so forth are supposed to be modes params
            i ++;
        }
        modesSet(user, modes, modeparams, channel);
    }
    delete[] modeparams;
    return ;
}
