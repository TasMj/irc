/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_PASSWDMISMATCH.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 01:25:50 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/17 01:53:01 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Responses.hpp"

std::string	ERR_PASSWDMISMATCH(std::string nick, std::string pwd)
{
	std::stringstream output;

	output << ":" << PREFIXE;
	output << " 464 " << nick;
	output << " :" << pwd;
	output << " incorrect." << "\r\n"; 

	return (output.str());
}