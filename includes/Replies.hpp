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

//001 to 003, welcome rpl 

#define RPL_WELCOME(rplname, nickname)              rplname + " 001 " + nickname + " :welcome to IRC_NOUSHMAKS " + nickname + " ! \n"
#define RPL_YOURHOST(rplname, servername)           rplname + " 002:your host is " + servername ".\n"
#define RPL_CREATED                                 rplname + " 003:This server was created, in the 6th year of the 6th decade of the 6th century.\n"

// //AWAY 301 / 305 / 306

// #define	RPL_AWAY(rplname, nickname)                 rplname + " 301 " + nickname + " :Is away\n" //send when you send a msg to an away user
// #define RPL_UNAWAY(rplname)                         rplname + " 305 : You are no longer away\n"
// #define	RPL_NOAWAY(rplname)                         rplname + " 306 : You have been marked as being away\n"

//LIST 322 / 323

// #define	RPL_LIST(rplname, nickname, channel, topic)       rplname + " 322 " + nickname + " " + channel + ": " + topic + "\n"
// #define RPL_LISTEND(rplname, nickname)				      rplname + " 323 " + nickname + ": end of LIST\n"

#define	RPL_LIST(rplname, nick, channel, client_count, topic)       rplname + " 322 " + nick + " " + channel + " " + client_count + " :" + topic + "\n"
#define RPL_LISTEND(rplname, nickname)				        rplname + " 323 " + nickname + " : end of LIST\n"

//TOPIC / 331 / 332

#define	RPL_NOTOPIC(rplname, nickname, channel)           rplname + " 331 " + nickname + " " + channel + " :No topic is set\n"
#define	RPL_TOPIC(rplname, nickname, channel, topic)      rplname + " 332 " + nickname + " " + channel + " " + topic + "\n"

//INVITE / 341

#define	RPL_INVITING(rplname, nick, invite_nick, chan) rplname + " 341 " + nick + " " + invite_nick + " " + chan + "\n"

// //OPER / 381

// #define RPL_YOUREOPER(rplname)			        rplname + " 381 : You are now an IRC operator\n"

//USER 392 / 393 / 394 / 395

#define RPL_NAMEREPLY(rplname, nick, symbol, channel)                       rplname + " 353 " + nick + " " + symbol + " " + channel + " :"
#define RPL_ENDOFNAMES(rplname, nick, channel)                              rplname + " 366 " + nick + " " + channel +" :End of NAMES list\n"     
#define	RPL_USERSTART(rplname)			                                    rplname + " 392:UserID Terminal Host\n" //sent first
#define	RPL_USERS(rplname, username, ttyline /*jsp cque c*/, hostname)      rplname + " 393:" + username + " " + ttyline + " " + hostname + "\n"
#define RPL_ENDOFUSERS(rplname) 			                                rplname + " 394:End of users\n"
#define RPL_NOUSERS(rplname)				                                rplname + " 395:Nobody logged in\n"

// MODE / 221 (jcomprends pas trop auqnd elle s'envoie elle) / 501

#define	RPL_UMODIS(rplname, userModeStr)            rplname + " 221:" + userModeStr + "\n"
#define RPL_CHANNELMODEIS(replynick, channel, nick, modestring)   replynick + " 324 :" + nick + " " + channel + " " + modestring
#define RPL_MUTED(rplname, nick, channel)           rplname + nick + " :Was succesfully muted in " + channel + "\n"
#define RPL_ALLRDYMUTED(rplname, nick, channel)     rplname + nick + " :Was allready muted in " + channel + "\n"
#define RPL_UNMUTED(rplname, nick, channel)         rplname + nick + " :Was succesfully unmuted in " + channel + "\n"
#define RPL_NOTMUTED(rplname, nick, channel)        rplname + nick + " :Was not unmuted in " + channel + "\n"

#define RPL_BANNED(rplname, nick, channel)          rplname + nick + " :Was succesfully banned from " + channel + "\n"
#define RPL_ALLRDYBANNED(rplname, nick, channel)    rplname + nick + " :Was allready banned in " + channel + "\n"
#define RPL_UNBANNED(rplname, nick, channel)        rplname + nick + " :Was succesfully unbanned from " + channel + "\n"
#define RPL_NOTBANNED(rplname, nick, channel)       rplname + nick + " :Was not banned in " + channel + "\n"

#define RPL_OPED(rplname, nick, channel)            rplname + nick + " :Was succesfully made operator in " + channel + "\n"
#define RPL_ALLRDYOP(rplname, nick, channel)        rplname + nick + " :Was allready chanop in " + channel + "\n"
#define RPL_UNOPED(rplname, nick, channel)          rplname + nick + " :Was succesfully de-oped in " + channel + "\n"
#define RPL_NOTOP(rplname, nick, channel)           rplname + nick + " :Was not chanop in " + channel + "\n"

#define RPL_USERLIMITSET(rplname, channel, nbr)     rplname + "  " + channel + " :Users limit was set to : " + nbr + "\n"

//WHO 352

#define RPL_WHOREPLY(rplname, channel, username, host, server, nick, flags, realname) rplname + " 352 " + channel + " " + username + " " + host + " " + nick +  " " + flags + " :1 " + realname + "\n" 

/************************************ ERRORS ************************************/

#define ERR_NEEDMOREPARAMS(rplname, nick, cmd)        rplname + " 461 " + nick + " " + cmd + ":Not enough parameters\n" // 461
#define ERR_UNKNOWNNCOMMAND(rplname, nick, cmd)       rplname + " 421 " + nick + " " + cmd + ":Unknown command\n" // 421
#define ERR_PASSWDMISMATCH(rplname)		        rplname + " 464 : Password incorrect\n" // 464
#define ERR_NOPRIVILEGES(rplname)		        rplname + " 481 :Permission Denied- You're not an IRC operator\n" // 481

//NICK

#define	ERR_NOSUCHNICK(rplname, nick, target)   rplname + " 406 " + nick + " " + target + ":No such nick\n" // 401
#define ERR_NONICKNAMEGIVEN(rplname, nick)		rplname + " 431 " + nick + ":No nickname given\n" //431
#define ERR_ERRONEUSNICKNAME(rplname, nick)     rplname + " 432 " + nick + ":Erroneous nickname\n" //432 when a nick contains invalid char
#define ERR_NICKNAMEINUSE(rplname, nick, newnick)        rplname + " 433 " + nick + " " + newnick + ":Nickname is in use\n" // 433
//#define CMD_NICK()

//USER

#define ERR_ALREADYREGISTERED(rplname, nick)	rplname + " 462 " + nick + " : Unauthorized command (already registered)\n" // 462, send as a response to a second USER call trying to overide user info 
#define ERR_NOTREGISTERED(rplname, nick)        rplname + " 451 " + nick + " :You have not registered\n"

//MODE

#define ERR_UMODEUNKNOWNFLAG(rplname, nick)	        rplname + " 501: Unknown MODE flag\n" // 501
#define ERR_USERSDONTMATCH(rplname)		        rplname + " 502: Cannot change mode for other users\n" // 502
#define ERR_INVITEONLYCHAN(rplname, chan)       rplname + " 473 " + chan + ":is invite only\n"

//PRIVMSG and NOTICE

#define ERR_NOTEXTTOSEND(rplname, nick)		    rplname + " 412 " + nick + " : No text to send\n" // 412
#define ERR_NORECIPIENT(rplname, cmd)           rplname + " 411: No recipient given" + cmd + "\n" // 411 no target to PRIVMSG
#define ERR_TOOMANYTARGETS(rplname, cmd)		rplname + " 407 " + cmd + ":there are too many targets to your action\n"

//CHANNEL RELATED

#define	ERR_NOSUCHCHANNEL(rplname, nick, channel)         rplname + " 402 " + nick + " " + channel + " :No such channel\n" // 403
#define ERR_CANNOTSENDTOCHAN(rplname, channel)      rplname + " 404 " + channel + " :Cannot send to channel\n" // 404
#define ERR_UNAVAILRESOURCE(rplname, nickOrChan)    rplname + nickOrChan + " :is temporarily unavailable\n" //437 pas sur du bail
#define ERR_NOTONCHANNEL(rplname, nick, chan)       rplname + " 442 " + nick + " " + chan + " :You are not on that channel\n" // 442
#define ERR_USERONCHANNEL(rplname, chan, user)      rplname + " 443 " + user + " :Is already on channel " + chan + "\n" // 443
#define ERR_USERNOTINCHANNEL(rplname, nick, target, chan)   rplname + " 441 " + nick + " " + target + " " + chan +" :is not on channel\n" // 441
#define ERR_BADCHANNELKEY(rplname, nick ,chan)      rplname + " 475 " + nick + " " + chan + " :cannot join channel (+k)\n" // 475
#define ERR_CHANOPRIVSNEEDED(rplname, chan)         rplname + " 482 " + chan + " :You're not channel operator\n" // 482
#define ERR_BANNEDFROMCHAN(rplname, nick, chan)     rplname + + " 474 " + nick + " " + chan + " :Cannot join channel (+b)\n"
#define ERR_USERLIMITREACHED(rplname, chan)         rplname + chan + " :users limit reached\n"

// PING & PONG

#define ERR_NOORIGIN(rplname, nick)			            rplname + " 409 " + nick + ":No origin specified\n" // 409 for ping and pong


#endif
