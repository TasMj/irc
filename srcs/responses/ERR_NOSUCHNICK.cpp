/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_NOSUCHNICK.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 01:08:21 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/17 01:00:16 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Responses.hpp"

std::string	ERR_NOSUCHNICK(std::string nick, std::string target, std::string reason)
{
	std::stringstream output;

	output << ":" << PREFIXE;
	output << " 401 " << nick;
	output << " " << target << " :";
	output << reason << "\r\n"; 

	return (output.str());
}
