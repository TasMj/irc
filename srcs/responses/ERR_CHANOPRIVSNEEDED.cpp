/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_CHANOPRIVSNEEDED.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:41:30 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/16 19:22:29 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Responses.hpp"

std::string	ERR_CHANOPRIVSNEEDED(std::string nick, std::string chan)
{
	std::stringstream output;

	output << ":" << PREFIXE;
	output << " 482 #" << chan;
	output << " " << nick << " :";
	output << "You need to be an operator on this channel." << "\r\n"; 

	return (output.str());
}