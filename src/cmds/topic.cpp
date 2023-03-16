/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:25 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/16 09:42:59 by aandric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	Server::Topic(User &user, Message &message)
{
    if (message._argsNb < 2)
    {
        reply(user, ERR_NEEDMOREPARAMS(message._cmd));
        return ;
    }
    std::string channel_name = message._arguments[0];
    std::cout << channel_name << std::endl;
    if (!isChannel(channel_name))
    {
        reply(user, ERR_NOSUCHCHANNEL(channel_name));
        return ;
    }
    Channel *channel = getChannelWithName(channel_name); // TO DO > function to get reference to channel to set topic 
    if (!channel->isUserInChannel(user))
    {
        reply(user, ERR_NOTONCHANNEL(channel_name));
        return ;
    }

    if (message._argsNb == 2) // if user asks for topic of channel
    {
        if (channel->getTopic().empty())
        {
            reply(user, RPL_NOTOPIC(channel_name));
            return ;
        }
        else
        {
            reply(user, RPL_TOPIC(channel_name, channel->getTopic()));
            return ;
        }
    }
    
    if (message._argsNb > 2) // if user wants to set new topic 
    {
        std::string new_topic = get_suffix(&message._arguments[1]);
        if (new_topic.find(":") != 0)
            return ;
        if (new_topic.size() == 1) // if empty string for topic (after ":""), topic cleared
        {
            channel->setTopic("");
            _rplMsg = "Topic unset on " + channel_name;
            channel->sendToUsers(_rplMsg); // all  users notified on channel that topic cleared
            return ;
        }
        else
        {
            if (channel->getTopicStatus() == false || channel->userIsOp(user.getNickname()) == true) // check if user has the rights to set new topic
            {
                getChannelWithName(channel_name)->setTopic(new_topic);
                // channel->setTopic(new_topic);
                _rplMsg = "New topic set on " + channel_name + new_topic + "\n";
                channel->sendToUsers(_rplMsg);
                return ;
            }
            else
            {
                reply(user, ERR_CHANOPRIVSNEEDED(channel_name));
                return ;
            }
        }
    }
}

// TOPIC message
//      Command: TOPIC
//   Parameters: <channel> [<topic>]
// The TOPIC command is used to change or view the topic of the given channel. If <topic> is not given, either RPL_TOPIC or RPL_NOTOPIC is returned specifying the current channel topic or lack of one. If <topic> is an empty string, the topic for the channel will be cleared.

// If the client sending this command is not joined to the given channel, and tries to view its’ topic, the server MAY return the ERR_NOTONCHANNEL (442) numeric and have the command fail.

// If RPL_TOPIC is returned to the client sending this command, RPL_TOPICWHOTIME SHOULD also be sent to that client.

// If the protected topic mode is set on a channel, then clients MUST have appropriate channel permissions to modify the topic of that channel. If a client does not have appropriate channel permissions and tries to change the topic, the ERR_CHANOPRIVSNEEDED (482) numeric is returned and the command will fail.

// If the topic of a channel is changed or cleared, every client in that channel (including the author of the topic change) will receive a TOPIC command with the new topic as argument (or an empty argument if the topic was cleared) alerting them to how the topic has changed.

// Clients joining the channel in the future will receive a RPL_TOPIC numeric (or lack thereof) accordingly.

// Numeric Replies:

// ERR_NEEDMOREPARAMS (461)
// ERR_NOSUCHCHANNEL (403)
// ERR_NOTONCHANNEL (442)
// ERR_CHANOPRIVSNEEDED (482)
// RPL_NOTOPIC (331)
// RPL_TOPIC (332)
// RPL_TOPICWHOTIME (333)
// Command Examples:

//   TOPIC #test :New topic          ; Setting the topic on "#test" to
//                                   "New topic".

//   TOPIC #test :                   ; Clearing the topic on "#test"

//   TOPIC #test                     ; Checking the topic for "#test"