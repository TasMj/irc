/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:26:50 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/17 04:20:19 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(std::string password, int port)
	: _password(password)
	, _prefixServer(":localhost")
{
	struct pollfd new_poll;

	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (_sockfd == -1) // errno
		throw(std::runtime_error("Failed to create socket"));

	_sockAddr.sin_family = AF_INET;
	_sockAddr.sin_addr.s_addr = INADDR_ANY;
	_sockAddr.sin_port = htons(port);
	int reuseAddr = 1;
	if (setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &reuseAddr, sizeof(reuseAddr)) == -1)
		throw(std::runtime_error("Failed to set SO_REUSEADDR option"));

	if (bind(_sockfd, (struct sockaddr *)&_sockAddr, sizeof(sockaddr)) < 0) // port + errno
		throw(std::runtime_error("Failed to bind to port"));

	if (listen(_sockfd, 10) < 0)
		throw(std::runtime_error("Failed to listen on socket"));

	new_poll.fd = _sockfd;
	new_poll.events = POLLIN;
	new_poll.revents = 0;
	_polls.push_back(new_poll);

	_cmd_list["NICK"]		= &Server::cmd_nick;
	_cmd_list["USER"]		= &Server::cmd_user;
	_cmd_list["PASS"]		= &Server::cmd_pass;
	_cmd_list["PING"]		= &Server::cmd_ping;
	_cmd_list["JOIN"]		= &Server::cmd_join;
	_cmd_list["INVITE"]		= &Server::cmd_invite;
	_cmd_list["MODE"]		= &Server::cmd_mode;
	_cmd_list["PRIVMSG"]	= &Server::cmd_privmsg;
	_cmd_list["QUIT"]		= &Server::cmd_quit;
	_cmd_list["KICK"]		= &Server::cmd_kick;
	_cmd_list["TOPIC"]		= &Server::cmd_topic;
}

Server::~Server() {
	std::vector<pollfd>::iterator				it;
	for (it = _polls.begin(); it != _polls.end(); it++) {
		close(it->fd);
	}
	
	std::deque<Client>::iterator	jt;
	for (jt = _clients.begin(); jt != _clients.end(); jt++)
		jt->leaveAllChannels();

	std::map<std::string, Channel*>::iterator	ite;
	for (ite = _channels.begin(); ite != _channels.end(); ite++) {
        delete ite->second;
	}
}

void	Server::addNewClient() {
	struct sockaddr_in cliAdd;
	socklen_t len = sizeof(cliAdd);

	int receiving_fd = accept(_sockfd, (sockaddr *)&(cliAdd), &len);

	if (receiving_fd < 0)
		throw(std::runtime_error("Failed to create Client"));

	struct pollfd new_poll;
	new_poll.fd = receiving_fd;
	new_poll.events = POLLIN | POLLOUT;
	new_poll.revents = 0;

	_clients.push_back(Client(receiving_fd, this));
	_polls.push_back(new_poll);
}

void	Server::removeClient(Client& cli) {
	int	fd = cli.get_fd();

	std::deque<Client>::iterator	it;
	for (it = _clients.begin(); it != _clients.end(); it++) {
		if (it->get_fd() == fd) {
			it->leaveAllChannels();
			_clients.erase(it);
			close(fd);
			break;
		}
	}
	
	std::vector<pollfd>::iterator jt;
	for (jt = _polls.begin(); jt != _polls.end(); ++jt) {
		if (jt->fd == fd) {
			_polls.erase(jt);
			break;
		}
	}
}

int		Server::execute_cmd(Client* cli, t_message* msg) {
	if (!cli || ! msg)
		return (-1);
	t_cmd_list::iterator	it = _cmd_list.find(msg->command);
	if (it != _cmd_list.end()) {
		function toExecute = it->second;
		(this->*(toExecute))(cli, msg);
	}
	return (0);
}

int		Server::serverLoop() {
	g_isRunning = true;
	while (g_isRunning) {
		size_t 			i;
		for (i = 0; i < _polls.size(); i++) {
			if (poll(&_polls[0], _polls.size(), -1) == -1 && g_isRunning)
				throw(std::runtime_error("poll() failed"));

			int		fd = _polls[i].fd;
			short	event = _polls[i].revents;
			if (event & POLLIN && fd == _sockfd) {
				addNewClient();
				continue;
			}
			
			Client* cli = getRefClientByFd(fd);
			if (cli) {
				if (event & POLLIN) {
					std::deque<t_message*> messages;					
					if (cli->read_stream(messages)) {
						for (size_t i = 0; i < messages.size(); i++) {
							std::cout << GRE << fd << ": " << *messages[i] << WHI << std::endl;
							execute_cmd(cli, messages[i]);
							delete messages[i];
						}
					} else {
						removeClient(*cli);
					}
				}
				else if (event & POLLOUT) {
					cli->write_stream();
				}
			}
		}
	}
	return (0);
}
