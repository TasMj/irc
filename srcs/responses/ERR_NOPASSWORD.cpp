/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_NOPASSWORD.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 01:15:15 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/17 01:16:50 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Responses.hpp"

std::string	ERR_NOPASSWORD(std::string nick, std::string chan)
{
	std::stringstream output;

	output << ":" << PREFIXE;
	output << " 475 " << nick;
	output << " #" << chan << " :";
	output << "Cannot unset channel password - no password set" << "\r\n"; 

	return (output.str());
}