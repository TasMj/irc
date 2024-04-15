/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:26:42 by tmejri            #+#    #+#             */
/*   Updated: 2024/04/15 14:24:43 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Channel.hpp"

/* Channel *Server::getRefChannelByName(std::string name)
{
	std::map<std::string, Channel*>::iterator it = _channels.begin();

	for (it = _channels.begin(); it != _channels.end(); it++)
	{
        // std::cout << CYA << "it->first: " << it->first << WHI << std::endl;
		if (it->first == name)
            return (it->second);
	}
    return (NULL);
} */

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
            std::cout << toKick << " has been kicked" << std::endl;
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
	t_channel_map::iterator it;
	it = _channels.find(channelName);
    Channel *currentChan = it->second; //recup Channel
    std::string ERR;
    std::string output;
    
    if (it == _channels.end())
        ERR = errChannel(cli->get_nickName(), channelName, " Channel doesn't exist.");
    else if (currentChan->checkOperator(cli) == false) // verifier que emitter a le droit de kick
        ERR = errOperator(cli->get_nickName(), channelName, " Not an operator.");
    else if (currentChan->checkClientExist(toKick) == false) //verifier que le client existe
        ERR = errClient(cli->get_nickName(), channelName, " Client not present in this channel");
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