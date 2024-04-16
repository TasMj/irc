/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:15:29 by tmejri            #+#    #+#             */
/*   Updated: 2024/04/16 17:33:20 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"


std::string ERR_CHANOPRIVSNEEDED(std::string nickname, std::string channel, std::string reason)
{
	std::stringstream	output;
    
    output << ":" << PREFIXE;
	output << " 482 #";
	output << " " << nickname;
	output << " #" << channel;
	output << " :" << reason;
	output << "\r\n";
	return (output.str());
}

std::string kickMsg(std::string nickname, std::string channel, std::string reason)
{
    std::stringstream	output;
    
    output << ":" << PREFIXE;
	output << " 40?";
	output << " " << nickname;
	output << " #" << channel;
	output << " :" << reason;
	output << "\r\n";
	return (output.str());
}

std::string RPL_NOTOPIC(std::string nickname, std::string channel, std::string reason)
{
    std::stringstream	output;
    
    output << ":" << PREFIXE;
	output << " 331";
	output << " " << nickname;
	output << " #" << channel;
	output << " :" << reason;
	output << "\r\n";
	return (output.str());
}


std::string	RPL_TOPIC(std::string nickname, std::string channel, std::string topic)
{
	std::stringstream	output;
	(void)nickname;
	output << ":" << PREFIXE;
	output << " 332";
	output << " " << nickname;
	output << " #" << channel;
	output << " :" << topic;
	output << "\r\n";
	return (output.str());
}