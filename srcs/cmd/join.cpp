
#include "Server.hpp"

void	Server::cmd_join(Client* cli, t_message* msg) {
	(void)cli;
	if (0
		|| !expect_At_Least_N_Params(msg, 1)
	) {return; }
	
	std::deque<std::string> channelNames = split(msg->params[0], ",");
	std::deque<std::string> channelPasswords;
    if (msg->params.size() == 2) {
        channelPasswords = split(msg->params[1], ",");
    }
	
	for (size_t i = 0; i < channelNames.size(); i++) {
        std::string     name = channelNames[i];
        std::string*    password = NULL;
		if (name[0] == '#' || name[0] == '&') {
            name.erase(0,1);
            if (i < channelPasswords.size())
                password = new std::string(channelPasswords[i]);
            t_channel_map::iterator it = _channels.find(name);
            if (it == _channels.end())
                _channels[name] = new Channel(name, password);
            cli->join(_channels[name], password);
            delete password;
        } else {
            //send 476 -> ERR_BADCHANMASK
        }
	}	
}