#include "Server.hpp"

void	Server::cmd_quit(Client* cli, t_message* msg) {
	if (0
		|| !expect_N_Params(msg, 1)
	) { return; }

	int fd = cli->get_fd();
	std::deque<Client>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (it->get_fd() == fd)
		{
			removeClient(*it);
			break ;
		}
	}
}

/*
TODO:
	quand un user quit il doit quitter
		- les channels
		- la liste des invite
		- la list des operateurs
*/