#include "Server.hpp"

void	Server::cmd_quit(Client* cli, t_message* msg) {
	if (0
		|| !expect_N_Params(msg, 1)
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