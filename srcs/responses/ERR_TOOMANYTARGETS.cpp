/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_TOOMANYTARGETS.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 02:26:17 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/17 02:30:15 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Responses.hpp"

std::string	ERR_TOOMANYTARGETS(std::string nick, std::string command)
{
	std::stringstream output;

	output << ":" << PREFIXE;
	output << " 407 " << nick;
	output << " " << command << " :"<< "Too many targets." << "\r\n"; 

	return (output.str());
}	