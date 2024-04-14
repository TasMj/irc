/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:15:29 by tmejri            #+#    #+#             */
/*   Updated: 2024/04/14 18:59:38 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

std::string	errChannel(std::string nickname, std::string channel, std::string reason)
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

std::string errOperator(std::string nickname, std::string channel, std::string reason)
{
	std::stringstream	output;
    
    output << ":" << PREFIXE;
	output << " 40? ";
	output << " " << nickname;
	output << " #" << channel;
	output << " :" << reason;
	output << "\r\n";
	return (output.str());
}

std::string errClient(std::string nickname, std::string channel, std::string reason)
{
	std::stringstream	output;
    
    output << ":" << PREFIXE;
	output << " 40? ";
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
	output << " 40? ";
	output << " " << nickname;
	output << " #" << channel;
	output << " :" << reason;
	output << "\r\n";
	return (output.str());
}
