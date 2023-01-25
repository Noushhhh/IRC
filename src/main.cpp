/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:01:07 by aandric           #+#    #+#             */
/*   Updated: 2023/01/25 16:16:43 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"


int main(int ac, char **av)
{
	int sock;
	struct sockaddr_in my_addr;

	if (ac < 2)
		return 0;
	
	int port = std::atoi(av[1]);

	my_addr.sin_family = AF_INET; // use IPv4 or IPv6, whichever
	my_addr.sin_port = htons(port);
	my_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // or INADDR_ANY >> set random usable IP Address
	std::memset(my_addr.sin_zero, 0, sizeof( my_addr.sin_zero));

	sock = socket(my_addr.sin_family, SOCK_STREAM, 0);
	std::cout << sock << std::endl;
	if (sock == -1)
	{
		std::cout << "error: socket: " << std::strerror(errno) << std::endl;
		return 0;
	}
	if (bind(sock, (struct sockaddr *)&my_addr, sizeof(my_addr)) < 0)
	{
		std::cout << "error: bind: " << std::strerror(errno) << std::endl;
		return 0;
	}
	if (listen(sock, BACKLOG) < 0)
	{
		std::cout << "error: listen: " << std::strerror(errno) << std::endl;
		return 0;
	}

	// while (1)
	// {
		socklen_t addr_size;
		struct sockaddr their_addr;
		addr_size = sizeof(their_addr);
		int new_socket = accept(sock, (struct sockaddr *)&their_addr, &addr_size);
		if (new_socket < 0)
		{
			std::cout << "error: accept: " << std::strerror(errno) << std::endl;
			return 0;
		}
		char buff[250];
		while (recv(new_socket, buff, sizeof(buff), 0) > 0)
		//recv(new_socket, buff, sizeof(buff), 0);
		{
			std::cout << buff;
			memset(buff, 0, 250); 
		}
	// }
	return 0;
}

// listen()  for incoming connections on a specific port—multiplayer network games do this when they tell you to “connect to 192.168.5.10 port 3490”.) 