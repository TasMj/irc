/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL_WELCOME.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:43:23 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/15 17:57:04 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Responses.hpp"

std::string	RPL_WELCOME(Client *cli)
{
	std::stringstream output;

	output << ":" << PREFIXE;
	output << " 001 " << cli->get_nickName();
	output << " : \n" << WELCOME << "Bienvenue sur ";
	output << SERVER << " " << cli->get_nickName();
	output << "!" << cli->get_userName();
	output << "@" << PREFIXE << "\r\n"; 

	return (output.str());
}	