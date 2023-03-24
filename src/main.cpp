/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:01:07 by aandric           #+#    #+#             */
/*   Updated: 2023/03/24 15:28:14 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

// void	freeChans

void	Server::freeChans()
{
	std::list< Channel >::iterator it = _servInstance->getChanList()->begin();
	std::list< Channel >::iterator end = _servInstance->getChanList()->end();

	while (it != end)
	{
		std::cout << it->getName() << " was deleted" << std::endl;
		it->getBanList().erase(it->getBanList().begin(), it->getBanList().end());
		it->getOpList().erase(it->getOpList().begin(), it->getOpList().end());
		it->getMutedList().erase(it->getMutedList().begin(), it->getMutedList().end());
		it ++;
	}
	_servInstance->getChanList()->erase(_servInstance->getChanList()->begin(),_servInstance->getChanList()->end());
}

void	Server::signalHandler(int sig)
{

	std::cout << "SIG HANDLE\n";
	std::cout << "SIG HANDLE\n";
	std::cout << "SIG HANDLE\n";
	std::cout << "SIG HANDLE\n";
	_servInstance->freeChans();
	_servInstance->_pollFds.erase(_servInstance->_pollFds.begin(), _servInstance->_pollFds.end());

	{
		std::list< User >::iterator it = _servInstance->getUserList()->begin();
		std::list< User >::iterator end = _servInstance->getUserList()->end();

		while (it != end)
		{
			it->freeJoinedChans();
			it ++;
		}
		_servInstance->getUserList()->erase(_servInstance->getUserList()->begin(), _servInstance->getUserList()->end());
	}
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
