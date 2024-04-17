/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL_NOTOPIC.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:24:25 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/16 18:24:51 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Responses.hpp"

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