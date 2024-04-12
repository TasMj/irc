/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:26:50 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/12 16:30:20 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server()
{

}

Server::Server(std::string password)
	: _password(password)
	, _prefixServer(":localhost")
{
	_cmd_list["NICK"]		= &Server::cmd_nick;
	_cmd_list["USER"]		= &Server::cmd_user;
	_cmd_list["PRIVMSG"]	= &Server::cmd_privmsg;
	_cmd_list["PING"]		= &Server::cmd_ping;
	_cmd_list["PASS"]		= &Server::cmd_pass;
	_cmd_list["QUIT"]		= &Server::cmd_quit;
	_cmd_list["JOIN"]		= &Server::cmd_join;

}

Server::~Server()
{
	std::cout << "The server has been shutdown." << std::endl;
}

std::string const &	Server::getPrefixServer() const
{
	return (this->_prefixServer);
}

int Server::initServer(int port) {
	struct pollfd new_poll;

	this->_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_sockfd == -1)
	{
		std::cout << RED << "Failed to create socket. errno: " << errno << WHI<<std::endl;
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
}

void Server::addNewClient()
{
	Client cli;

	struct sockaddr_in cliAdd;
	struct pollfd new_poll;
	socklen_t len = sizeof(cliAdd);

	int receiving_fd = accept(this->_sockfd, (sockaddr *)&(cliAdd), &len);

	new_poll.fd = receiving_fd;
	new_poll.events = POLLIN | POLLOUT;
	new_poll.revents = 0;

	cli.set_fd(receiving_fd);
	cli.set_ip(inet_ntoa(cliAdd.sin_addr));
	cli.set_Server(this);
	this->_clients.push_back(cli);
	this->_polls.push_back(new_poll);
	
	//std::cout << "CLIENT " << receiving_fd << " CONNECTED" << std::endl;
	//receiveFirstData(&cli);
}

Client* Server::getRefClientByFd(int fd)
{
	std::deque<Client>::iterator	it = _clients.begin();
	std::deque<Client>::iterator	itend = _clients.end();

	while (it != itend)
	{
		if (it->get_fd() == fd)
			return (&(*it));
		it++;
	}
	return (NULL);
}

void	Server::prepareMsgToClient(Client *cli)
{
	int					client_fd = cli->get_fd();
	Transmission*		transmission = this->getTransmissionByFd(client_fd);
	if (transmission == NULL)
		return;
	std::string			toSend = transmission->getMsg(); 
	std::vector<int>	destinataire = transmission->getFdDest();

	for (size_t i = 0; i < destinataire.size(); i++) {
		Client* dest = getRefClientByFd(destinataire[i]);
		if (dest)
			dest->setBufferOut(toSend);
	}

	std::vector<Transmission>::iterator	it;
	
	for (it = this->_transmission.begin(); it < this->_transmission.end(); it++)
	{
		if (it->getFdEmitter() == cli->get_fd())
			break ;
	}
	this->_transmission.erase(it);
	
}

void Server::setUpTransmission(Client *cli, std::string msg, int fdDest) {
    Transmission newTrans;
    
    newTrans.setFdEmitter(cli->get_fd());
    newTrans.setMsg(msg);
    newTrans.addNewFdDest(fdDest);
	this->_transmission.push_back(newTrans);
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

Transmission*	Server::getTransmissionByFd(int fd)
{
	std::vector<Transmission>::iterator	it;
	Transmission						ret;

	for (it = _transmission.begin(); it < _transmission.end(); it++)
	{
		if (it->getFdEmitter() == fd)
			return (&(*it));
	}
	return (NULL);
}

void	Server::removeClient(Client& cli)
{
	int	fd = cli.get_fd();
	size_t i = 0;
	std::deque<Client>::iterator it;
	std::vector<pollfd>::iterator jt;
	for (it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (it->get_fd() == fd)
			break ;
		i++;
	}
	close(it->get_fd());
	_clients.erase(it);
	for (jt = _polls.begin(); jt != _polls.end(); ++jt)
	{
		if (it->get_fd() == fd)
			break ;
		i++;
	}
	close(jt->events);
	_polls.erase(jt);
	close(fd);
	
}

int Server::serverLoop()
{
	g_isRunning = true;
	size_t 			i;
	while (g_isRunning)
	{
		//std::cout << "recv" <<std::endl;

		for (i = 0; i < this->_polls.size(); i++)
		{
			if (poll(&this->_polls[0], this->_polls.size(), -1) == -1 && g_isRunning)
				throw(std::runtime_error("poll() failed"));
/*
			Client* cli = getRefClientByFd(this->_polls[i].fd);
			if (cli == NULL) {
				continue;
				return (-1); // mais en vrai c'est chelou
			}
*/
			if (this->_polls[i].revents & POLLIN)
			{
				if (this->_polls[i].fd == this->_sockfd)
					this->addNewClient();
				else
				{
					try {
						std::deque<t_message*> messages;
						Client* cli = getRefClientByFd(this->_polls[i].fd);
						
						if (cli && cli->receive(messages)) {
							for (size_t i = 0; i < messages.size(); i++) {
								std::cout << GRE << "[[[receiveData]]]\n" << *messages[i] << WHI << std::endl;
								execute_cmd(cli, messages[i]);
								delete messages[i];
							}
						}
					} catch (std::exception &e) {
						std::cout << RED << "ERROR: " << e.what() << WHI << std::endl;
					}
				}
			}
			else if (this->_polls[i].revents & POLLOUT) {
				Client* cli = getRefClientByFd(this->_polls[i].fd);	
				cli->send_transmission();
			}
			_polls[i].revents = 0;
		}
	}
	this->cleanServer();
	return (0);
}

std::vector<Transmission> Server::getTransmission()
{
	return (this->_transmission);
}

Transmission Server::getFirstTransmission()
{
	Transmission ret;
	ret = this->_transmission[0];
	this->_transmission.erase(this->_transmission.begin());
	return (ret);
}
