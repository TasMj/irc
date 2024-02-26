/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:26:50 by tmalless          #+#    #+#             */
/*   Updated: 2024/02/26 16:21:19 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

Server::Server(unsigned int port, std::string password) : _port(port), _password(password)
{

};

int Server::initServer(int port)
{
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

	this->_epoll_fd = epoll_create1(0);

	if (this->_epoll_fd == -1)
	{
		fprintf(stderr, "Failed to create epoll file descriptor\n");
		return 1;
	}

	event.events = EPOLLIN;
	event.data.fd = 0;

	if (epoll_ctl(this->_epoll_fd, EPOLL_CTL_ADD, 0, &event))
	{
		fprintf(stderr, "Failed to add file descriptor to epoll\n");
		close(this->_epoll_fd);
		return 1;
	}

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
	return (0);
};

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
		event_count = epoll_wait(this->_epoll_fd, events, MAX_EVENTS, 30000);
		printf("%d ready events\n", event_count);
		for (i = 0; i < event_count; i++)
		{
			printf("Reading file descriptor '%d' -- ", events[i].data.fd);
			bytes_read = read(this->_connection[0], read_buffer, READ_SIZE);
			printf("%zd bytes read.\n", bytes_read);
			read_buffer[bytes_read] = '\0';
			printf("Read '%s'\n", read_buffer);

			if (!strncmp(read_buffer, "stop\0", 5))
				running = 0;
		}
	}
	if (close(this->_epoll_fd))
	{
		fprintf(stderr, "Failed to close epoll file descriptor\n");
		return (1);
	}
	return (0);
}
