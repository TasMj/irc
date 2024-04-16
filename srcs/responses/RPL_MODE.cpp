/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL_MODE.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:06:37 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/15 22:11:20 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Responses.hpp"

std::string	RPL_MODE(std::string nick, std::string chan, std::string sign, std::string flag, std::string reason)
{
	std::stringstream output;

	output << ":" << nick;
	output << " MODE #" << chan;
	output << " " << sign << flag;
	output << " :" << reason << "\r\n";

	return (output.str());
}