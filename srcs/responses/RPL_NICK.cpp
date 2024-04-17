/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL_NICK.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 22:50:14 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/17 05:25:10 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Responses.hpp"

std::string	RPL_NICK(Client *cli, std::string newNick)
{
	std::stringstream output;

	output << ":" << newNick;
	//output << "!" << cli->get_userName();
	//output << "@" << PREFIXE ;
	output << " NICK " << cli->get_nickName()  << "\r\n";

	return (output.str());
}