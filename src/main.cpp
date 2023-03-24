/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:01:07 by aandric           #+#    #+#             */
/*   Updated: 2023/03/24 11:31:34 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

void	Server::signalHandler(int sig)
{
	std::list< Channel >::iterator it = _servInstance->getChanList()->begin();
	std::list< Channel >::iterator end = _servInstance->getChanList()->end();
	std::list< Channel >::iterator buff;

	while (it != end)
	{
		buff = it;
		it ++;
		_servInstance->getChanList()->erase(buff);
	}
	std::exit (sig);
}

int main(int ac, char **av)
{
	if (ac < 3)
		return 0;

	Server Serv(std::atoi(av[1]), std::string(av[2]));
	Serv.init();
	std::signal(SIGINT, &Server::signalHandler);
	if (!Serv.pollDispatch())
	{
		std::cerr << "an error has occured during server runtime, errno : "
		<< std::strerror(errno) << std::endl;
	}
	return 0;
}
