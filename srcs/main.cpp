/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:18:08 by tmalless          #+#    #+#             */
/*   Updated: 2024/03/11 16:27:12 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"
#include "../includes/Client.hpp"

int main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cout << "Error: invalid input.\nMust be: ./ircserv <port> <password>" << std::endl;
		return (1);
	}

	char			*port = av[1];
	std::string		psw = av[2];
	unsigned int	portDigit = atoi(port);

	/* if (!checkElt(av[0], portDigit, psw))
		return (1); */

	Server *server;
	server = new Server(portDigit, psw);
	if (server->initServer(portDigit) != 0)
		exit(EXIT_FAILURE);
	server->serverLoop();
}
