#include "Server.hpp"

std::string	PRIVMSG(std::string sender, std::string channel, std::string message)
{
	std::stringstream	output;

	output << ":" <<  sender;
	output << " PRIVMSG ";
	output << "#" << channel;
	output << " :" << message;
	output << "\r\n";
	return (output.str());
}

void    Server::cmd_privmsg(Client* cli, t_message* msg) {
	if (0
		|| !expect_At_Least_N_Params(msg, 1)
		|| !expect_LastParams(msg)
	) { return; }

    std::string prefixe = ":localhost PRIVMSG ";	   
	std::string response;
	
	std::string name = msg->params[0];
    /*on check si nick ou channel*/
	if (name[0] == '#') {
        name.erase(0,1);
        std::map<std::string, Channel*>::iterator it = _channels.find(name);
        if (it == _channels.end()) {
            // ERROR channel not found
            return;
        }
        response = PRIVMSG(cli->get_nickName(), it->second->getName() ,msg->last_params);
        it->second->sendToAllClients(response, cli);
	} else {
        /*si nick*/
        std::string nick = name;
        std::string msgToSend = msg->last_params;

		int		fd_to_send;
		Client* found = findNickName(nick);
        if (found) {
        	response = prefixe + nick + " :" + response + "\n";
			fd_to_send = found->get_fd();
        }
		else
        {
			response = prefixe + nick + " :" + "no nick matching\n";
			fd_to_send = cli->get_fd();
        }
		cli->get_Server()->setUpTransmission(cli, response, fd_to_send);
        cli->get_Server()->prepareMsgToClient(cli);
    }
}
