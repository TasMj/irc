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
            setUpTransmission(cli, ERR_NOSUCHCHANNEL(cli->get_nickName(), it->second->getName(), name + "is not an existing channel."), cli->get_fd());
        	prepareMsgToClient(cli);
            return;
        }

		if (!it->second->isInChannel(cli->get_nickName()))
		{
			setUpTransmission(cli, ERR_NOTONCHANNEL(cli->get_nickName(), it->second->getName(), "You're not on that channel."), cli->get_fd());
        	prepareMsgToClient(cli);
			return ;
		}
        response = RPL_PRIVMSG(cli->get_nickName(), "#" + it->second->getName() ,msg->last_params);
        it->second->sendToAllClients(response, cli);
	} else {
        /*si nick*/
        std::string nick = name;
        std::string msgToSend = msg->last_params;

		//int		fd_to_send;
		Client* found = findNickName(nick);
        if (found) {
        	setUpTransmission(cli, RPL_PRIVMSG(cli->get_nickName(), nick, msgToSend), found->get_fd());
        	prepareMsgToClient(cli);
        }
		else
        {
			setUpTransmission(cli, ERR_NOSUCHNICK(cli->get_nickName(), nick, "No user matching with" + nick + "."), cli->get_fd());
        	prepareMsgToClient(cli);
        }
		/* setUpTransmission(cli, response, found->get_fd());
        prepareMsgToClient(cli); */
    }
}
