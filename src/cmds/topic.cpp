/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:25 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/10 14:57:58 by aandric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	Server::Topic(User &user, Message &message)
{
    if (message._argsNb < 2)
    {
        // _errMsg = ERR_NEEDMOREPARAMS(message._cmd);
		// send(user.getSockfd(), _errMsg.c_str(), _errMsg.length(), 0);
        reply(user, ERR_NEEDMOREPARAMS(message._cmd));
        return ;
    }
    std::string channel_name = message._arguments[0];
    if (!isChannel(channel_name))
    {
        // _errMsg = ERR_NOSUCHCHANNEL(channel_name);
        // send(user.getSockfd(), _errMsg.c_str(), _errMsg.length(), 0);
        reply(user, ERR_NOSUCHCHANNEL(channel_name));
        return ;
    }
    Channel *channel = getChannelWithName(channel_name);
    if (!channel->isUserInChannel(user)) // check if user in channel
    {
        // _errMsg = ERR_NOTONCHANNEL(channel_name);
        // send(user.getSockfd(), _errMsg.c_str(), _errMsg.length(), 0);
        reply(user, ERR_NOTONCHANNEL(channel_name));
        return ;
    }

    if (message._argsNb == 2) // if user asks for topic of channel
    {
        if (channel->getTopic().empty())
        {
            // _rplMsg = RPL_NOTOPIC(channel_name);
            // send(user.getSockfd(),  _rplMsg.c_str(),  _rplMsg.length(), 0);
            reply(user, RPL_NOTOPIC(channel_name));
            return ;
        }
        else
        {
            // _rplMsg = RPL_TOPIC(channel_name, channel->getTopic()); // give topic to user 
            // send(user.getSockfd(),  _rplMsg.c_str(),  _rplMsg.length(), 0);
            reply(user, RPL_TOPIC(channel_name, channel->getTopic()));
            return ;
        }
    }
    
    if (message._argsNb > 2) // if user wants to set new topic 
    {
        std::string new_topic = get_suffix(&message._arguments[2]);
        if (new_topic.find(":") != 0)
            return ;
         // remove ":" at start of new topic
        if (new_topic.size() == 1) // if empty stirng for topic (after ":""), topic cleared
        {
            channel->setTopic("");
            _rplMsg = "Topic unset on #" + channel_name;
            channel->sendToUsers(_rplMsg); // all  users notified on channel that topic cleared
            return ;
        }
        else
        {
            //new_topic = new_topic.substr(1); // remove ":" at beginning of topic
            if (channel->getTopicStatus() == false || channel->userIsOp(user.getNickname()) == true) // check if user has the rights to set new topic
            {
                channel->setTopic(message._arguments[2]);
                _rplMsg = "New topic set on #" + channel_name + ": " + message._arguments[2] + "\n";
                channel->sendToUsers(_rplMsg);
                return ;
            }
            else
            {
                // _errMsg = ERR_CHANOPRIVSNEEDED(channel_name);
                // send(user.getSockfd(),  _rplMsg.c_str(),  _rplMsg.length(), 0);
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