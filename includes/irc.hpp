/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:58:01 by aandric           #+#    #+#             */
/*   Updated: 2023/03/01 14:31:50 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
#define IRC_HPP
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <list>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <poll.h>
#include <cstdlib>
#include <fcntl.h>
#include <strings.h>
#include <string>
#include <limits.h>
#include <algorithm>
#include <iterator>

#include "User.hpp"
#include "Message.hpp"
#include "Replies.hpp"
#include "Channel.hpp"
#include "Server.hpp"

#define BACKLOG         10
#define TIMEOUTLIMIT    -1
#define MAX_CHAR        512

#define SO_EE_ORIGIN_NONE    0
#define SO_EE_ORIGIN_LOCAL   1
#define SO_EE_ORIGIN_ICMP    2
#define SO_EE_ORIGIN_ICMP6   3

std::string *cppsplit(std::string str, char sep);
size_t      ft_arraySize(std::string *array);
bool        isCharset(char c, std::string charset);







// crete a server with a socket. Listen entries in particular entry to get new msgs / clients
// In server >> Chanel, users, state
// 

// get messages from client and parse them >> execute command 
// test with one function of command and then do other functions 
// each socket in one user 
// 



#endif 