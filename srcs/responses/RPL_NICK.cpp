/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL_NICK.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 22:50:14 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/15 23:13:15 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Responses.hpp"

std::string	RPL_NICK(Client *cli, std::string newNick)
{
	std::stringstream output;

	output << ":" << cli->get_nickName();
	output << "!" << cli->get_userName();
	output << "@" << PREFIXE ;
	output << " NICK :" << newNick << "\r\n";

	return (output.str());
}