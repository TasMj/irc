/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_NICKNAMEINUSE.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:24:24 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/17 00:59:55 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Responses.hpp"

std::string	ERR_NICKNAMEINUSE(std::string oldNick, std::string newNick, std::string reason)
{
	(void)reason;
	std::stringstream output;

	output << ":" << PREFIXE;
	output << " 433 " << (oldNick.empty() ? "*" : oldNick);
	output << " " << newNick << " :"<< "This nickname is already in use." << "\r\n"; 

	return (output.str());
}	