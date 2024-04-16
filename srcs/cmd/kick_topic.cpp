/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick_topic.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:26:42 by tmejri            #+#    #+#             */
/*   Updated: 2024/04/16 15:14:58 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Channel.hpp"

Channel *Server::getRefChannelByName(std::string name)
{
	std::map<std::string, Channel*>::iterator it = _channels.begin();

	for (it = _channels.begin(); it != _channels.end(); it++)
	{
		if (it->first == name)
            return (it->second);
	}
    return (NULL);
}

bool    Channel::checkClientExist(std::string toKick)
{
    t_clients_map::iterator it = _clients.begin();
    
    for (it = _clients.begin(); it != _clients.end(); it++)
	{
		if (it->first == toKick)
            return (true);
	}
    std::cout << toKick << " " << std::endl;
    return (false);
}

void    Channel::removeCliFromChan(std::string toKick)
{
    t_clients_map::iterator it = _clients.begin();
    
    for (it = _clients.begin(); it != _clients.end(); it++)
	{
		if (it->first == toKick)
        {
            _clients.erase(it);
            // std::cout << toKick << " has been kicked" << std::endl;
            return ;
        }
	}
}

std::string	kickMsg(std::string user, std::string channel, std::string kickedUser, std::string reason)
{
	std::stringstream	output;

	output << ":" <<  user;
	output << " KICK ";
	output << "#" << channel;
	output << " " << kickedUser;
	output << " " << reason;
	output << "\r\n";
	return (output.str());
}

bool    Channel::checkTopicExist()
{
    if (this->_topic.empty())
        return (false);
    return (true);
}

void    Channel::setTopic(std::string topic)
{
    this->_topic = topic;
}

std::string Channel::getTopic()
{
    return (this->_topic);
}

void	Server::cmd_topic(Client* cli, t_message* msg)
{
    (void)cli;
    std::string ERR;
    std::string output;
    std::cout << msg->raw << std::endl;
    if (0 || !expect_N_Params(msg, 1))
    {
        ERR = ERR_NEEDMOREPARAMS("", "TOPIC", "need more param.");        
        return;
    }
    std::string &channelName = msg->params[0];
    channelName = channelName.substr(1);
    // std::cout << "Channel: " << channelName << std::endl;
    // std::cout << "Topic: " <<  << std::endl;

    Channel *currentChan = Server::getRefChannelByName(channelName); //recup Channel
    if (currentChan == NULL)
        ERR = ERR_NOSUCHCHANNEL(cli->get_nickName(), channelName, " Channel doesn't exist.");
    else if (currentChan->checkClientExist(cli->get_nickName()) == false) //verifier que le client existe
        ERR = ERR_NOTONCHANNEL(cli->get_nickName(), channelName, " Client not present in this channel");
    else if (!expect_LastParams(msg))
    {
        if (currentChan->getTopic() != "")
            output = RPL_TOPIC(cli->get_nickName(), channelName, currentChan->getTopic());
        else
            ERR = RPL_NOTOPIC(cli->get_nickName(), channelName, "NO TOPIC YET");
    }
    else
    {
        // if ( && currentChan->checkOperator(cli) == false) modif topic mode operator??
            ERR = ERR_CHANOPRIVSNEEDED(cli->get_nickName(), channelName, " Not an operator.");
        std::string new_top = msg->last_params;
        if (new_top != "" && new_top[0] == ':')
            new_top = new_top.substr(1);
        currentChan->setTopic(new_top);
        output = RPL_TOPIC(cli->get_nickName(), channelName, new_top);
        currentChan->sendToAllClients(output, cli);
    }
    
    else if () // verifier que emitter a le droit de kick
       
       
    if (!ERR.empty())
        cli->get_Server()->setUpTransmission(cli, ERR, cli->get_fd()); //
    else if (!output.empty())
        cli->get_Server()->setUpTransmission(cli, output, cli->get_fd()); //
    cli->get_Server()->prepareMsgToClient(cli);

}

void	Server::cmd_kick(Client* cli, t_message* msg)
{
    (void)cli;
    
    if (0 || !expect_At_Least_N_Params(msg, 1))
        return ;
        
    std::deque<std::string> nameAndReason = split(msg->last_params, ":");

    std::string &channelName = msg->params[1];
    std::string toKick = nameAndReason[0];

    if (toKick.size() == 2)
        toKick.erase(1, 2);
    else
        toKick.erase(toKick.length() - 1, toKick.length() - 2);
    std::string reason = nameAndReason[1];
    
    // std::cout << "Channel: " << channelName << std::endl;
    // std::cout << "Name: <" << toKick << ">" << std::endl;
    // std::cout << "Reason: " << reason << std::endl;

    Channel *currentChan = Server::getRefChannelByName(channelName); //recup Channel
    std::string ERR;
    std::string output;
    
    if (currentChan == NULL)
        ERR = ERR_NOSUCHCHANNEL(cli->get_nickName(), channelName, " Channel doesn't exist.");
    else if (currentChan->checkOperator(cli) == false) // verifier que emitter a le droit de kick
        ERR = ERR_CHANOPRIVSNEEDED(cli->get_nickName(), channelName, " Not an operator.");
    else if (currentChan->checkClientExist(toKick) == false) //verifier que le client existe
        ERR = ERR_NOTONCHANNEL(cli->get_nickName(), channelName, " Client not present in this channel");
    else
    {
        currentChan->removeCliFromChan(toKick); //si il existe, le remove de la map channel
        output = kickMsg(cli->get_nickName(), channelName, toKick, reason);
        currentChan->sendToAllClients(output, cli);
    }
    if (!ERR.empty())
        cli->get_Server()->setUpTransmission(cli, ERR, cli->get_fd()); //
    else if (!output.empty())
        cli->get_Server()->setUpTransmission(cli, output, cli->get_fd()); //
    cli->get_Server()->prepareMsgToClient(cli);
}