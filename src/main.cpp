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
	Serv.init();

	while (1)
	{
		Serv.pollDispatch();
	}

	return 0;
}
