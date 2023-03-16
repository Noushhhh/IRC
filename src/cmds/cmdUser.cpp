/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdUser.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:57:38 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/16 10:29:20 by aandric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void	Server::cmdUser(User &user, Message &message)
{
    if (message.getArgsNb() < 5)
    {
        reply(user, ERR_NEEDMOREPARAMS(message.getCmd()));
        return ;
	}
    if (user.getRegistered() == true)
    {
        reply(user, ERR_ALREADYREGISTERED);
        return ;
    }
    user.setUsername((message.getArguments())[0]);
    if ((message.getArguments())[1].length() != 1 || !(((message.getArguments())[1]).find_first_not_of("012345678")) || (message.getArguments())[2] != "*")
    {
        reply(user, "wrong format for user mode: try: '0 *'\n");
        return ;
    }
    if ((message.getArguments())[4].find(":") == 0)
    {
        std::string realname = get_suffix(&(message.getArguments())[4]);
        realname = (message.getArguments())[4].substr(1);
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
