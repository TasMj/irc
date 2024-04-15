/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL_MYINFO.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:11:30 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/15 14:14:33 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Responses.hpp"

std::string	RPL_MYINFO()
{
	std::stringstream output;

	output << ":" << PREFIXE;
	output << " 004 ";
	output << ":";
	output << SERVER << " ";
	output << VERSION << " o itlk\r\n";

	return (output.str());
}	