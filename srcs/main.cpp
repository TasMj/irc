/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:18:08 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/16 17:15:08 by aclement         ###   ########.fr       */
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
		std::cout << RED << "Error: invalid input.\nMust be: ./ircserv <port> <password>" << WHI << std::endl;
		return (1);
	}

	char			*port = av[1];
	std::string		psw = av[2];
	unsigned int	portDigit = atoi(port);
		
	Server *server = new Server(psw);
	
	signal(SIGINT, signalHandler);
	if (server->initServer(portDigit) != 0) {
		std::cout << RED << "Error" << WHI << std::endl;
		exit(EXIT_FAILURE);
	}
	server->serverLoop();
}
