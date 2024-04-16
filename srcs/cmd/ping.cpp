#include "Server.hpp"

void	Server::cmd_ping(Client* cli, t_message* msg) {
	if (0
		|| !expect_N_Params(msg, 1)
	) { return; }
	
    std::string response = ":localhost PONG localhost: " + cli->get_nickName() + "\n";
	cli->setBufferOut(response);
}