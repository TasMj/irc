#include "Server.hpp"

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
            response = ERR_NOSUCHCHANNEL(cli->get_nickName(), it->second->getName(), name + "is not an existing channel.");
			cli->setBufferOut(response);
            return;
        }

		if (!it->second->isInChannel(cli->get_nickName()))
		{
			response = ERR_NOTONCHANNEL(cli->get_nickName(), it->second->getName(), "You're not on that channel.");
			cli->setBufferOut(response);
			return ;
		}
        response = RPL_PRIVMSG(cli->get_nickName(), "#" + it->second->getName() ,msg->last_params);
        it->second->sendToAllClients(response, cli);
	} else {
        /*si nick*/
        std::string nick = name;
        std::string msgToSend = msg->last_params;

		Client* found = getRefClientByNick(nick);
        if (found) {
        	response = RPL_PRIVMSG(cli->get_nickName(), nick, msgToSend);
			cli->setBufferOut(response);
        }
		else
        {
			response = ERR_NOSUCHCHANNEL(cli->get_nickName(), nick, "No user matching with" + nick + ".");
			cli->setBufferOut(response);
        }
		cli->setBufferOut(response);
    }
}
