/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:15:29 by tmejri            #+#    #+#             */
/*   Updated: 2024/04/15 23:30:43 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

std::string	ERR_NOSUCHCHANNEL(std::string nickname, std::string channel, std::string reason)
{
	std::stringstream	output;

	output << ":" << PREFIXE;
	output << " 403 ";
	output << " " << nickname;
	output << " #" << channel;
	output << " :" << reason;
	output << "\r\n";
	return (output.str());
}

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

std::string ERR_NOTONCHANNEL(std::string nickname, std::string channel, std::string reason)
{
	std::stringstream	output;
    
    output << ":" << PREFIXE;
	output << " 442 #";
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

std::string ERR_NEEDMOREPARAMS(std::string channel, std::string cmd, std::string reason)
{
    std::stringstream	output;

	(void)channel;
	output << ":" << PREFIXE;
	output << " 461";
	if (channel.size())
		output << " #" << channel;
	output << " " << cmd;
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