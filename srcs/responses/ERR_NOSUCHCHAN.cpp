/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_NOSUCHCHAN.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 01:08:17 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/16 01:12:53 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Responses.hpp"

std::string	ERR_NOSUCHNICK(std::string nick, std::string target, std::string reason)
{
	std::stringstream output;

	output << ":" << PREFIXE;
	output << " 403 " << nick;
	output << " " << target << " :";
	output << reason << "\r\n"; 

	return (output.str());
}