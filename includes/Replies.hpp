/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:58:22 by mgolinva          #+#    #+#             */
/*   Updated: 2023/01/27 12:58:22 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_HPP
#define REPLIES_HPP

#include "irc.hpp"

/*********************************** REPLIES ***********************************/

//01 to 03, welcome rpl

#define RPL_WELCOME(nickname)       "welcome to Internet Relay Network " + nickname + " ! \n"
#define RPL_YOURHOST(servername)    "your host is " + servername ".\n"
#define RPL_CREATED				    "This server was created, in the 6th year of the 6th decade of the 6th century."

//AWAY 301 / 305 / 306

#define	RPL_AWAY(nickname)          nickname + " :Is away" //send when you send a msg to an away user
#define RPL_UNAWAY				    ":You are no longer away"
#define	RPL_NOAWAY				    ":You have been marked as being away"

//LIST 322 / 323

#define	RPL_LIST(channel, topic)    channel + " :" + topic
#define RPL_LISTEND				    ": end of LIST"

//TOPIC / 331 / 332

#define	RPL_NOTOPIC(channel)        channel + " :No topic is set"
#define	RPL_TOPIC(channel, topic)   channel + " :" + topic

//INVITE / 341

#define	RPL_INVITING(channel, nick) nick + " :Was succesfully invited to " + channel 

//OPER / 381

#define RPL_YOUREOPER			    " :You are now an IRC operator"

//USER 392 / 393 / 394 / 395

#define	RPL_USERSTART			                                " :UserID Terminal Host" //sent first
#define	RPL_USERS(username, ttyline /*jsp cque c*/, hostname)   ": " + username + " " + ttyline + " " + hostname
#define RPL_ENDOFUSERS			                                " :End of users"
#define RPL_NOUSERS				                                ":Nobody logged in"

// MODE / 221 (jcomprends pas trop auqnd elle s'envoie elle) / 501

#define	RPL_UMODIS(userModeStr)     " :" + userModeStr

/************************************ ERRORS ************************************/

#define ERR_NEEDMOREPARAMS(cmd) \   cmd + " :Not enough parameters" // 461
#define ERR_UNKNOWNNCOMMAND(cmd)    cmd + " :Unknown command" // 421
#define ERR_PASSWDMISMATCH		    ":Password incorrect" // 464
#define ERR_NOPRIVILEGES		    " :Permission Denied- You're not an IRC operator" // 481

//NICK

#define	ERR_NOSUCHNICK(nick)        nick + " :No such nick" // 401
#define ERR_NONICKNAMEGIVEN		    " :No nickname given" //431
#define ERR_ERRONEUSNICKNAME(nick)  nick + " :Erroneous nickname" //432 when a nick contains invalid char
#define ERR_NICKNAMEINUSE(nick)     nick + " :Nickname is in use" // 433

//USER

#define ERR_ALREADYREGISTERED	    ":Unauthorized command (already registered)" // 462, send as a response to a second USER call trying to overide user info 

//MODE

#define ERR_UMODEUNKNOWNFLAG	    ":Unknown MODE flag" // 501
#define ERR_USERSDONTMATCH		    ":Cannot change mode for other users" // 502

//PRIVMSG and NOTICE

#define ERR_NOTEXTTOSEND		    " :No text to send" // 412
#define ERR_NORECIPIENT(cmd)        " :No recipient given" + cmd // 411 no target to PRIVMSG
#define ERR_TOOMANYTARGETS		    ": there are too many targets to your PM"

//CHANNEL RELATED

#define	ERR_NOSUCHCHANNEL(channel)      channel + " :No such channel" // 403
#define ERR_CANNOTSENDTOCHAN(channel)   channel + " :Cannot send to channel" // 404
#define ERR_UNAVAILRESOURCE(nickOrChan) nickOrChan + " :is temporarily unavailable" //437 pas sur du bail
#define ERR_NOTONCHANNEL(chan)          chan + " :You are not on that channel" // 442
#define ERR_USERONCHANNEL(chan, user)   user + " :Is already on channel " + chan // 443
#define ERR_USERNOTINCHANNEL(nick, chan)nick + ": is not on channel " + chan // 441
#define ERR_CHANOPRIVSNEEDED(chan)      chan + " :You're not channel operator" // 482

// PING & PONG

#define ERR_NOORIGIN			" :No origin specified" // 409 for ping and pong


#endif
