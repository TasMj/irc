/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:29:36 by tmalless          #+#    #+#             */
/*   Updated: 2024/03/19 15:57:52 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP

# define SERVER_HPP

# include <string>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <cstdlib>
# include <iostream>
# include <unistd.h>
# include <string.h>
#include <fcntl.h>
# include <poll.h>
# include <sys/epoll.h>
# include <vector>

#define RED "\e[1;31m" //-> for red color
#define WHI "\e[0;37m" //-> for white color
#define GRE "\e[1;32m" //-> for green color
#define YEL "\e[1;33m" //-> for yellow color

# include "Client.hpp"


#define MAX_EVENTS 5
#define READ_SIZE 10

class Server
{
private:
	unsigned int				_port;
	std::string					_password;
	sockaddr_in					_sockAddr;
	int							_sockfd;
	int							_connection[5];
	struct pollfd				_poll;
	int 						_epoll_fd;
	std::vector<Client>			_clients;
	std::vector<pollfd>			_polls;
	
	Server();
	
public:
	Server(unsigned int port, std::string password);
	~Server();

	int		initServer(int port);
	int		serverLoop();
	void	addNewClient();
	void	receiveData(int fd);
};

int	checkElt(std::string serverName, int port, std::string psw);

#endif