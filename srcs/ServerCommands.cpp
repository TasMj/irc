/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerCommands.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:26:50 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/11 19:22:57 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

bool	expect_N_Params(t_message* msg, size_t n) {
	return (msg->params.size() == n);
}

bool	expect_At_Least_N_Params(t_message* msg, size_t n) {
	return (msg->params.size() >= n);
}

bool	expect_LastParams(t_message* msg) {
	return (msg->has_last_params);
}

/* ************************************************************************** */

static Client* findNickName(std::deque<Client>& clients, std::string nickName) {
	std::deque<Client>::iterator first, last;

	first = clients.begin();
	last = clients.end();
	while (first != last) {
    	if (nickName.compare(first->get_nickName()))
			return (&(*first));
		++first;
	}
	return (NULL);
}

int Server::execute_cmd(Client* cli, t_message* msg)
{
	if (!cli || ! msg)
		return (-1);
	t_cmd_list::iterator	it = _cmd_list.find(msg->command);
	if (it != _cmd_list.end()) {
		function toExecute = it->second;
		(this->*(toExecute))(cli, msg);
	}
	return (0);
}

void    Server::cmd_nick(Client* cli, t_message* msg) {
	if (0
		|| !expect_N_Params(msg, 1)
	) { return; }
	
    std::string newNick = msg->params[0];
    std::string nickName = cli->get_nickName();
	
	std::string response;

	// CHECKING
    if (findNickName(_clients, newNick))
        response = ":localhost NICK " + nickName + " :\nthis nickname already exist. Please try a new one.\n";
	else {
		cli->set_nickName(newNick);
    	response = ":localhost NICK " + newNick + " :Your nick name is now : " + newNick + "\n"; 
	}

	// SENDING
    cli->get_Server()->setUpTransmission(cli, response, cli->get_fd());
    cli->get_Server()->prepareMsgToClient(cli);
}

void	Server::cmd_join(Client* cli, t_message* msg) {
	if (0
		|| !expect_N_Params(msg, 1)
	) {return; }
	// for (int i = 0; msg->params[i]; i++)
		
}

void	Server::cmd_ping(Client* cli, t_message* msg) {
	if (0
		|| !expect_N_Params(msg, 0)
	) { return; }
	
    std::string response = ":localhost PONG localhost: " + cli->get_nickName() + "\n";
    cli->get_Server()->setUpTransmission(cli, response, cli->get_fd());
    cli->get_Server()->prepareMsgToClient(cli);
}

void	Server::cmd_quit(Client* cli, t_message* msg) {
	if (0
		|| !expect_N_Params(msg, 0)
	) { return; }

	int fd = cli->get_fd();
	std::deque<Client>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (it->get_fd() == fd)
		{
			it->remove();
			break ;
		}
	}
}

void	Server::cmd_pass(Client* cli, t_message* msg) {
	if (0
		|| !expect_N_Params(msg, 1)
	) { return; }
	
	if (!msg->params.empty() && _password.compare(msg->params[0]) == 0)
		return ;

	std::string err_msg =":localhost DISCONNECT localhost: \n Wrong password.\n";
	send(cli->get_fd(), err_msg.c_str(), err_msg.size(), 0);
}

void    Server::cmd_privmsg(Client* cli, t_message* msg) {
	if (0
		|| !expect_At_Least_N_Params(msg, 1)
		|| !expect_LastParams(msg)
	) { return; }
	
	std::string name = msg->params[0];
    /*on check si nick ou channel*/
	if (name[0] == '#') {
		/*si channel*/
        /*recup nom du chennel*/
        /*recup msg du chennel*/
        /*on verifie que le nickname existe*/
        /*on envoie le msg au nickname*/
	} else {
        /*si nick*/
        std::string nick = name;
        std::string msgToSend = msg->last_params;


        std::string prefixe = ":localhost PRIVMSG ";	   
	   	std::string response;

		int		fd_to_send;
		Client* found = findNickName(_clients, nick);
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

void    Server::cmd_privmsg(Client* cli, t_message* msg) {
}