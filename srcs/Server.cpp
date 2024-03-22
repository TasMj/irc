/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:26:50 by tmalless          #+#    #+#             */
/*   Updated: 2024/03/22 14:59:41 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

Server::Server(unsigned int port, std::string password) : _port(port), _password(password){

																	   };

int Server::initServer(int port)
{
	struct pollfd new_poll;

	this->_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_sockfd == -1)
	{
		std::cout << "Failed to create socket. errno: " << errno << std::endl;
		return (1);
	}

	this->_sockAddr.sin_family = AF_INET;
	this->_sockAddr.sin_addr.s_addr = INADDR_ANY;
	this->_sockAddr.sin_port = htons(port);
	int reuseAddr = 1;
	if (setsockopt(this->_sockfd, SOL_SOCKET, SO_REUSEADDR, &reuseAddr, sizeof(reuseAddr)) == -1)
	{
		std::cout << "Failed to set SO_REUSEADDR option" << std::endl;
		return (1);
	}

	if (bind(this->_sockfd, (struct sockaddr *)&this->_sockAddr, sizeof(sockaddr)) < 0)
	{
		std::cout << "Failed to bind to port " << port << ". errno: " << errno << std::endl;
		return (1);
	}

	if (listen(this->_sockfd, 10) < 0)
	{
		std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
		return (1);
	}

	auto addrlen = sizeof(sockaddr);
	new_poll.fd = this->_sockfd;
	new_poll.events = POLLIN;
	new_poll.revents = 0;
	this->_polls.push_back(new_poll);
	return (0);
};

void Server::addNewClient()
{
	Client cli;

	struct sockaddr_in cliAdd;
	struct pollfd new_poll;
	socklen_t len = sizeof(cliAdd);
	std::string welcome_msg;

	welcome_msg = ":localhost 001 tmejri :\n\n\n\n\n\n\nWelcome\n\nPlease select a nickname with the command /nick\n\n\n";
	int receiving_fd = accept(this->_sockfd, (sockaddr *)&(cliAdd), &len);

	fcntl(receiving_fd, F_SETFL, O_NONBLOCK);

	new_poll.fd = receiving_fd;
	new_poll.events = POLLIN;
	new_poll.revents = 0;

	cli.set_fd(receiving_fd);
	cli.set_ip(inet_ntoa(cliAdd.sin_addr));
	cli.init_nickName("NickDefault_", cli.get_fd());
	this->_clients.push_back(cli);
	this->_polls.push_back(new_poll);

	send(cli.get_fd(), welcome_msg.c_str(), welcome_msg.size(), 0);
	std::cout << "CLIENT " << receiving_fd << " CONNECTED" << std::endl;

	std::vector<Client>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); ++it)
	{
		std::cout << "fd : " << it->get_fd() << ", Nickname : " << it->get_nickName() << std::endl;
	}
}

void Server::receiveData(int fd)
{
	char buff[1024];
	memset(buff, 0, sizeof(buff));

	ssize_t bytes = recv(fd, buff, sizeof(buff) - 1, 0);

	if (bytes <= 0)
	{
		std::cout << RED << "Client <" << fd << "> Disconnected" << WHI << std::endl;
		// ClearClients(fd); //-> clear the client
		close(fd); //-> close the client socket
	}

	else
	{ //-> print the received data
		buff[bytes] = '\0';

		/*first connection*/
		if (strncmp(buff, "CAP LS", 6) == 0)
		{
			std::cout << BLU << "1st connection" << WHI << std::endl;
		}

		// std::cout << YEL << "Client <" << fd << "> Data: " << WHI << buff;
		std::vector<Client>::iterator it;
		std::string tmp;
		for (it = _clients.begin(); it != _clients.end(); ++it)
		{
			// std::cout << RED << it->get_nickName() << WHI << std::endl;
			if (it->get_fd() == fd)
			{
				tmp = it->get_nickName();
				break;
			}
		}
		// std::cout << RED << tmp << WHI << std::endl;
		std::cout << YEL << tmp << ": " << WHI << buff;
			

		// here you can add your code to process the received data: parse, check, authenticate, handle the command, etc...
		execute_cmd(_clients, fd, buff);
	}
}

int Server::serverLoop()
{
	int running = 1;
	int event_count;
	int i;
	size_t bytes_read;
	char read_buffer[READ_SIZE + 1];

	while (running)
	{
		printf("\nPolling for input...\n");
		// event_count = epoll_wait(this->_epoll_fd, events, MAX_EVENTS, 30000);
		// printf("%d ready events\n", event_count);
		for (i = 0; i < this->_polls.size(); i++)
		{
			if (poll(&this->_polls[0], this->_polls.size(), -1) == -1 && running)
				throw(std::runtime_error("poll() failed"));
			if (this->_polls[i].revents & POLLIN)
			{
				if (this->_polls[i].fd == this->_sockfd)
					this->addNewClient();
				else
					this->receiveData(this->_polls[i].fd);
			}
			/* printf("Reading file descriptor '%d' -- ", events[i].data.fd);
			bytes_read = read(this->_connection[0], read_buffer, READ_SIZE);
			printf("%zd bytes read.\n", bytes_read);
			read_buffer[bytes_read] = '\0';
			printf("Read '%s'\n", read_buffer);

			if (!strncmp(read_buffer, "stop\0", 5))
				running = 0; */
		}
	}
	/* if (close(this->_epoll_fd))
	{
		fprintf(stderr, "Failed to close epoll file descriptor\n");
		return (1);
	} */
	return (0);
}
