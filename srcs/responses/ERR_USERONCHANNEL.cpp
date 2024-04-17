/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_USERONCHANNEL.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 00:35:36 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/17 00:36:26 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Responses.hpp"

std::string	ERR_NOSUCHNICK(std::string nick, std::string chan, std::string reason)
{
	std::stringstream output;

	output << ":" << PREFIXE;
	output << " 443 " << nick;
	output << " #" << chan << " :";
	output << reason << "\r\n"; 

	return (output.str());
}