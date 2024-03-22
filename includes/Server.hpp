/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:29:36 by tmalless          #+#    #+#             */
/*   Updated: 2024/03/22 19:04:34 by tas              ###   ########.fr       */
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
# include <map>

#define RED "\e[1;31m" //-> for red color
#define WHI "\e[0;37m" //-> for white color
#define GRE "\e[1;32m" //-> for green color
#define YEL "\e[1;33m" //-> for yellow color
#define BLU "\e[0;34m"
#define PUR "\e[0;35m"
#define CYA "\e[0;36m"

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
		// std::map<int, std::string>	_clients;
		std::vector<pollfd>			_polls;
		
		Server();
		
	public:
		Server(unsigned int port, std::string password);
		~Server();
	
		int		initServer(int port);
		int		serverLoop();
		void	addNewClient();
		void	receiveData(int fd);

		// std::string get_username(std::vector<Client> _clients, char *buff);
		
};

int	checkElt(std::string serverName, int port, std::string psw);

/**************/
void	execute_cmd(std::vector<Client>& _clients, int fd, std::string buff);
void	recup_data(std::vector<Client>& _clients, char *buff);




#endif