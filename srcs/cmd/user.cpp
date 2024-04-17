#include "Server.hpp"

void    Server::cmd_user(Client* cli, t_message* msg) {
	if (0
		|| !expect_N_Params(msg, 3)
	) { return; }
		
    std::string userName = msg->params[0];
	//bool		modified = false;
	std::string response;

	// CHECKING
    /* while (getRefClientByName(userName))
	{
		userName.append("_");
		modified = true;
	}
	if (modified)
        response = ":localhost 462 " + msg->params[0] + ": This username is already taken. Your username is : " << userName << "\r\n";
	else */
    response = ":localhost Your username is : " + userName + "\r\n"; 
	
	cli->set_userName(userName);

	// SENDING
	cli->setBufferOut(response);
	if (msg->command == "USER")
		cli->isWelcomed("USER");
}