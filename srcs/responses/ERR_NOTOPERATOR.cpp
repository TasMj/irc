/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_NOTOPERATOR.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 01:07:29 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/17 01:08:58 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Responses.hpp"

std::string	ERR_NOTOPERATOR(std::string nick, std::string target)
{
	std::stringstream output;

	output << ":" << PREFIXE;
	output << " 482 " << nick;
	output << " " << target << " :";
	output << "You're not an operator on the channel." << "\r\n"; 

	return (output.str());
}