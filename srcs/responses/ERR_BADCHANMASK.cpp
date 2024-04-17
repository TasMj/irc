/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_BADCHANMASK.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:40:39 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/16 19:22:11 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Responses.hpp"

std::string	ERR_BADCHANMASK(std::string nick, std::string chan)
{
	std::stringstream output;

	output << ":" << PREFIXE;
	output << " 476 " << nick;
	output << " #" << chan << " :"<< "Invalid chan mask" << "\r\n"; 

	return (output.str());
}	