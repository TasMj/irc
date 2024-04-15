/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_NEEDMOREPARAMS.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:03:43 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/15 18:28:37 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Responses.hpp"

std::string	ERR_NEEDMOREPARAMS(std::string nick, std::string cmd, std::string reason)
{
	std::stringstream output;

	output << ":" << PREFIXE;
	output << " 461 " << nick;
	output << " " << cmd << " :";
	output << reason << "\r\n"; 

	return (output.str());
}