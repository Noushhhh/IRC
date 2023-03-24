/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:57:52 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/24 14:02:05 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"
#include "../../includes/Channel.hpp"

void        namelistRPL(Channel &chan, User user)
{
    std::string                  rpl_buff;
    std::list< User *>::iterator it = chan.getUsersList().begin();
    
    if (chan.getUsersList().size() == 0)
    {
        rpl_buff = RPL_NOUSERS(user.getReplyName());
        send (user.getSockfd(), rpl_buff.c_str(), rpl_buff.length(), 0);
        return ;
    }
    if (chan.getSecrecyStatus())
        rpl_buff = RPL_NAMEREPLY((*it)->getReplyName(), (*it)->getNickname(), "@", chan.getName());
    if (chan.getPrivacyStatus())
        rpl_buff = RPL_NAMEREPLY((*it)->getReplyName(), (*it)->getNickname(), "*", chan.getName());
    else
        rpl_buff = RPL_NAMEREPLY((*it)->getReplyName(), (*it)->getNickname(), "=", chan.getName());
    while (it != chan.getUsersList().end())
    {
        if (chan.userIsOp((*it)->getNickname()) == true)
            rpl_buff += "@" + (*it)->getNickname() += " ";
        else if (chan.userIsMuted((*it)->getNickname()) == false)
            rpl_buff += "+" + (*it)->getNickname() += " ";
        else
            rpl_buff += (*it)->getNickname() += " ";
        it ++;
    }
    rpl_buff += "\n";
    reply (user, rpl_buff);
    chan.sendToUsers(rpl_buff);
    reply (user, RPL_ENDOFNAMES(user.getReplyName(), user.getNickname(),chan.getName()));
    chan.sendToUsers(RPL_ENDOFNAMES(user.getReplyName(), user.getNickname(),chan.getName()));
}

void joinRPL(Channel &chan, User user)
{
    //TO DO : if channel mode is quiet only one username is sent (the activ user)

    std::string                  rpl_buff = RPL_TOPIC(user.getReplyName(), user.getNickname(), chan.getName(), chan.getTopic());

    if (chan.getQuietStatus() == true)
        return ;

    if (chan.getTopic().empty())
        rpl_buff = RPL_NOTOPIC(user.getReplyName(), user.getNickname(), chan.getName());
    chan.sendToUsers(user.getReplyName() + " JOIN " + chan.getName() + "\n");
    // chan.sendToUsers(rpl_buff);
    reply(user, rpl_buff);
    namelistRPL(chan, user);
}

void remove_from_all_channels(User &user, std::list< Channel > &channelList)
{
    std::list< Channel >::iterator  cIt = channelList.begin();
    std::list< User *>::iterator     uIt;
    user.getJoinedChans().erase(user.getJoinedChans().begin(), user.getJoinedChans().end());
    while (cIt != channelList.end())
    {
        uIt = cIt->getUsersList().begin();
        while (uIt != cIt->getUsersList().end())
        {
            if (user.getNickname() == (*uIt)->getNickname())
            {
                cIt->sendToUsers(user.getReplyName() + " PART " + cIt->getName() + "\n");
                cIt->getUsersList().erase(uIt);
                break ;
            }
            uIt ++;
        }
        cIt ++;
    }
}

static std::string *split(std::string str)
{
    int i = 0;
    int ct = 1;
    while (str[i])
    {
        if (str[i] == ',')
            ct ++;
        i ++;
    }
    std::string *strArray = new std::string[ct + 1];
    for (int i = 0; i < ct; i ++)
    {
        for (int j = 0; str[j]; j ++)
        {
            if (str[j] == ',')
            {
                if (strArray[i].empty())
                    strArray[i].push_back('\0');
                i ++;
            }
            else if (i < ct && str[j] && str[j] != ',')
                strArray[i].push_back(str[j]);
        }
    }
    return (strArray);
}

static bool pswdMatch(const std::string &chanPswd, std::string givenPswd)
{
    if (givenPswd.find('\n') != std::string::npos)
        givenPswd = givenPswd.substr(0, givenPswd.size() - 2);
    if (chanPswd == givenPswd)
        return (true);
    return (false);
}

void	Server::Join(User &user, Message &message)
{
	std::string err_buff;
    std::string *chansSplit = NULL;
    std::string *keysSplit = NULL;
    std::string::iterator it;
    bool chanExist = false;

    message._it = message._splitMessage.begin() + 1; // channel name

    if (message._splitMessage.size() == 1)
    {
        reply(user, ERR_NEEDMOREPARAMS(user.getReplyName(), user.getNickname(), message._cmd));
        return ;
    }
    if (message._splitMessage.size() == 2 || message._splitMessage.size() == 3)
        chansSplit = split(std::string(*message._it));
    if (message._splitMessage.size() == 3)
        keysSplit = split(*(message._it + 1));
    if (message._splitMessage.size() > 3)
    {
        reply(user, ERR_TOOMANYTARGETS(user.getReplyName(), message._cmd));
        return ;
    }

    // if passed arg is 0, remove user from all chans
    
    if (message._splitMessage.size() == 2 && *(message._it) == "0")
        remove_from_all_channels(user, _channelsList);
        
    else
    {    
        // look for the channel to join
        for (size_t i = 0; i < ft_arraySize(chansSplit); i ++)
        {
            chanExist = false;
            for (_channelsListIt = _channelsList.begin(); _channelsListIt != _channelsList.end(); _channelsListIt ++)
            {
                // if chan exist, user will join
                if (_channelsListIt->getName() == chansSplit[i])
                {
                    // if allready on channel

                    if (_channelsListIt->getUserItInList(_channelsListIt->getUsersList(), user.getNickname()) != _channelsListIt->getUsersList().end())
                    {
                        reply (user, ERR_USERONCHANNEL(user.getReplyName(), _channelsListIt->getName(), user.getNickname()));
                        chanExist = true;
                        break ;
                    }

                    // keep from joining if is invite only or user is banned or user limit is reached

                    if (_channelsListIt->getInviteStatus() == true)
                    {
                        reply (user, ERR_INVITEONLYCHAN(user.getReplyName(), _channelsListIt->getName()));
                        chanExist = true;
                        break ;
                    }
                    else if (_channelsListIt->userIsBanned(user.getNickname()) == true)
                    {
                        reply (user, ERR_BANNEDFROMCHAN(user.getReplyName(), user.getNickname(), _channelsListIt->getName()));
                        chanExist = true;
                        break ;
                    }
                    else if (_channelsListIt->getUsersLimitStatus() == true  && _channelsListIt->getUsersLimit() <= _channelsListIt->getUsersList().size())
                    {
                        reply (user, ERR_USERLIMITREACHED(user.getReplyName(), _channelsListIt->getName()));
                        chanExist = true;
                        break ;
                    }
                    
                    //if chan is key protected and a key args was given to JOIN cmd and it matchs chan key
                    
                    if ((_channelsListIt->getPswdStatus() && message._splitMessage.size() > 2 &&
                    i < ft_arraySize(keysSplit) && pswdMatch(_channelsListIt->getPswd(), keysSplit[i]))
                    || (!_channelsListIt->getPswdStatus()))
                    {
                        _channelsListIt->getUsersList().push_back(&user);
                        user.getJoinedChans().push_back(&(*_channelsListIt));
                        joinRPL(*_channelsListIt, user);
                        chanExist = true;
                        break ;
                    }
                    reply (user, ERR_BADCHANNELKEY(user.getReplyName(), user.getNickname(), _channelsListIt->getName()));
                    chanExist = true;
                    break ;
                }
            }

            // if chan doesn't already exist it is created, upon the condition his name is valid
            if (!chanExist)
            {
                try
                {
                    // if a keyword is specified
                    
                    if (message._splitMessage.size() > 2 && i < ft_arraySize(keysSplit) && keysSplit[i][0] != 0)
                    {
                        // if (i > keysSplit->size())
                        Channel *newChan = new Channel(chansSplit[i], keysSplit[i], user);
                        user.getJoinedChans().push_back(newChan);
                        _channelsList.push_back(*newChan);
                        joinRPL(*getChannelWithName(newChan->getName()), user);
	                    // reply (user, RPL_CHANNELMODEIS(user.getReplyName(), newChan->getName(), user.getNickname(), newChan->modeIs()));
                    }
                    
                    //if none is
                    else
                    {
                        Channel *newChan = new Channel(chansSplit[i], user);
                        user.getJoinedChans().push_back(newChan);
                        _channelsList.push_back(*newChan);
                        joinRPL(*getChannelWithName(newChan->getName()), user);
	                    // reply (user, RPL_CHANNELMODEIS(user.getReplyName(), newChan->getName(), user.getNickname(), newChan->modeIs()));
                    }
                    
                }
                catch(const Channel::BadNameException& e)
                {
                    err_buff = chansSplit[i];
                    err_buff.append(e.badName());
                    send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
                }
            }
        }
    }

    delete[] chansSplit;
    delete[] keysSplit;
}
