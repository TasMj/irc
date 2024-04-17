/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_NOSUCHCHANNEL.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 01:08:17 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/17 01:00:11 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Responses.hpp"

std::string	ERR_NOSUCHCHANNEL(std::string nick, std::string chan, std::string reason)
{
	std::stringstream output;

	output << ":" << PREFIXE;
	output << " 403 " << nick;
	output << " #" << chan << " :";
	output << reason << "\r\n"; 

	return (output.str());
}