/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_NOTONCHANNEL.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:59:30 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/17 00:35:55 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Responses.hpp"

std::string	ERR_NOTONCHANNEL(std::string nick, std::string chan, std::string reason)
{
	std::stringstream output;

	output << ":" << PREFIXE;
	output << " 442 " << nick;
	output << " #" << chan << " :";
	output << reason << "\r\n"; 

	return (output.str());
}