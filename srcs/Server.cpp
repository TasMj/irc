/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:26:50 by tmalless          #+#    #+#             */
/*   Updated: 2024/03/11 17:27:35 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"


Server::Server(unsigned int port, std::string password) : _port(port), _password(password)
{

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

/* 	this->_epoll_fd = epoll_create1(0);

	if (this->_epoll_fd == -1)
	{
		fprintf(stderr, "Failed to create epoll file descriptor\n");
		return 1;
	}

	event.events = EPOLLIN;
	event.data.fd = 0;
 */
/* 	if (epoll_ctl(this->_epoll_fd, EPOLL_CTL_ADD, 0, &event))
	{
		fprintf(stderr, "Failed to add file descriptor to epoll\n");
		close(this->_epoll_fd);
		return 1;
	} */

	if (listen(this->_sockfd, 10) < 0)
	{
		std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
		return (1);
	}

	auto addrlen = sizeof(sockaddr);
	this->_connection[0] = accept(this->_sockfd, (struct sockaddr *)&this->_sockAddr, (socklen_t *)&addrlen);
	if (this->_connection[0] < 0)
	{
		std::cout << "Failed to grab connection. errno: " << errno << std::endl;
		return (1);
	}
	new_poll.fd = this->_sockfd;
	new_poll.events = POLLIN;
	new_poll.revents = 0;
	this->_polls.push_back(new_poll);
	return (0);
};

void	Server::addNewClient()
{
	Client	cli;

	struct sockaddr_in	cliAdd;
	struct pollfd	new_poll;
	socklen_t	len = sizeof(cliAdd);

	int	receiving_fd = accept(this->_sockfd, (sockaddr *)&(cliAdd), &len);

	fcntl(receiving_fd, F_SETFL, O_NONBLOCK);

	new_poll.fd = receiving_fd;
	new_poll.events = POLLIN;
	new_poll.revents = 0;

	cli.set_fd(receiving_fd);
	cli.set_ip(inet_ntoa(cliAdd.sin_addr));
	this->_clients.push_back(cli);
	this->_polls.push_back(new_poll);

	std::cout << "CLIENT " << receiving_fd << " CONNECTED" << std::endl; 
}

void Server::receiveData(int fd)
{
 char buff[1024]; //-> buffer for the received data
 memset(buff, 0, sizeof(buff)); //-> clear the buffer

 ssize_t bytes = recv(fd, buff, sizeof(buff) - 1 , 0); //-> receive the data

 if(bytes <= 0){ //-> check if the client disconnected
  std::cout << RED << "Client <" << fd << "> Disconnected" << WHI << std::endl;
  //ClearClients(fd); //-> clear the client
  close(fd); //-> close the client socket
 }

 else{ //-> print the received data
  buff[bytes] = '\0';
  std::cout << YEL << "Client <" << fd << "> Data: " << WHI << buff;
  //here you can add your code to process the received data: parse, check, authenticate, handle the command, etc...
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
		//event_count = epoll_wait(this->_epoll_fd, events, MAX_EVENTS, 30000);
		//printf("%d ready events\n", event_count);
		for (i = 0; i < this->_polls.size(); i++)
		{
			if (poll(&this->_polls[0], this->_polls.size(), -1) == -1 && running)
				throw (std::runtime_error("poll() failed"));
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
