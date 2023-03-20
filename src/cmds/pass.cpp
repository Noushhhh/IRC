/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:16 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/20 13:46:49 by aandric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	Server::Pass(User &user, Message &message)
{
	if (message._argsNb < 2)
	{
		reply(user, ERR_NEEDMOREPARAMS(user.getReplyName(), message._cmd));
		return ;
	}
	if (user.getRegistered() == true)
	{
		reply(user, ERR_ALREADYREGISTERED(user.getReplyName()));
		return ;
	}
	else
		user.setPassword(message._arguments[0]);
}

// PASS message
//      Command: PASS
//   Parameters: <password>
// The PASS command is used to set a ‘connection password’. If set, the password must be set before any attempt to register the connection is made. This requires that clients send a PASS command before sending the NICK / USER combination.

// The password supplied must match the one defined in the server configuration. It is possible to send multiple PASS commands before registering but only the last one sent is used for verification and it may not be changed once the client has been registered.

// If the password supplied does not match the password expected by the server, then the server SHOULD send ERR_PASSWDMISMATCH (464) and MAY then close the connection with ERROR. Servers MUST send at least one of these two messages.

// Servers may also consider requiring SASL authentication upon connection as an alternative to this, when more information or an alternate form of identity verification is desired.

// Numeric replies:

// ERR_NEEDMOREPARAMS (461)
// ERR_ALREADYREGISTERED (462)
// ERR_PASSWDMISMATCH (464)
// Command Example:

//   PASS secretpasswordhere
