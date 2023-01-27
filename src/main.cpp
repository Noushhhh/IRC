/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:01:07 by aandric           #+#    #+#             */
/*   Updated: 2023/01/27 13:50:55 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"


int main(int ac, char **av)
{

	if (ac < 3)
		return 0;
	
	Server Serv(std::atoi(av[1]), std::string(av[2]));

	try
	{
		Serv.setSock(SOCK_STREAM, PROTOCOL);
		Serv.bindSock();
		Serv.listenTo(BACKLOG);
	}
	catch(const Server::ServerException e)
	{
		std::cerr << e.errorMsg() << '\n';
	}
	// while (1)
	// {
		socklen_t addr_size;
		struct sockaddr their_addr;
		addr_size = sizeof(their_addr);
		int new_socket = accept(Serv.getSock(), (struct sockaddr *)&their_addr, &addr_size);
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
