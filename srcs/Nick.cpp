/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:55:54 by tmejri            #+#    #+#             */
/*   Updated: 2024/04/12 17:04:40 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

void    recup_nickNamee(Client *cli, std::string buff_str)
{
    
    size_t position = FindInString(buff_str, "NICK"); //obtient la position de la premiere occurence
    if (position != std::string::npos) //si le mot NICK est présent
    {
        std::string nick_data; // recup de NICK jusqu'à \n
        nick_data = buff_str.substr(position + 5, buff_str.size());
        
        size_t end = nick_data.find_first_of("\r\n");
        if (end != std::string::npos)
            nick_data = nick_data.substr(0, end);
        cli->set_nickName(nick_data); //set the nicknqme
    }
}

void    recup_userr(Client *cli, std::string buff_str)
{
    size_t position = FindInString(buff_str, "USER");
    if (position != std::string::npos)
    {
        std::string user_data;
        user_data = buff_str.substr(position + 5, buff_str.size());
        
        size_t end = user_data.find_first_of("\r\n");
        if (end != std::string::npos)
            user_data = user_data.substr(0, end);

        position = FindInString(user_data, ":");
        std::string user_name;
        user_name = user_data.substr(position + 1, user_data.size());
        cli->set_userName(user_name); //set the nicknqme
    }
}
