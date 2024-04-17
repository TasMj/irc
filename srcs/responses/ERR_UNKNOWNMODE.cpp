/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_UNKNOWNMODE.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 00:49:05 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/17 00:51:55 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Responses.hpp"

std::string	ERR_UNKNOWNMODE(std::string nick, std::string chan)
{
	std::stringstream output;

	output << ":" << PREFIXE;
	output << " 472 " << nick;
	output << " #" << chan << " :";
	output << "Invalid Flag(s) ([+|-]i|t|k|o|l)." << "\r\n"; 

	return (output.str());
}