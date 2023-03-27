/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:01:07 by aandric           #+#    #+#             */
/*   Updated: 2023/03/27 16:46:32 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

// void	freeChans

void	Server::freeChans()
{
	std::list< Channel >::iterator it = _channelsList.begin();
	std::list< Channel >::iterator end = _channelsList.end();

	// Channel *ptr;

	while (it != end)
	{
		it->getUsersList().clear();
		it->getOpList().clear();
		it->getBanList().clear();
		it->getMutedList().clear();
		it ++;
	};
	_channelsList.clear();
	// _servInstance->getChanList()->erase(_servInstance->getChanList()->begin(),_servInstance->getChanList()->end());
}

void	Server::freeUsers()
{
	std::list< User >::iterator it = _usersList.begin();
	std::list< User >::iterator end = _usersList.end();

	while (it != end)
	{
		it->getJoinedChans().clear();
		it ++;
	}
	_usersList.clear();
}

void print(pollfd obj)
{
	std::cout << obj.fd <<std::endl;
}

void	Server::serverShutdown()
{
	freeChans();
	freeUsers();
	_pollFds.clear();
}

void	Server::signalHandler(int sig)
{
	_servInstance->serverShutdown();
	std::exit (sig);
}

int main(int ac, char **av)
{
	if (ac < 3)
		return 0;

	Server Serv(std::atoi(av[1]), std::string(av[2]));

	std::signal(SIGINT, &Server::signalHandler);
	Serv.init();
	if (!Serv.pollDispatch())
	{
		std::cerr << "an error has occured during server runtime, errno : "
		<< std::strerror(errno) << std::endl;
	}
	return 0;
}
