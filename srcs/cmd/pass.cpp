#include "Server.hpp"

void	Server::cmd_pass(Client* cli, t_message* msg) {
	if (0
		|| !expect_N_Params(msg, 1)
	) { return; }

	if (!msg->params.empty()
		&& _password.compare(msg->params[0]) == 0
		//&& !cli->get_nickName().empty()
		//&& !cli->get_userName().empty()
	) {
		cli->isWelcomed("PASS");
		
		return ;
	}

	std::string err_msg =":localhost Wrong password.\n";
	cli->setBufferOut(err_msg);
}