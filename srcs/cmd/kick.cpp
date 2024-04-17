/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:26:42 by tmejri            #+#    #+#             */
/*   Updated: 2024/04/17 05:20:16 by tmejri           ###   ########.fr       */
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
    std::deque<Client*>::iterator it = _clients.begin();
    
    for (it = _clients.begin(); it != _clients.end(); it++)
	{
		if ((*it)->get_nickName() == toKick)
            return (true);
	}
    return (false);
}

void    Channel::removeCliFromChan(std::string toKick)
{
    std::deque<Client*>::iterator it = _clients.begin();
    
    for (it = _clients.begin(); it != _clients.end(); it++)
	{
		if ((*it)->get_nickName() == toKick)
        {
            _clients.erase(it);
            return ;
        }
	}
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

void	Server::cmd_kick(Client* cli, t_message* msg)
{
    if (0
        || !expect_At_Least_N_Params(msg, 2)
        || !expect_LastParams(msg)
    ) return ;
        
    std::string channelName = msg->params[0];
    std::string toKick = msg->params[1];

	if (!channelName.empty() && (channelName[0] == '#' || channelName[0] == '&'))
		channelName.erase(0,1);
    if (toKick.size() == 2)
        toKick.erase(1, 2);
    else
        toKick.erase(toKick.length() - 1, toKick.length() - 2);
    std::string reason = msg->last_params;

	t_channel_map::iterator it;
	it = _channels.find(channelName);
    if (it == _channels.end())
        return;
    Channel *currentChan = it->second; //recup Channel
    std::string ERR;
    std::string output;
    
    if (currentChan == NULL)
        ERR = ERR_NOSUCHCHANNEL(cli->get_nickName(), channelName, " Channel doesn't exist.");
    else if (currentChan->checkOperator(cli) == false) // verifier que emitter a le droit de kick
        ERR = ERR_CHANOPRIVSNEEDED(cli->get_nickName(), channelName);
    else if (currentChan->checkClientExist(toKick) == false) //verifier que le client existe
        ERR = ERR_NOTONCHANNEL(cli->get_nickName(), channelName, " Client not present in this channel");
    else
    {
        currentChan->removeCliFromChan(toKick); //si il existe, le remove de la map channel
        output = RPL_KICK(cli->get_nickName(), toKick, channelName, reason);
        currentChan->sendToAllClients(output, cli);
    }
    if (!ERR.empty())
        cli->setBufferOut(ERR);
    else if (!output.empty())
        cli->setBufferOut(output);
}