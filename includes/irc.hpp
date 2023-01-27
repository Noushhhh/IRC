/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:58:01 by aandric           #+#    #+#             */
/*   Updated: 2023/01/27 16:22:51 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
#define IRC_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cerrno>
#include <list>
#include <sstream>
#include <unistd.h>

#include "Server.hpp"
#include "User.hpp"
#include "Replies.hpp"

#define BACKLOG 10

//#include "Server.hpp"

// crete a server with a socket. Listen entries in particular entry to get new msgs / clients
// In server >> Chanel, users, state
// 

// get messages from client and parse them >> execute command 
// test with one function of command and then do other functions 
// each socket in one user 
// 



#endif 