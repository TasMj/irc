/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL_JOIN.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:30:45 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/15 21:10:53 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Responses.hpp"

std::string	RPL_JOIN(Client *cli, std::string chan)
{
	std::stringstream output;

	output << ":" << cli->get_nickName();
	output << "!" << cli->get_userName();
	output << "@" << PREFIXE ;
	output << " JOIN #" << chan << "\r\n";

	return (output.str());
}