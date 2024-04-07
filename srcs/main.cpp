/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:18:08 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/07 21:36:19 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"
#include "../includes/Client.hpp"

bool g_isRunning = false;

void	signalHandler(int sig)
{
	std::cout << INTERCEPT << std::endl << "Terminating signal intercepted : " << sig << "." << std::endl;
	g_isRunning = false;
}

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
	std::cout << BLU << server->getPwd() << WHI << std::endl;
	signal(SIGINT, signalHandler);
	if (server->initServer(portDigit) != 0)
		exit(EXIT_FAILURE);
	server->serverLoop();
}
