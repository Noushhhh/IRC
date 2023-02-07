/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:58:22 by mgolinva          #+#    #+#             */
/*   Updated: 2023/01/27 12:58:22 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
#define USER_HPP

#include "irc.hpp"

class User
{
    public  :
        int         _sockfd;
        sockaddr_in _addr;
        std::string _username;
        std::string _nickname;
        std::string _realname;


    // PASS Check if the passwd is ok if not reject user
    // NICK set nickname for user

    public  :

        User();
        User(int sockfd, sockaddr_in addr);
        User(const User &src);
        ~User();

        User &operator=(const User &src);


};

#endif
