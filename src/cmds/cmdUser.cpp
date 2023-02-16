/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdUser.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:57:38 by mgolinva          #+#    #+#             */
/*   Updated: 2023/02/14 14:58:52 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

bool	Server::cmdUser(User &user, Message &message)
{
    std::cout << message._argsNb << std::endl;
    if (message._argsNb != 6)
    {
        std::string err_msg1 = ERR_NEEDMOREPARAMS(message._cmd);
		send(user.getSockfd(), err_msg1.c_str(), err_msg1.length(), 0);
		return false;
	}
    if (user.getRegistered())
    {
        std::string err_msg = ERR_ALREADYREGISTERED;
		send(user.getSockfd(), err_msg.c_str(), err_msg.length(), 0);
		return false;
    }
    message._it = message._splitMessage.begin() + 1;
    user.setUsername(*message._it);
    message._it++;
    if ((*message._it).length() != 1 || !((*message._it).find_first_not_of("012345678")) || (*(message._it + 1) != "*"))
    {
        std::cout << "wrong format for user mode: try: '0 *'" << std::endl;
        return false ;
    }
    user.setBitMode((uint8_t) std::stoi(*message._it));
    message._it + 2;
    user.setRealname(*message._it + " " + *(message._it + 1));
    // split with separator ":""
    if (user.getPassword() == this->getPassword())
        user.setRegistered();
    std::string welcome_msg = "WELCOME TO THE FUTURE " + user.getNickname() + "\n";
	send(user.getSockfd(), welcome_msg.c_str(), welcome_msg.length(), 0);
    // welcome msg
    return true ;
}


// Example:

//    USER guest 0 * :Ronnie Reagan   ; User registering themselves with a
//                                    username of "guest" and real name
//                                    "Ronnie Reagan".

//    USER guest 8 * :Ronnie Reagan   ; User registering themselves with a
//                                    username of "guest" and real name
//                                    "Ronnie Reagan", and asking to be set
//                                    invisible.
