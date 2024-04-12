/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerCommands.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:26:50 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/12 17:06:18 by aclement         ###   ########.fr       */
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

Client*	Server::findNickName(std::string nickName) {
	if (nickName.empty())
		return (NULL);
	std::deque<Client>::iterator first, last;

	first = _clients.begin();
	last = _clients.end();
	while (first != last) {
    	if (nickName.compare(first->get_nickName()) == 0)
			return (&(*first));
		++first;
	}
	return (NULL);
}

static Client* findUserName(std::deque<Client>& clients, std::string userName) {
	std::deque<Client>::iterator first, last;

	first = clients.begin();
	last = clients.end();
	while (first != last) {
    	if (userName.compare(first->get_userName()) == 0)
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
    if (findNickName(newNick))
        response = ":localhost NICK " + nickName + " :\nthis nickname already exist. Please try a new one.\n";
	else {
		cli->set_nickName(newNick);
    	response = ":localhost NICK " + newNick + " :Your nick name is now : " + newNick + "\n"; 
	}

	// SENDING
    cli->get_Server()->setUpTransmission(cli, response, cli->get_fd());
    cli->get_Server()->prepareMsgToClient(cli);
	cli->isWelcomed(NICK);
}

void    Server::cmd_user(Client* cli, t_message* msg) {
	if (0
		|| !expect_N_Params(msg, 3)
	) { return; }
	
		
    std::string userName = msg->params[0];
	bool		modified = false;
	std::string response;

	// CHECKING
    while (findUserName(_clients, userName))
	{
		userName.append("_");
		modified = true;
	}
	if (modified)
        response = ":localhost USER " + userName + " :" + msg->params[0] + " is already taken. You're now known has " + userName + ".\n";
	else
    	response = ":localhost USER " + userName + " :You're now known has " + userName + "\n"; 
	cli->set_userName(userName);


	// SENDING
    cli->get_Server()->setUpTransmission(cli, response, cli->get_fd());
    cli->get_Server()->prepareMsgToClient(cli);
	
	cli->isWelcomed(USER);
}

/* void	Server::cmd_join(Client* cli, t_message* msg) {
	if (0
		|| !expect_N_Params(msg, 1)
	) {return; }
	// for (int i = 0; msg->params[i]; i++)
		
} */

void	Server::cmd_ping(Client* cli, t_message* msg) {
	if (0
		|| !expect_N_Params(msg, 1)
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
			removeClient(*it);
			break ;
		}
	}
}

void	Server::cmd_pass(Client* cli, t_message* msg) {
	if (0
		|| !expect_N_Params(msg, 1)
	) { return; }

	if (!msg->params.empty()
		&& _password.compare(msg->params[0]) == 0
		//&& !cli->get_nickName().empty()
		//&& !cli->get_userName().empty()
	) {
		cli->isWelcomed(PASS);
		
		return ;
	}

	std::string err_msg =":localhost DISCONNECT localhost: \n Wrong password.\n";
	cli->get_Server()->setUpTransmission(cli, err_msg, cli->get_fd());
    cli->get_Server()->prepareMsgToClient(cli);
//	send(cli->get_fd(), err_msg.c_str(), err_msg.size(), 0);
}