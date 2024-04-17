/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 18:28:10 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/17 02:42:20 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/Server.hpp"
# include "../../includes/Channel.hpp"

/* ************************************************************************** */
// MODE COMMAND LOGIC
/* ************************************************************************** */

static void	cmd_mode_chan(Client* cli, t_message* msg, Channel* chan) {
	std::string response;
	std::string	userName;
	std::string	password;
	char		op = '+';

	if (msg->params[1][0] == '-')
		op = '-';
	/* for (size_t n = 2; n <= nParamsNeeded; n++)
	{ */
	for (size_t i = 0; msg->params[1][i]; i++)
	{
		size_t n = 2;
		if (msg->params[1][i] == 'o')
		{
			if (n >= msg->params.size())
			{
				response = ERR_NEEDMOREPARAMS(cli->get_nickName(), "MODE", "Please provide a username (o).");
				cli->setBufferOut(response);
			}
			else if (op == '+') {
				Client* newOperator = cli->get_Server()->getRefClientByName(msg->params[n]);
				if (newOperator)
					chan->addOperator(cli, newOperator, false);
			}
			else
				chan->removeOperator(cli, cli->get_Server()->getRefClientByName(msg->params[n]));
			n++;
		}
		if (msg->params[1][i] == 'k')
		{
			if (n >= msg->params.size() && op == '+')
			{
				response = ERR_NEEDMOREPARAMS(cli->get_nickName(), "MODE", "Please provide an alphanum password (+k).");
				cli->setBufferOut(response);
			}
			else if (op == '+')
			{
				chan->modPassword(msg->params[n], cli);
				n++;
			}
			else
				chan->removePassword(cli);
		}
		if (msg->params[1][i] == 'l')
		{
			if (n >= msg->params.size() && op == '+')
			{
				response = ERR_NEEDMOREPARAMS(cli->get_nickName(), "MODE", "Please provide a numeric limit (+l).");
				cli->setBufferOut(response);
			}
			else if (op == '+')
			{
				chan->modLimit(msg->params[n], cli);
				n++;
			}
			else
				chan->removeLimit(cli);
		}
		if (msg->params[1][i] == 'i')
		{
			if (op == '+')
				chan->inviteModeOn(cli);
			else
				chan->inviteModeOff(cli);
		}
		if (msg->params[1][i] == 't')
		{
			if (op == '+')
				chan->topicModeOn(cli);
			else
				chan->topicModeOff(cli);
		}
	}
}

void	Server::cmd_mode(Client* cli, t_message* msg) {
	std::string response;
	std::map<std::string, Channel *>::iterator	it;
	if (msg->params[0][0] == '#')
		msg->params[0].erase(0,1);

	it = _channels.find(msg->params[0]);
	if (it != _channels.end())
	{
		if (!it->second->checkOperator(cli))
		{
			response = ERR_CHANOPRIVSNEEDED(cli->get_nickName(), it->second->getName()), cli->get_fd();
			cli->setBufferOut(response);
			return ;
		}
		if (msg->params[1].find_first_not_of("+-itkol", 0) != std::string::npos)
		{
			response = ERR_UNKNOWNMODE(cli->get_nickName(), it->second->getName());
			cli->setBufferOut(response);
		}
		else
			cmd_mode_chan(cli, msg, it->second);
	}
	else
	{
		response = ERR_NOSUCHCHANNEL(cli->get_nickName(), msg->params[0], "This channel doesn't exist.");
		cli->setBufferOut(response);
	}
}

/* ************************************************************************** */
// HANDLE OPERATOR FLAG
/* ************************************************************************** */

bool			Channel::checkOperator(Client* cli)
{
	if (!cli)
		return (false);
	std::vector<Client *>::iterator it;
	for (it = _operators.begin(); it != _operators.end(); it++)
	{
		std::cout << (*it) << std::endl;
		if ((*it)->get_userName() == cli->get_userName())
		{
			std::cout << cli->get_nickName() << " is an operator of this channel." << std::endl;
			return (true);
		}
	}
	std::cout << cli->get_nickName() << " is not an operator of this channel." << std::endl;
	return (false);
};

void			Channel::addOperator(Client* sender, Client* receiver, bool creation)
{
	std::string msg;
	if (!receiver)
	{
		std::cout << "This user doesn't exist." << std::endl;
		msg = ERR_NOSUCHNICK(sender->get_nickName(), "", "This user doesn't exist");
		sender->setBufferOut(msg);
		return ;
	}
		
	if (!creation)
	{
		t_clients_map::iterator it;
		
		for (it = _clients.begin(); it != _clients.end(); it++)
		{
			if (it->second->get_nickName() == receiver->get_nickName())
				break ;
		}
		
		if (it == _clients.end())
		{
			msg = ERR_NOTONCHANNEL(sender->get_nickName(), _name, "This user is not in this channel.");
			sender->setBufferOut(msg);
			return ;
		}
	}
	
	for (size_t i = 0; i < _operators.size(); i++)
	{
		if (_operators[i]->get_nickName() == receiver->get_nickName())
		{
			msg = ERR_ISOPERATOR(sender->get_nickName(), receiver->get_nickName());
			sender->setBufferOut(msg);
			return ;
		}
	}
	msg = receiver->get_nickName() + " is a new operator of this channel.";
	msg = RPL_MODE(sender->get_nickName(), _name, "+", "o", msg);
	sendToAllClients(msg);
	_operators.push_back(receiver);
};

void			Channel::removeOperator(Client* sender, Client* receiver)
{
	std::string msg;
	if (!receiver)
		return ;

	std::vector<Client*>::iterator it;
	for (it = _operators.begin(); it != _operators.end(); it++)
	{
		if ((*it)->get_nickName() == receiver->get_nickName())
		{
			_operators.erase(it);
			msg = receiver->get_nickName() + " is no more an operator of this channel.";
			msg = RPL_MODE(sender->get_nickName(), _name, "-", "o", msg);
			sendToAllClients(msg);
			return ;
		}
	}
	msg = ERR_NOTOPERATOR(sender->get_nickName(), receiver->get_nickName());
	sender->setBufferOut(msg);
};

/* ************************************************************************** */
// HANDLE PASSWORD FLAG
/* ************************************************************************** */

void			Channel::modPassword(std::string password, Client* cli)
{
	std::string msg;
	//if (!(_mode & (t_mode)K))

	std::cout << "This channel already ask for a password to enter." << std::endl;
	if (_password)
		_password->erase();
	std::string *pwd = new std::string(password);
	_password = pwd;
	delete pwd;

	_keyModeOn = true;
		//_mode = (t_mode)_mode | (t_mode)KEY; 
	/* if ((_mode & (t_login)K))
		std::cout << "le flag a ete ajoute !" << std::endl; */
	msg = password + " is the new password of this channel.";
	msg = RPL_MODE(cli->get_nickName(), _name, "+", "k", msg);
	sendToAllClients(msg);
	
};

void			Channel::removePassword(Client* cli)
{
	std::string msg;
	if (!_keyModeOn)
	{
		msg = ERR_NOPASSWORD(cli->get_nickName(), _name);
		cli->setBufferOut(msg);
		return ;
	}
	else
		_keyModeOn = false;	

	msg = RPL_MODE(cli->get_nickName(), _name, "-", "k", "This channel has no more password.");
	sendToAllClients(msg);
	if (_password)
		_password->erase();
};

/* ************************************************************************** */
// HANDLE LIMIT FLAG
/* ************************************************************************** */

void			Channel::modLimit(std::string limit, Client* cli)
{
	std::string msg;
	int	n_lim;
	
	if (limit.find_first_not_of("0123456789") != std::string::npos)
	{
		
		msg = ERR_NEEDMOREPARAMS(cli->get_nickName(), "MODE", "Need a numeric limit (+l).");
		cli->setBufferOut(msg);
		return ;
	}
		
	n_lim = atoi(limit.c_str());
	_limit = (size_t)n_lim;
	//_mode = (t_mode)_mode | (t_mode)LIMIT; 
	_limitModeOn = true;
	msg = limit + " is the maximum number of user allowed in this channel.";
	msg = RPL_MODE(cli->get_nickName(), _name, "+", "l", msg);
	sendToAllClients(msg);
};

void			Channel::removeLimit(Client* cli)
{
	_limitModeOn = false;
	std::string msg = RPL_MODE(cli->get_nickName(), _name, "-", "l", "This channel has no more user limit.");
	sendToAllClients(msg);
};

/* ************************************************************************** */
// HANDLE INVITE FLAG
/* ************************************************************************** */

void			Channel::inviteModeOn(Client* cli)
{
	_inviteModeOn = true;
	std::string msg = RPL_MODE(cli->get_nickName(), _name, "+", "i", "This channel is now accessible only through invitation.");
	sendToAllClients(msg);
};

void			Channel::inviteModeOff(Client* cli)
{
	_inviteModeOn = false;
	std::string msg = RPL_MODE(cli->get_nickName(), _name, "-", "i", "No more need to be invited to join this channel.");
	sendToAllClients(msg);
};

/* ************************************************************************** */
// HANDLE TOPIC FLAG
/* ************************************************************************** */

void			Channel::topicModeOn(Client* cli)
{
	_topicModeOn = true;
	std::string msg = RPL_MODE(cli->get_nickName(), _name, "+", "t", "Topic cmd reserved for operators on this channel.");
	sendToAllClients(msg);	
};

void			Channel::topicModeOff(Client* cli)
{
	_topicModeOn = false;
	std::string msg = RPL_MODE(cli->get_nickName(), _name, "-", "t", "Topic cmd enabled for every user on this channel.");
	sendToAllClients(msg);	
};