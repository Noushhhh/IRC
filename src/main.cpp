/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:01:07 by aandric           #+#    #+#             */
/*   Updated: 2023/01/23 17:50:38 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"


int main()
{
	int sock;
	struct addrinfo hints, *res;

	memset(&hints, 0, sizeof hints);
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;  // use IPv4 or IPv6, whichever
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; // fill in IP for me

	std::cout << getaddrinfo(0, "3490", &hints, &res) << std::endl;
	sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	std::cout << sock << std::endl;
	if (sock == -1)
	{
		//std::cerr << "error: socket" << std::endl;
		std::cout << "Or, in German, " << std::strerror(errno) << std::endl;
		return 0;
	}
	bind(sock, res->ai_addr, res->ai_addrlen);
	return 0;
}

// listen()  for incoming connections on a specific port—multiplayer network games do this when they tell you to “connect to 192.168.5.10 port 3490”.) 