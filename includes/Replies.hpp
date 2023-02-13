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

#define RPL_WELCOME				(nickname) \ "welcome to Internet Relay Network " + nickname + " ! \n"
#define RPL_YOURHOST			(servername) \ "your host is " + servername ".\n"
#define RPL_CREATED				"This server was created, in the 6th year of the 6th decade of the 6th century."

#define	RPL_AWAY				(nickname, msg) \ nickname + " :" + msg
#define RPL_UNAWAY				":You are no longer away"
#define	ERR_NOSUCHNICK			"401"
#define	ERR_NOSUCHSERVER		"402"
#define	ERR_NOSUCHCHANNEL		"403"
#define ERR_CANNOTSENDTOCHAN	"404"
#define ERR_TOOMANYCHANNELS		"405"
#define ERR_TOOMANYTARGETS		"407"
#define ERR_NOORIGIN			"409"
#define ERR_NORECIPIENT			"411"
#define ERR_NOTEXTTOSEND		"412"
#define ERR_NOTOPLEVEL			"413"
#define ERR_WILDTOPLEVEL		"414"
#define ERR_UNKNOWNNCOMMAND		"421"
#define ERR_NOADMININFO			"423"
// #define ERR_FILEERROR			"424" si on fait les bobos
#define ERR_NONICKNAMEGIVEN		"431"
#define ERR_NICKNAMEINUSE		"433"
#define ERR_USERNOTINCHANNEL	"441"
#define ERR_NOTONCHANNEL		"442"
#define ERR_USERONCHANNEL		"443"
#define ERR_NOLOGIN				"444"
#define ""
#define ""
#define ""
#define ""
#define ""
#define ""
#define ""
#define ""
#define ""

class Replies
{
private	:


public	:

	Replies();
	Replies(const Replies &src);
	~Replies();
	
	Replies &operator=(const Replies &src);

	
};



#endif
