/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL_TOPIC.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:24:21 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/16 18:25:15 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Responses.hpp"

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