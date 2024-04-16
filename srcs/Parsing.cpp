/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:54:11 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/16 17:15:12 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

int	checkName(std::string serverName)
{
	if (strcmp(serverName.c_str(), "./ircserv") != 0)
		return (1);
	return (0);
}

int checkPort(int port)
{
	if (port < 0 || port > 65535)
	{
		std::cout << "Error: invalid port" << std::endl;
		return (1);
	}
	return (0);
}

int checkPsw(std::string psw)
{
	(void)psw;
	return (0);
}
