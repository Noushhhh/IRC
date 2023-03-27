/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:01:07 by aandric           #+#    #+#             */
/*   Updated: 2023/03/27 14:10:25 by mgolinva         ###   ########.fr       */
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

void	Server::signalHandler(int sig)
{
	_servInstance->freeChans();
	_servInstance->_pollFds.clear();


	std::list< User >::iterator it = _servInstance->getUserList()->begin();
	std::list< User >::iterator end = _servInstance->getUserList()->end();

	while (it != end)
	{
		it->getJoinedChans().clear();
		it ++;
	}
	_servInstance->getUserList()->erase(_servInstance->getUserList()->begin(), _servInstance->getUserList()->end());
	std::exit (sig);
}

int main(int ac, char **av)
{
	if (ac < 3)
		return 0;

	Server Serv(std::atoi(av[1]), std::string(av[2]));

	std::cout << "SIZE OF CHAN " << sizeof(Channel) << std::endl;
	std::cout << "SIZE OF POLLFD " << sizeof(pollfd) << std::endl;
	std::cout << "SIZE OF USER " << sizeof(User) << std::endl;

	std::signal(SIGINT, &Server::signalHandler);
	Serv.init();
	if (!Serv.pollDispatch())
	{
		std::cerr << "an error has occured during server runtime, errno : "
		<< std::strerror(errno) << std::endl;
	}
	return 0;
}
