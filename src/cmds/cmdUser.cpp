/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdUser.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:57:38 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/15 10:48:21 by aandric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	Server::cmdUser(User &user, Message &message)
{
    std::cout << "YO" << std::endl;
    if (message._argsNb < 5)
    {
        reply(user, ERR_NEEDMOREPARAMS(message._cmd));
        return ;
	}
    if (user.getRegistered() == true)
    {
        reply(user, ERR_ALREADYREGISTERED);
        return ;
    }
    user.setUsername(message._arguments[0]);
    if ((message._arguments[1]).length() != 1 || !((message._arguments[1]).find_first_not_of("012345678")) || message._arguments[2] != "*")
    {
        reply(user, "wrong format for user mode: try: '0 *'\n");
        return ;
    }
    if (message._arguments[4].find(":") == 0)
    {
        std::string realname = get_suffix(&message._arguments[4]);
        realname = message._arguments[4].substr(1);
        user.setRealname(realname);
    }
    if (user.getPassword() == this->getPassword())
    {
        user.setRegistered();
        reply(user, RPL_WELCOME(user.getNickname()));
    }
    else
    {
        reply(user, ERR_PASSWDMISMATCH);
        //close user
        return ;
    }
    return ; 
}
