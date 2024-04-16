/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL_INVITE.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:55:18 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/16 15:24:04 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Responses.hpp"

std::string	RPL_INVITE(std::string sender, std::string receiver, std::string chan)
{
	std::stringstream output;

	output << ":" << PREFIXE;
	output << " 341 " << sender;
	output << " " << receiver << " #";
	output << chan << "\r\n";

	return (output.str());
}