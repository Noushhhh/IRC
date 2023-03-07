/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:57:52 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/07 10:13:36 by aandric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"
#include "../../includes/Channel.hpp"

static void joinRPL(Channel chan, User user)
{
    //TO DO : if channel mode is quiet only one username is sent (the activ user)

    std::string                 rpl_buff = RPL_TOPIC(chan.getName(), chan.getTopic());;
    std::list< User >::iterator it = chan.getUsersList().begin();

    if (chan.getTopic().empty())
        rpl_buff = RPL_NOTOPIC(chan.getName());
    send (user.getSockfd(), rpl_buff.c_str(), rpl_buff.length(), 0);

    if (chan.getUsersList().size() == 0)
    {
        rpl_buff = RPL_NOUSERS;
        send (user.getSockfd(), rpl_buff.c_str(), rpl_buff.length(), 0);
        return ;
    }

    rpl_buff = RPL_USERSTART;
    send (user.getSockfd(), rpl_buff.c_str(), rpl_buff.length(), 0);
    while (it != chan.getUsersList().end())
    {
        rpl_buff = RPL_USERS(it->getNickname(),,);
        send (user.getSockfd(), rpl_buff.c_str(), rpl_buff.length(), 0);
        it ++;
    }
    rpl_buff = RPL_ENDOFUSERS;
    send (user.getSockfd(), rpl_buff.c_str(), rpl_buff.length(), 0);
}

static void remove_from_all_channels(User &user, std::list< Channel > &channelList)
{
    std::list< Channel >::iterator  cIt = channelList.begin();
    std::list< User >::iterator     uIt;
    while (cIt != channelList.end())
    {
        uIt = cIt->getUsersList().begin();
        while (uIt != cIt->getUsersList().end())
        {
            if (user.getNickname() == uIt->getNickname())
            {
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
    // for (int i = 0; i < ct; i ++)
    //     std::cout << "strArray ["<< i << "] :" << strArray[i] << std::endl;
    // std::cout << std::endl;
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
        err_buff = ERR_NEEDMOREPARAMS(std::string("JOIN"));
        send(user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
        return ;
    }
    if (message._splitMessage.size() == 2 || message._splitMessage.size() == 3)
        chansSplit = split(std::string(*message._it));
    if (message._splitMessage.size() == 3)
        keysSplit = split(*(message._it + 1));
    if (message._splitMessage.size() > 3)
    {
        err_buff = ERR_TOOMANYTARGETS(std::string("JOIN"));
        send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
        return ;
    }

    // if passed arg is 0, remove user from all chans
    
    if (message._splitMessage.size() == 2 && *(message._it) == "0")
    {
        remove_from_all_channels(user, _channelsList);
        user.getJoinedChans().erase(user.getJoinedChans().begin(), user.getJoinedChans().end());
        err_buff = " :succesfully removed from all channels\n";
        send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
    }
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

                    if (user.isOnChan(_channelsListIt->getName()))
                    {
                        err_buff = ERR_USERONCHANNEL(_channelsListIt->getName(), user.getNickname());
                        send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
                        chanExist = true;
                        break ;
                    }
                    // keep from joining if is invite only or user is banned or user limit is reached

                    if (_channelsListIt->getInviteStatus() == true)
                    {
                        err_buff = ERR_ISINVITEONLY(_channelsListIt->getName());
                        send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
                        break ;
                    }
                    if (_channelsListIt->userIsBanned(user.getNickname()) == true)
                    {
                        err_buff = ERR_ISBANNED(_channelsListIt->getName());
                        send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
                        break ;
                    }
                    if (_channelsListIt->getUsersLimitStatus() == true  && _channelsListIt->getUsersLimit() >= _channelsListIt->getUsersList().size())
                    {
                        err_buff = ERR_USERLIMITREACHED(_channelsListIt->getName());
                        send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
                        break ;
                    }
                    
                    //if chan is key protected and a key args was given to JOIN cmd and it matchs chan key
                    
                    if ((_channelsListIt->getPswdStatus() && message._splitMessage.size() > 2 &&
                    i < ft_arraySize(keysSplit) && pswdMatch(_channelsListIt->getPswd(), keysSplit[i]))
                    || (!_channelsListIt->getPswdStatus()))
                    {
                        _channelsListIt->getUsersList().push_back(user);
                        user.getJoinedChans().push_back(*_channelsListIt);
                        joinRPL(*_channelsListIt, user);
                        chanExist = true;
                        break ;
                    }
                    // std::cout << "given pswd = " << keysSplit[i] << "pswd = " << _channelsListIt->getPswd() << std::endl; 
                    err_buff = ERR_BADCHANNELKEY(_channelsListIt->getName());
                    send (user.getSockfd(), err_buff.c_str(), err_buff.length(), 0);
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
                        Channel newChan(chansSplit[i], keysSplit[i], user);
                        _channelsList.push_back(newChan);
                        user.getJoinedChans().push_back(newChan);
                        joinRPL(newChan, user);
                    }
                    
                    //if none is
                    else
                    {
                        Channel newChan(chansSplit[i], user);
                        _channelsList.push_back(newChan);
                        user.getJoinedChans().push_back(newChan);
                        joinRPL(newChan, user);
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
