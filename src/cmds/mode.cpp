/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:01 by mgolinva          #+#    #+#             */
/*   Updated: 2023/02/14 16:34:43 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

bool	Server::Mode(User &user, Message &message)
{
    std::cout << "SAUCISSE" << std::endl;
    (void) user;
    (void) message;
    return (true);
}
