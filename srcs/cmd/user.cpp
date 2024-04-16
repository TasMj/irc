#include "Server.hpp"

void    Server::cmd_user(Client* cli, t_message* msg) {
	/* if (0
		|| !expect_N_Params(msg, 3)
	) { return; } */
	/* if (!(cli->getLogStatus() & PASS))
	{
		std::cout << "zebi" << std::endl;
		cli->get_Server()->removeClient(*cli);
		return ;
	} */
		
    std::string userName = msg->params[0];
	bool		modified = false;
	std::string response;

	// CHECKING
    while (getRefClientByName(userName))
	{
		userName.append("_");
		modified = true;
	}
	if (modified)
        response = ":localhost " + msg->params[0] + " is already taken. Your username is : " + userName + ".\n";
	else
    	response = ":localhost Your username is : " + userName + "\n"; 
	cli->set_userName(userName);
	if (cli->get_userName()[0] == '&')
		cli->setIsOps(true);
	else
		cli->setIsOps(false);

	// SENDING
	cli->setBufferOut(response);
	if (msg->command == "USER")
		cli->isWelcomed("USER");
}