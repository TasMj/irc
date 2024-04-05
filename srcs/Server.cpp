/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:26:50 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/05 18:58:46 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"
#include "../includes/Transmission.hpp"

Server::Server(unsigned int port, std::string password) : _port(port), _password(password)
{
	std::cout << RED << std::endl << std::endl << password << std::endl << std::endl << WHI;
};

Server::~Server()
{
	std::cout << "The server has been shutdown." << std::endl;
};

std::string Server::getPwd()
{
	return(this->_password);
}

std::vector<pollfd> Server::getPollfds()
{
	return(this->_polls);
}

std::vector<Client> Server::getClient()
{
	return(this->_clients);
}

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

	new_poll.fd = this->_sockfd;
	new_poll.events = POLLIN;
	new_poll.revents = 0;
	this->_polls.push_back(new_poll);
	return (0);
};

#include <cstdio>
void Server::addNewClient()
{
	Client cli;

	struct sockaddr_in cliAdd;
	struct pollfd new_poll;
	socklen_t len = sizeof(cliAdd);

	int receiving_fd = accept(this->_sockfd, (sockaddr *)&(cliAdd), &len);
	fcntl(receiving_fd, F_SETFL, O_NONBLOCK);

	new_poll.fd = receiving_fd;
	new_poll.events = POLLIN;
	new_poll.revents = 0;

	cli.set_fd(receiving_fd);
	cli.set_ip(inet_ntoa(cliAdd.sin_addr));
	cli.set_Server(this);
	this->_clients.push_back(cli);
	this->_polls.push_back(new_poll);
	
	std::cout << "CLIENT " << receiving_fd << " CONNECTED" << std::endl;

	std::vector<Client>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); ++it)
	{
		std::cout << "fd : " << it->get_fd() << ", Nickname : " << it->get_nickName() << std::endl;
	}
	
	if (receiveFirstData(&cli))
	{
		std::string welcome_msg;
		welcome_msg = ":localhost 001 " + cli.get_nickName() + " :\n\n\n\n\n\n\nWelcome\n\n\n\n\n";
		// std::cout << RED << "welcome msg :" <<std::endl << std::endl << cli.get_nickName() <<std::endl << std::endl << WHI;
		// handleMsg(&cli, welcome_msg);
		handleFirstMsg(&cli, welcome_msg);
		// send(cli.get_fd(), welcome_msg.c_str(), welcome_msg.size(), 0);		
	}

}

void	Server::handleFirstMsg(Client *cli, std::string msg)
{
	Transmission newTrans;

	newTrans.setMsg(msg);
	newTrans.setFdHost(cli->get_fd());
	_transmission.push_back(newTrans);

	setPollStatus(POLLOUT);
	
}



void	Server::handleMsg(Client *cli, std::string msg)
{
	Transmission newTrans;

	newTrans.setMsg(msg);
	newTrans.setFdHost(cli->get_fd());
	_transmission.push_back(newTrans);

	// setPollStatus(POLLOUT);
}

std::deque<std::string>	split(std::string str, std::string separator)
{
	std::deque<std::string> cmd;
	std::string a;
	
	size_t pos = 0;
	while ((pos = str.find(separator)) != std::string::npos)
	{
		a = str.substr(0, pos);
		std::cout << "ici : " << a << std::endl;
		pos += separator.length();
		str.erase(0, pos);
		cmd.push_back(a);
	}
	return(cmd);
}

int Server::receiveFirstData(Client *cli)
{
	char buff[1024];
	memset(buff, 0, sizeof(buff));

	ssize_t bytes = recv(cli->get_fd(), buff, sizeof(buff) - 1, 0);

	if (bytes <= 0)
	{
		std::cout << RED << "Client <" << cli->get_fd() << "> Disconnected" << WHI << std::endl;
		close(cli->get_fd()); //-> close the client socket
	}
	else
	{
		bool is_pwd = false;
		buff[bytes + 1] = '\0';
		std::deque<std::string> cmds = split(buff, "\n");
		std::cout << cmds.size() << std::endl;
		for (size_t i = 0; i < cmds.size(); i++)
		{
			std::cout << PUR << "COUCOU : " << WHI << cmds.at(i) << std::endl;
			if (strncmp("PASS ", cmds.at(i).c_str(), 5) == 0)
				is_pwd = true;
		}
		recup_dataa(cli, cmds);
		if (!is_pwd)
		{
			std::string error_msg;
			std::string miss_pw = "You need a password to connect.\n";
			error_msg = ":localhost DISCONECT localhost: \n" + miss_pw;
			handleMsg(cli, error_msg);
			// send(cli->get_fd(), error_msg.c_str(), error_msg.size(), 0);	
			return (0);
		}
	}
	return (1);
}

void Server::receiveData(int fd)
{
	char buff[1024];
	memset(buff, 0, sizeof(buff));

	ssize_t bytes = recv(fd, buff, sizeof(buff) - 1, 0);

	if (bytes <= 0)
	{
		std::cout << RED << "Client <" << fd << "> Disconnected" << WHI << std::endl;
		close(fd); //-> close the client socket
	}

	else
	{
		buff[bytes] = '\0';

		std::vector<Client>::iterator it;
		Client tmp;
		for (it = _clients.begin(); it != _clients.end(); ++it)
		{
			if (it->get_fd() == fd)
			{
				tmp = *it;
				break;
			}
		}
		handleMsg(&tmp, buff);
	}
}

void Server::cleanServer()
{
	std::vector<pollfd>::iterator it;

	for (it = this->_polls.begin(); it != this->_polls.end(); it++)
	{
		close(it->fd);
	}
	delete this;
}

void	Server::setPollStatus(unsigned int status)
{
	this->_pollStatus = status;
}

void	Server::exec_transmission(std::vector<Transmission> transmission)
{
	std::vector<Transmission>::iterator it;
	
	for (it = transmission.begin(); it != transmission.end(); ++it)
		execute_cmd(_clients , it->getFdHost(), it->getMsg());
	setPollStatus(POLLIN);
	transmission.clear();
}


int Server::serverLoop()
{
	g_isRunning = true;
	size_t 			i;
	setPollStatus(POLLIN);
	int flag = 0;

	while (g_isRunning)
	{
		std::cout << "\nPolling for input...\n" << std::endl;
		for (i = 0; i < this->_polls.size(); i++)
		{
			if (poll(&this->_polls[0], this->_polls.size(), -1) == -1 && g_isRunning)
				throw(std::runtime_error("poll() failed"));

			if (_pollStatus == POLLIN)
			{
				if (this->_polls[i].revents & POLLIN)
				{
					if (this->_polls[i].fd == this->_sockfd)
					{
						std::cout << GRE << ":::" << WHI << std::endl;
						this->addNewClient();
						flag = 1;
					}
					else
					{
						std::cout << GRE << "..." << WHI << std::endl;	
						this->receiveData(this->_polls[i].fd);
						flag++;
					}
				}
			}
			if (_pollStatus == POLLOUT && flag == 1)
			{
				std::cout << GRE << "]]]" << WHI << std::endl;
				exec_transmission(_transmission);
			}
		}
		if (_pollStatus == POLLOUT)
			{
				std::cout << GRE << "]]]" << WHI << std::endl;
				exec_transmission(_transmission);
			}
	}
	this->cleanServer();
	return (0);
}
