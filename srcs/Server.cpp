/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:26:50 by tmalless          #+#    #+#             */
/*   Updated: 2024/03/19 15:57:20 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

Channel::~Channel()
{}

Channel::Channel()
{}

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
	// this->_polls[0].fd = accept(this->_sockfd, (struct sockaddr *)&this->_sockAddr, (socklen_t *)&addrlen);
	// if (this->_connection[0] < 0)
	// {
	// 	std::cout << "Failed to grab connection. errno: " << errno << std::endl;
	// 	return (1);s
	// }
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
	std::string	welcome_msg;

	welcome_msg = ":localhost 001 tmejri :\n\n\n\n\n\n\n Welcome \n\n\n\n\n";
	int	receiving_fd = accept(this->_sockfd, (sockaddr *)&(cliAdd), &len);

	fcntl(receiving_fd, F_SETFL, O_NONBLOCK);

	new_poll.fd = receiving_fd;
	new_poll.events = POLLIN;
	new_poll.revents = 0;

	cli.set_fd(receiving_fd);
	cli.set_ip(inet_ntoa(cliAdd.sin_addr));
	this->_clients.push_back(cli);
	this->_polls.push_back(new_poll);

	send(cli.get_fd(), welcome_msg.c_str(), welcome_msg.size(), 0);
	std::cout << "CLIENT " << receiving_fd << " CONNECTED" << std::endl; 
}

bool Channel::hasName(const std::string& nameToCheck) const
{
        	return this->_name == nameToCheck;
}

void	Server::verify_existing_chan_or_creat(char *channelNameStart, int fd)
{
	std::string name(channelNameStart);
    bool channelFound = false;

    // Parcourir chaque Channel dans Chan
    for (std::list<Channel>::iterator it = Chan.begin(); it != Chan.end(); ++it)
	{
        if (it->hasName(name))
		{
            std::cout << "Oui, le channel existe déjà." << std::endl;
            it->fd_in_channel.push_back(fd); // Ajoute le fd au canal existant
            channelFound = true;
            break;
        }
    }

    if (!channelFound)
	{
        // Si le canal n'a pas été trouvé, le créer et l'ajouter à la liste
        Channel newChannel(name);
        newChannel.fd_in_channel.push_back(fd); // Ajoute le fd au nouveau canal
        Chan.push_back(newChannel);
        std::cout << "Un nouveau channel a été créé : " << name << std::endl;
    }
}

std::string Channel::getName() const
{
	return (this->_name);
}

void Server::parcourirTousLesChannels()
{
       std::list<Channel>::const_iterator it;
        for (it = Chan.begin(); it != Chan.end(); ++it)
		{
            std::cout << "Nom du channel : " << it->getName() << std::endl;
			for (std::vector<int>::const_iterator fd_it = it->fd_in_channel.begin(); fd_it != it->fd_in_channel.end(); ++fd_it)
        	{
        	    std::cout << "fd " << *fd_it << " present dans channel: " << it->getName() << std::endl;
        	}
		}
}

int	Server::count_virgule(char *channelNameStart)
{
	int	count = 0;
	for (int i = 0; channelNameStart[i]; i++)
	{
		if (channelNameStart[i] == ',')
			count++;
	}
	return (count);
}

bool	Server::verify_bad_char(char *channelNameStart)
{
	std::string name;
	name = static_cast<std::string>(channelNameStart);
	std::cout << "name: " << name << std::endl;
	if (name.size() > 50)
		return (0);
	std::cout << "LA1" << std::endl;
	if (name[0] != '#')
	{
		return (0);
	}
	std::cout << "LA2" << std::endl;
	std::cout << name.size() << std::endl;
	for (size_t i = 1; i <= name.size() - 3; ++i)
	{
		// std::cout << name[i] << std::endl;
		if ((name[i] >= 97 && name[i] <= 122) || (name[i] >= 65 && name[i] <= 90) || (name[i] >= 48 && name[i] <= 57) || name[i] == 95 || name[i] == 45 || name[i] == 46)
			std::cout << name[i];
		else
			return (0);
	}
	std::cout << "LA3" << std::endl;
	return (1);

}

void	Server::choose_comm(char *buff, int fd)
{
	if (strncmp("NICK", buff, 4) == 0)
		std::cout << "oui nick commande" << std::endl;
	else if(strncmp("JOIN", buff, 4) == 0)
	{

		char *channelNameStart = strstr(buff, "JOIN ");
		channelNameStart = channelNameStart + strlen("JOIN ");
		std::cout << "OUI join commande: " << channelNameStart << std::endl;
        if (channelNameStart != NULL) // Si on trouve le symbole '#' 
        {
            // On pourrait directement utiliser channelNameStart qui contient déjà l'adresse du début du nom du canal.
            std::cout << "Channel: " << channelNameStart << std::endl;
			if (verify_bad_char(channelNameStart) == 1)
				verify_existing_chan_or_creat(channelNameStart, fd);
			else
				std::cout << "bad indentation of join parameters command!" << std::endl;
        }
		// else if (channelNameStart != NULL && strchr(channelNameStart, ','))// plusieurs channels
		// {
			// int nb_of_chan = count_virgule(channelNameStart) + 1;
			// const char* start = channelNameStart;
			// for (int i = 0; i < nb_of_chan; ++i)
			// {
    			// const char* end = strchr(start, ',');
    			// if (!end) end = start + strlen(start); // Si pas de ',', pointer vers la fin de la chaîne
// 
    			// int len = end - start;
    			// char* tmp = new char[len + 1]; // +1 pour '\0'
    			// strncpy(tmp, start, len);
    			// tmp[len] = '\0';
				// verify_existing_chan_or_creat(tmp, fd);
// 
    			// std::cout << "tmp: " << tmp << std::endl;
// 
    			// delete[] tmp; // Ne pas oublier de libérer la mémoire
// 
    			// start = end + 1; // Passer au prochain nom de canal
			// }
		// }
        else
        {
            std::cout << "Commande JOIN mal formée, aucun canal spécifié." << std::endl;
        }
	}
	else
		std::cout << "non" << std::endl;
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
	/***********COMMANDE**************/
	choose_comm(buff, fd);
	parcourirTousLesChannels();	

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
