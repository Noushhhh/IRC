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

#define 

// add /n at the ned of every string 

/*********************************** REPLIES ***********************************/

//01 to 03, welcome rpl

#define RPL_WELCOME(nickname)       ":ircserv 01 welcome to IRC NOUSHMAKS " + nickname + " ! \n"
#define RPL_YOURHOST(servername)    "02 your host is " + servername ".\n"
#define RPL_CREATED				    "03 This server was created, in the 6th year of the 6th decade of the 6th century.\n"

//AWAY 301 / 305 / 306

#define	RPL_AWAY(nickname)          "301" + nickname + " :Is away\n" //send when you send a msg to an away user
#define RPL_UNAWAY				    "305 : You are no longer away\n"
#define	RPL_NOAWAY				    "306 : You have been marked as being away\n"

//LIST 322 / 323

#define	RPL_LIST(channel, topic)    "322 " + channel + " " + topic + "\n"
#define RPL_LISTEND				    "323: end of LIST\n"

//JOIN

#define RPL_JOINZERO(nick)          nick + " :succesfully removed from all channels\n"

//TOPIC / 331 / 332

#define	RPL_NOTOPIC(channel)        "331 " + channel + ": No topic is set\n"
#define	RPL_TOPIC(channel, topic)   "332 "+ channel + " " + topic + "\n"

//INVITE / 341

#define	RPL_INVITING(channel, nick) "341 " + nick + ": Was succesfully invited to " + channel + "\n"

//OPER / 381

#define RPL_YOUREOPER			    "381 : You are now an IRC operator\n"

//USER 392 / 393 / 394 / 395

#define	RPL_USERSTART			                                "392: UserID Terminal Host\n" //sent first
#define	RPL_USERS(username, ttyline /*jsp cque c*/, hostname)   "393: " + username + " " + ttyline + " " + hostname + "\n"
#define RPL_ENDOFUSERS			                                "394: End of users\n"
#define RPL_NOUSERS				                                "395: Nobody logged in\n"

// MODE / 221 (jcomprends pas trop auqnd elle s'envoie elle) / 501

#define	RPL_UMODIS(userModeStr)     "221:" + userModeStr + "\n"
#define RPL_MUTED(nick, channel)    nick + ": Was succesfully muted in " + channel + "\n"
#define RPL_ALLRDYMUTED(nick, channel)    nick + ": Was allready muted in " + channel + "\n"
#define RPL_UNMUTED(nick, channel)  nick + ": Was succesfully unmuted in " + channel + "\n"
#define RPL_NOTMUTED(nick, channel)  nick + ": Was not unmuted in " + channel + "\n"

#define RPL_BANNED(nick, channel)   nick + ": Was succesfully banned from " + channel + "\n"
#define RPL_ALLRDYBANNED(nick, channel)    nick + ": Was allready banned in " + channel + "\n"
#define RPL_UNBANNED(nick, channel) nick + ": Was succesfully unbanned from " + channel + "\n"
#define RPL_NOTBANNED(nick, channel)  nick + ": Was not banned in " + channel + "\n"

#define RPL_OPED(nick, channel)     nick + ": Was succesfully made operator in " + channel + "\n"
#define RPL_ALLRDYOP(nick, channel)    nick + ": Was allready chanop in " + channel + "\n"
#define RPL_UNOPED(nick, channel)   nick + ": Was succesfully de-oped in " + channel + "\n"
#define RPL_NOTOP(nick, channel)  nick + ": Was not chanop in " + channel + "\n"

#define RPL_USERLIMITSET(channel, nbr) " " + channel + ": Users limit was set to : " + nbr + "\n"

/************************************ ERRORS ************************************/

#define ERR_NEEDMOREPARAMS(cmd)     "461 " + cmd + ": Not enough parameters\n" // 461
#define ERR_UNKNOWNNCOMMAND(cmd)    "421 " + cmd + ": Unknown command\n" // 421
#define ERR_PASSWDMISMATCH		    "464: Password incorrect\n" // 464
#define ERR_NOPRIVILEGES		    "481: Permission Denied- You're not an IRC operator\n" // 481

//NICK

#define	ERR_NOSUCHNICK(nick)        "406 " + nick + ": No such nick\n" // 401
#define ERR_NONICKNAMEGIVEN		    "431: No nickname given\n" //431
#define ERR_ERRONEUSNICKNAME(nick)  "432 " + nick + ": Erroneous nickname\n" //432 when a nick contains invalid char
#define ERR_NICKNAMEINUSE(nick)     "433 "nick + ": Nickname is in use\n" // 433

//USER

#define ERR_ALREADYREGISTERED	    "462: Unauthorized command (already registered)\n" // 462, send as a response to a second USER call trying to overide user info 

//MODE

#define ERR_UMODEUNKNOWNFLAG	    "501: Unknown MODE flag\n" // 501
#define ERR_USERSDONTMATCH		    "502: Cannot change mode for other users\n" // 502
#define ERR_INVITEONLYCHAN(chan)    "473 " + chan + ": is invite only\n"

//PRIVMSG and NOTICE

#define ERR_NOTEXTTOSEND		    "412: No text to send\n" // 412
#define ERR_NORECIPIENT(cmd)        "411: No recipient given" + cmd + "\n" // 411 no target to PRIVMSG
#define ERR_TOOMANYTARGETS(cmd)		"407 " + cmd + ": there are too many targets to your action\n"

//CHANNEL RELATED

#define	ERR_NOSUCHCHANNEL(channel)      "402 " + channel + ": No such channel\n" // 403
#define ERR_CANNOTSENDTOCHAN(channel)   "404 " + channel + ": Cannot send to channel\n" // 404
#define ERR_UNAVAILRESOURCE(nickOrChan) nickOrChan + ": is temporarily unavailable\n" //437 pas sur du bail
#define ERR_NOTONCHANNEL(chan)          "442 " + chan + ": You are not on that channel\n" // 442
#define ERR_USERONCHANNEL(chan, user)   "443 " + user + ": Is already on channel " + chan + "\n" // 443
#define ERR_USERNOTINCHANNEL(nick, chan)"451 " + nick + ": is not on channel " + chan + "\n" // 441
#define ERR_ISCHANOP(nick)              nick + ": is chanop and cannot be muted, banned or unoped\n"
#define ERR_BADCHANNELKEY(chan)         "475 " + chan + ": Cannot join channel (+k)\n" // 475
#define ERR_CHANOPRIVSNEEDED(chan)      "482 " + chan + ": You're not channel operator\n" // 482
#define ERR_ISBANNED(nick, chan)        nick + ": is banned from " + chan + "\n"
#define ERR_USERLIMITREACHED(chan)      chan + ": users limit reached\n"

// PING & PONG

#define ERR_NOORIGIN			"409: No origin specified\n" // 409 for ping and pong


#endif
