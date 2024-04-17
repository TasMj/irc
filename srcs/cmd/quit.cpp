#include "Server.hpp"

void	Server::cmd_quit(Client* cli, t_message* msg) {
	if (0
		|| !expect_LastParams(msg)
	) { return; }
	removeClient(*cli);
}

/*
TODO:
	quand un user quit il doit quitter
		- les channels
		- la liste des invite
		- la list des operateurs
*/