/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Msg.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:07:43 by tmejri            #+#    #+#             */
/*   Updated: 2024/03/25 15:08:03 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

std::string recup_nick_msg(std::string buff)
{
    std::string nick = buff.substr(8, buff.size());
        
    size_t end = nick.find_first_of(" ");
    if (end != std::string::npos)
        nick = nick.substr(0, end);
    return (nick);
}

std::string recup_msg(std::string buff, int start)
{
    std::string tmp;
    size_t end = buff.find_first_of("\r\n");
    std::cout << PUR << "start: " << start << " end: " << end << WHI << std::endl;
    if (end != std::string::npos)
        tmp = buff.substr(0, end);
    std::string msg;
    msg = tmp.substr(start, tmp.length());
    return (msg);
}
