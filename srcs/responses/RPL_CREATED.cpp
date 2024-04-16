/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL_CREATED.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:09:48 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/15 14:14:58 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Responses.hpp"

std::string	RPL_CREATED()
{
	std::stringstream output;

	output << ":" << PREFIXE;
	output << " 003 ";
	output << ": The server was created on ";
	output << CREATION << ".\r\n" ;

	return (output.str());
}	