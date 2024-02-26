/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:29:36 by tmalless          #+#    #+#             */
/*   Updated: 2024/02/26 12:19:06 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP

# define SERVER_HPP

# include <string>
# include <sys/socket.h>
# include <netinet/in.h>
# include <cstdlib>
# include <iostream>
# include <unistd.h>
# include <string.h>
# include <poll.h>
#include <sys/epoll.h>


#define MAX_EVENTS 5
#define READ_SIZE 10

class Server
{
private:
	unsigned int	_port;
	std::string		_password;
	sockaddr_in		_sockAddr;
	int				_sockfd;
	Server();
	int				_connection;
	struct epoll_event event, events[MAX_EVENTS];
	int 			_epoll_fd;
	
public:
	Server(unsigned int port, std::string password);
	~Server();

	int		initServer(int port);
	int	serverLoop();
};

int	checkElt(std::string serverName, int port, std::string psw);

#endif