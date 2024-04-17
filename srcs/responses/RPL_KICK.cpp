/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL_KICK.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:19:10 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/16 18:19:27 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Responses.hpp"

std::string RPL_KICK(std::string kicker, std::string kicked, std::string channel, std::string reason)
{
    std::stringstream	output;
    
    output << ":" << kicker;
	output << " KICK";
	output << " " << kicked;
	output << " #" << channel;
	output << " :" << reason;
	output << "\r\n";
	return (output.str());
}