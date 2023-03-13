/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:27:34 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/13 15:12:57 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

std::string *cppsplit(std::string str, char sep)
{
    int         wordCT = 1;
    int         strSize = str.size();
    std::string *strArray;
    
    for (int i = 0; i < strSize; i ++)
    {
        if (str[i] == sep && i != strSize - 1 && i != 0)
        {
            wordCT ++;
            i ++;
        } 
        while (str[i] && str[i] == sep)// turn into a while and uncomment condition for real split
            i ++;
    }
    strArray = new std::string[wordCT + 1];

    int i = 0;
    int j = 0;

    while (i < wordCT)
    {
        while (str[j] == sep) // if you raise it above the while and turn it into a while it will give you a real split without empty strings
            j ++;
        while(str[j] && str[j] != sep)
        {
            strArray[i].push_back(str[j]);
            j ++;
        }
        // strArray[i].push_back('\0');
        i ++;
    }
    strArray[i].push_back('\0');
    return (strArray);
}

bool    isCharset(char c, std::string charset)
{
    ssize_t charset_size = charset.size();
    for (ssize_t i = 0; i < charset_size; i ++)
    {
        if (c == charset [i])
            return (true);
    }
    return (false);
}

size_t ft_arraySize(std::string *array)
{
    size_t i = 0;
    while (array[i].size() != 0)
        i ++;
    return (i);
}

std::string get_suffix(std::string *arguments)
{
    size_t i = 0;
    std::string full_argument = "";
    while (!arguments[i].empty())
    {
        full_argument = full_argument + arguments[i];
        if (i != arguments[i].size())
            full_argument = full_argument + " ";
        i++;
    }
    return (full_argument);
}

void    reply(User &user, std::string reply)
{
    send (user.getSockfd(), reply.c_str(), reply.length(), 0);
}