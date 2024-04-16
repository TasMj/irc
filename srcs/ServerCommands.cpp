/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerCommands.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:26:50 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/15 22:55:16 by tmalless         ###   ########.fr       */
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
	
	/* if (!(cli->getLogStatus() & PASS))
	{
		std::cout << "zboub" << std::endl;
		return ;
	} */
	
    std::string newNick = msg->params[0];
    std::string nickName = cli->get_nickName();
	std::string response;

	// CHECKING
    if (findNickName(newNick))
	{
		/* newNick.append("_");
		while (findNickName(newNick))
		{
			newNick.append("_");
		}
		cli->set_nickName(newNick); */
        //response = ":localhost NICK " + newNick + " :\nthis nickname has already been taken. Your new nickname is " + newNick + "\n";
		response = "A user already have this nickname";
		cli->get_Server()->setUpTransmission(cli, ERR_NICKNAMEINUSE(nickName, newNick, response), cli->get_fd());
    	cli->get_Server()->prepareMsgToClient(cli);
	}
	else {
		cli->get_Server()->setUpTransmission(cli, RPL_NICK(cli, newNick), cli->get_fd());
    	cli->get_Server()->prepareMsgToClient(cli);
		cli->set_nickName(newNick);
		cli->isWelcomed("NICK");
	}

	// SENDING
 
	
}

void    Server::cmd_user(Client* cli, t_message* msg) {
	/* if (0
		|| !expect_N_Params(msg, 3)
	) { return; } */
	/* if (!(cli->getLogStatus() & PASS))
	{
		std::cout << "zebi" << std::endl;
		cli->get_Server()->removeClient(*cli);
		return ;
	} */
		
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
        response = ":localhost " + msg->params[0] + " is already taken. Your username is : " + userName + ".\n";
	else
    	response = ":localhost Your username is : " + userName + "\n"; 
	cli->set_userName(userName);
	if (cli->get_userName()[0] == '&')
		cli->setIsOps(true);
	else
		cli->setIsOps(false);

	// SENDING
    cli->get_Server()->setUpTransmission(cli, response, cli->get_fd());
    cli->get_Server()->prepareMsgToClient(cli);
	
	if (msg->command == "USER")
		cli->isWelcomed("USER");
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
		|| !expect_N_Params(msg, 1)
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
		cli->isWelcomed("PASS");
		
		return ;
	}

	std::string err_msg =":localhost Wrong password.\n";
	cli->get_Server()->setUpTransmission(cli, err_msg, cli->get_fd());
    cli->get_Server()->prepareMsgToClient(cli);
	//cli->get_Server()->removeClient(*cli);
//	send(cli->get_fd(), err_msg.c_str(), err_msg.size(), 0);
}

// void    Server::cmd_privmsg(Client* cli, t_message* msg) {
// 	if (0
// 		|| !expect_At_Least_N_Params(msg, 1)
// 		|| !expect_LastParams(msg)
// 	) { return; }
	
// 	std::string name = msg->params[0];
//     /*on check si nick ou channel*/
// 	if (name[0] == '#') {
// 		/*si channel*/
//         /*recup nom du chennel*/
//         /*recup msg du chennel*/
//         /*on verifie que le nickname existe*/
//         /*on envoie le msg au nickname*/
// 	} else {
//         /*si nick*/
//         std::string nick = name;
//         std::string msgToSend = msg->last_params;


//         std::string prefixe = ":localhost PRIVMSG ";	   
// 	   	std::string response;

// 		int		fd_to_send;
// 		Client* found = findNickName(_clients, nick);
//         if (found) {
//         	response = prefixe + nick + " :" + response + "\n";
// 			fd_to_send = found->get_fd();
//         }
// 		else
//         {
// 			response = prefixe + nick + " :" + "no nick matching\n";
// 			fd_to_send = cli->get_fd();
//         }
// 		cli->get_Server()->setUpTransmission(cli, response, fd_to_send);
//         cli->get_Server()->prepareMsgToClient(cli);
//     }
// }

/* static size_t	n_params_wanted(std::string flags)
{
	size_t n = 0;
	for (size_t i = 0; flags[i]; i++)
	{
		if (flags[i] == 'o' || flags[i] == 'k' || flags[i] == 'l')
			n++;
	}
	return (n);
} */


