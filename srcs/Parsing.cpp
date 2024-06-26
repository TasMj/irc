/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:54:11 by tmalless          #+#    #+#             */
/*   Updated: 2024/03/28 13:50:14 by tmalless         ###   ########.fr       */
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

int	checkElt(std::string serverName, int port, std::string psw)
{
	(void)psw;
	if (!checkName(serverName))
		return (1);
	if (!checkPort(port))
		return (1);
	// if (!checkPsw(psw))
		// return (1);
	return (0);
}
