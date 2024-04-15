/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_CHANPRIVSNEEDED.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:41:30 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/15 23:43:54 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Responses.hpp"

std::string	ERR_CHANPRIVSNEEDED(std::string nick, std::string chan)
{
	std::stringstream output;

	output << ":" << PREFIXE;
	output << " 482 #" << chan;
	output << " " << nick << " :";
	output << "You need to be an operator on this channel." << "\r\n"; 

	return (output.str());
}