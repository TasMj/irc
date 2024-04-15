/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 18:28:10 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/16 00:15:34 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/Server.hpp"
# include "../../includes/Channel.hpp"

/* ************************************************************************** */
// UTILS
/* ************************************************************************** */

/* static void	modeError(char c)
{
	if (c == 'o')
	{
		std::cout << "Flag 'o' for command Mode need a user as parameter"<< std::endl;
	}
	if (c == 'k')
	{
		std::cout << "Flag 'k' for command Mode need a password as parameter"<< std::endl;
	}
	if (c == 'l')
	{
		std::cout << "Flag 'l' for command Mode need a number as parameter"<< std::endl;
	}
}; */

/* ************************************************************************** */
// MODE COMMAND LOGIC
/* ************************************************************************** */

static void	cmd_mode_chan(Client* cli, t_message* msg, Channel* chan) {
	//bool		i = false, t = false, k = false, o = false, l = false;
	std::string	userName;
	std::string	password;
	//size_t		limit;
	//size_t		nParamsNeeded = n_params_wanted(msg->params[1].c_str());
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
				cli->get_Server()->setUpTransmission(cli, ERR_NEEDMOREPARAMS(cli->get_nickName(), "MODE", "Please provide a username (o).") , cli->get_fd());
    			cli->get_Server()->prepareMsgToClient(cli);
			}
			else if (op == '+')
				chan->addOperator(cli, cli->get_Server()->getRefClientByName(msg->params[n]), false);
			else
				chan->removeOperator(cli, cli->get_Server()->getRefClientByName(msg->params[n]));
			n++;
		}
		if (msg->params[1][i] == 'k')
		{
			if (n >= msg->params.size() && op == '+')
			{
				cli->get_Server()->setUpTransmission(cli, ERR_NEEDMOREPARAMS(cli->get_nickName(), "MODE", "Please provide an alphanum password (+k).") , cli->get_fd());
    			cli->get_Server()->prepareMsgToClient(cli);
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
				cli->get_Server()->setUpTransmission(cli, ERR_NEEDMOREPARAMS(cli->get_nickName(), "MODE", "Please provide a numeric limit (+l).") , cli->get_fd());
    			cli->get_Server()->prepareMsgToClient(cli);
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
	
	std::cout << "Channel mode " << cli->get_nickName() << " " << msg->command << chan->getName() << std::endl;
}

void	Server::cmd_mode(Client* cli, t_message* msg) {
	
	std::map<std::string, Channel *>::iterator	it;
	if (msg->params[0][0] == '#')
		msg->params[0].erase(0,1);

	it = _channels.find(msg->params[0]);
	//std::cout << "Channel : " << this->_channels[msg->params[0]] << std::endl << "Client : " << this->getRefClientByName(msg->params[0])->get_userName() << std::endl;
	if (it != _channels.end())
	{
		if (!it->second->checkOperator(cli))
		{
			cli->get_Server()->setUpTransmission(cli, ERR_CHANPRIVSNEEDED(cli->get_nickName(), it->second->getName()), cli->get_fd());
    		cli->get_Server()->prepareMsgToClient(cli);
			return ;
		}
		if (msg->params[1].find_first_not_of("+-itkol", 0) != std::string::npos)
		{
			cli->get_Server()->setUpTransmission(cli, ":localhost Flags are incorect ([+|-]i|t|k|o|l).\n", cli->get_fd());
			cli->get_Server()->prepareMsgToClient(cli);
		}
		else
			cmd_mode_chan(cli, msg, it->second);
	}
	else
	{
		cli->get_Server()->setUpTransmission(cli, ":localhost Please specify a valid channel for MODE command.\n", cli->get_fd());
		cli->get_Server()->prepareMsgToClient(cli);
	}
}

/* ************************************************************************** */
// HANDLE OPERATOR FLAG
/* ************************************************************************** */

bool			Channel::checkOperator(Client* cli)
{
	if (!cli)
		return (false);
	for (size_t i = 0; i < _operators.size(); i++)
	{
		if (_operators[i]->get_userName() == cli->get_userName())
		{
			std::cout << cli->get_userName() << " is an operator of this channel." << std::endl;
			return (true);
		}
	}
	std::cout << cli->get_userName() << " is not an operator of this channel." << std::endl;
	return (false);
};

void			Channel::addOperator(Client* sender, Client* receiver, bool creation)
{
	std::string msg;
	/* if (!cli->get_Server()->getRefClientByName(name))
	{
		std::cout << name << " : this user doesn't exist." << std::endl;
		return ;
	} */
	if (!receiver)
	{
		std::cout << "This user doesn't exist." << std::endl;
		return ;
	}
		
	if (!creation)
	{
		t_clients_map::iterator it;
		
		for (it = _clients.begin(); it != _clients.end(); it++)
		{
			if (it->second->get_userName() == receiver->get_userName())
				break ;
		}
		
		if (it == _clients.end())
		{
			std::cout << receiver->get_userName() << " : this user is not in this channel." << std::endl;
			return ;
		}
	}
	
	for (size_t i = 0; i < _operators.size(); i++)
	{
		if (_operators[i]->get_userName() == receiver->get_userName())
		{
			std::cout << receiver->get_userName() << " is already an operator of this channel." << std::endl;
			return ;
		}
	}
	msg = receiver->get_userName() + " is a new operator of this channel.";
	sender->get_Server()->sendToAll(sender, RPL_MODE(sender->get_nickName(), _name, "+", "o", msg), _clients);
	_operators.push_back(receiver);
};

void			Channel::removeOperator(Client* sender, Client* receiver)
{
	std::string msg;
	if (!receiver)
		return ;
	/* if (!cli->get_Server()->getRefClientByName(cli->get_userName()))
	{
		std::cout << cli->get_userName() << " : this user doesn't exist." << std::endl;
		return ;
	} */
	std::vector<Client*>::iterator it;
	for (it = _operators.begin(); it != _operators.end(); it++)
	{
		if ((*it)->get_userName() == receiver->get_userName())
		{
			_operators.erase(it);
			msg = receiver->get_userName() + " is no more an operator of this channel.";
			sender->get_Server()->sendToAll(sender, RPL_MODE(sender->get_nickName(), _name, "-", "o", msg), _clients);
			return ;
		}
	}
	
	std::cout << receiver->get_userName() << " was not an operator of this channel." << std::endl;
};

/* ************************************************************************** */
// HANDLE PASSWORD FLAG
/* ************************************************************************** */

void			Channel::modPassword(std::string password, Client* cli)
{
	std::string msg;
	//if (!(_mode & (t_mode)K))
	if (_keyModeOn)
	{
		std::cout << "This channel already ask for a password to enter." << std::endl;
		if (_password)
			_password->erase();
		std::string *pwd = new std::string(password);
		_password = pwd;
		delete pwd;
	}
	else
		_keyModeOn = true;
		//_mode = (t_mode)_mode | (t_mode)KEY; 
	/* if ((_mode & (t_login)K))
		std::cout << "le flag a ete ajoute !" << std::endl; */
	msg = password + " is the new password of this channel.";
	cli->get_Server()->sendToAll(cli, RPL_MODE(cli->get_nickName(), _name, "+", "k", msg), _clients);
	
};

void			Channel::removePassword(Client* cli)
{
	if (!_keyModeOn)
	{
		std::cout << "This channel already doesn't have any password." << std::endl;
		return ;
	}
	else
		_keyModeOn = false;	
		//_mode = (t_mode)_mode & (t_mode)KEY; 
	/* if (!(_mode & (t_login)K))
		std::cout << "le flag a ete enleve !" << std::endl; */
	cli->get_Server()->sendToAll(cli, RPL_MODE(cli->get_nickName(), _name, "-", "k", "This channel has no more password."), _clients);
	std::cout << "this channel has no more password." << std::endl;
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
		cli->get_Server()->setUpTransmission(cli, ERR_NEEDMOREPARAMS(cli->get_nickName(), "MODE", "Need a numeric limit (+l).") , cli->get_fd());
    	cli->get_Server()->prepareMsgToClient(cli);
		return ;
	}
		
	n_lim = atoi(limit.c_str());
	_limit = (size_t)n_lim;
	//_mode = (t_mode)_mode | (t_mode)LIMIT; 
	_limitModeOn = true;
	msg = limit + " is the maximum number of user allowed in this channel.";
	cli->get_Server()->sendToAll(cli, RPL_MODE(cli->get_nickName(), _name, "+", "l", msg), _clients);
};

void			Channel::removeLimit(Client* cli)
{
	//_mode = (t_mode)_mode & (t_mode)LIMIT;
	_limitModeOn = false;
	cli->get_Server()->sendToAll(cli, RPL_MODE(cli->get_nickName(), _name, "-", "l", "This channel has no more user limit."), _clients);
	std::cout << "This channel has no more user limit." << std::endl;
};

/* ************************************************************************** */
// HANDLE INVITE FLAG
/* ************************************************************************** */

void			Channel::inviteModeOn(Client* cli)
{
	//_mode = (t_mode)_mode | (t_mode)INVITE; 
	_inviteModeOn = true;
	cli->get_Server()->sendToAll(cli, RPL_MODE(cli->get_nickName(), _name, "+", "i", "This channel is now accessible only through invitation."), _clients);
	std::cout << "This channel is now accessible only through invitation." << std::endl;
};

void			Channel::inviteModeOff(Client* cli)
{
	//_mode = (t_mode)_mode & (t_mode)INVITE; 
	_inviteModeOn = false;
	cli->get_Server()->sendToAll(cli, RPL_MODE(cli->get_nickName(), _name, "-", "i", "No more need to be invited to join this channel."), _clients);
	std::cout << "No more need to be invited to join this channel." << std::endl;
};

/* ************************************************************************** */
// HANDLE TOPIC FLAG
/* ************************************************************************** */

void			Channel::topicModeOn(Client* cli)
{
	//_mode = (t_mode)_mode | (t_mode)TOPIC;
	_topicModeOn = true;
	cli->get_Server()->sendToAll(cli, RPL_MODE(cli->get_nickName(), _name, "+", "t", "Topic cmd reserved for operators on this channel."), _clients);
	std::cout << "Topic cmd reserved for operqtors on this channel." << std::endl;
};

void			Channel::topicModeOff(Client* cli)
{
	//_mode = (t_mode)_mode & (t_mode)TOPIC;
	_topicModeOn = false;
	cli->get_Server()->sendToAll(cli, RPL_MODE(cli->get_nickName(), _name, "-", "t", "Topic cmd enabled for every user on this channel."), _clients);
	std::cout << "Topic cmd enabled for everybody on this channel." << std::endl;
};