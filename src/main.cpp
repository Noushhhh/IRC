/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:01:07 by aandric           #+#    #+#             */
/*   Updated: 2023/01/27 16:53:08 by mgolinva         ###   ########.fr       */
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
		std::cout <<"test" <<std::endl;
	}
	catch(const Server::ServerException &e)
	{
		std::cerr << e.errorMsg() << '\n';
		return (1);
	}

	int new_socket;
	socklen_t addr_size;
	struct sockaddr their_addr;

	while (1)
	{
		addr_size = sizeof(their_addr);
		new_socket = accept(Serv.getSock(), (struct sockaddr *)&their_addr, &addr_size);
		if (new_socket > 0)
		{
			if (!Serv.addUser(new_socket))
				return 0; // msg User couldnt be added
		}
		else if (new_socket < 0)
		{
			std::cout << "error: accept: " << std::strerror(errno) << std::endl;
		}
		std::cout << "new_sock = " << new_socket << std::endl;
		Serv.pollDispatch();
		// char buff[250];
		// while (recv(new_socket, buff, sizeof(buff), 0) > 0) // use poll 
		// {
		// 	std::cout << buff;
		// 	memset(buff, 0, 250);
		// }
	}
	return 0;
}
