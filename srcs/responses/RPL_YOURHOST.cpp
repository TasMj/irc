/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL_YOURHOST.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:06:08 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/15 14:10:31 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Responses.hpp"

std::string	RPL_YOURHOST()
{
	std::stringstream output;

	output << ":" << PREFIXE;
	output << " 002 ";
	output << ": Your host is ";
	output << SERVER << ", running on ";
	output << VERSION << "\r\n";

	return (output.str());
}	