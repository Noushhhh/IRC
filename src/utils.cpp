/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:27:34 by mgolinva          #+#    #+#             */
/*   Updated: 2023/03/29 13:48:04 by mgolinva         ###   ########.fr       */
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
        while (str[i] && str[i] == sep)
            i ++;
    }
    strArray = new std::string[wordCT + 1];

    int i = 0;
    int j = 0;

    while (i < wordCT)
    {
        while (str[j] == sep)
            j ++;
        while(str[j] && str[j] != sep)
        {
            strArray[i].push_back(str[j]);
            j ++;
        }
        i ++;
    }
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
    while (!array[i].empty())
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
        full_argument = full_argument + " ";
        i++;
    }
    return (full_argument);
}

void    reply(User &user, std::string reply)
{
    (void)user;
    send (user.getSockfd(), reply.c_str(), reply.length(), 0);
    std::cout << "message sent : " << reply;
}

std::vector<std::string>    split_cmd(std::string cmd)
{
    std::vector <std::string> cmd_array;
	char *string_to_split = new char[cmd.length()+1];
	std::strcpy(string_to_split, cmd.c_str());
	char *token = strtok(string_to_split, "\r\n");
	while(token != NULL)
	{
		cmd_array.push_back(token);
		token = strtok(NULL, "\r\n");
	}
	delete[] string_to_split;
	return cmd_array ;
}

