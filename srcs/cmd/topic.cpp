
#include "Server.hpp"

void	Server::cmd_topic(Client* cli, t_message* msg)
{
    std::string nickname = cli->get_nickName();
    std::string response;
    
    if (0 || !expect_N_Params(msg, 1))
    {
        response = ERR_NEEDMOREPARAMS(nickname, "TOPIC", "need more param.");
        cli->setBufferOut(response);   
        return;
    }
    
    std::string &channelName = msg->params[0];
    channelName = channelName.substr(1);
    Channel *currentChan = getRefChannelByName(channelName); //recup Channel
    
    if (currentChan == NULL) {
        response = ERR_NOSUCHCHANNEL(nickname, channelName, " Channel doesn't exist.");
        cli->setBufferOut(response);
        return ;   
    }
    if (currentChan->checkClientExist(nickname) == false) { //verifier que le client existe
        response = ERR_NOTONCHANNEL(nickname, channelName, " Client not present in this channel");
        cli->setBufferOut(response);
        return ;
    }
    
    if (expect_LastParams(msg) == false)
    {
        if (currentChan->getTopic() != "")
            response = RPL_TOPIC(nickname, channelName, currentChan->getTopic());
        else
            response = RPL_NOTOPIC(nickname, channelName, "NO TOPIC YET");
        cli->setBufferOut(response);
        return ;
    }

    if (currentChan->_topicModeOn && currentChan->checkOperator(cli) == false) {//modif topic mode operator??
        response = ERR_CHANOPRIVSNEEDED(nickname, channelName);
        cli->setBufferOut(response);
        return ;
    }
    std::string new_top = msg->last_params;
    if (new_top != "" && new_top[0] == ':')
        new_top = new_top.substr(1);
    currentChan->setTopic(new_top);
    response = RPL_TOPIC(nickname, channelName, new_top);
    currentChan->sendToAllClients(response);
}