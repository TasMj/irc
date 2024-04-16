#include "Server.hpp"

void    Server::cmd_nick(Client* cli, t_message* msg) {
	if (0
		|| !expect_N_Params(msg, 1)
	) { return; }
	
    std::string newNick = msg->params[0];
    std::string nickName = cli->get_nickName();
	std::string response;

	// CHECKING
    if (getRefClientByNick(newNick))
		response = ERR_NICKNAMEINUSE(nickName, newNick, "A user already have this nickname");
	else {
		response = RPL_NICK(cli, newNick);
		cli->set_nickName(newNick);
		cli->isWelcomed("NICK");
	}
	cli->setBufferOut(response);
}