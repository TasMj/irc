/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_ISOPERATOR.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 00:59:42 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/17 01:03:59 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Responses.hpp"

std::string	ERR_ISOPERATOR(std::string nick, std::string target)
{
	std::stringstream output;

	output << ":" << PREFIXE;
	output << " 491 " << nick;
	output << " :" << target << "is already an operator." << "\r\n"; 

	return (output.str());
}	