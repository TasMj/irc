/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 18:28:10 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/13 20:18:38 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/Server.hpp"
# include "../../includes/Channel.hpp"

/* ************************************************************************** */
// UTILS
/* ************************************************************************** */

static void	modeError(char c)
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
};

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
				modeError('o');
			else if (op == '+')
				chan->addOperator(msg->params[n], cli, false);
			else
				chan->removeOperator(msg->params[n], cli);
			n++;
		}
		if (msg->params[1][i] == 'k')
		{
			if (n >= msg->params.size() && op == '+')
				modeError('k');
			else if (op == '+')
			{
				chan->modPassword(msg->params[n]);
				n++;
			}
			else
				chan->removePassword();
		}
		if (msg->params[1][i] == 'l')
		{
			if (n >= msg->params.size() && op == '+')
				modeError('l');
			else if (op == '+')
			{
				chan->modLimit(msg->params[n]);
				n++;
			}
			else
				chan->removeLimit();
		}
		if (msg->params[1][i] == 'i')
		{
			if (op == '+')
				chan->inviteModeOn();
			else
				chan->inviteModeOff();
		}
		if (msg->params[1][i] == 't')
		{
			if (op == '+')
				chan->topicModeOn();
			else
				chan->topicModeOff();
		}
	}
	
	std::cout << "Channel mode " << cli->get_nickName() << " " << msg->command << chan->getName() << std::endl;
}

void	Server::cmd_mode(Client* cli, t_message* msg) {
	
	std::map<std::string, Channel *>::iterator	it;

	it = _channels.find(msg->params[0]);
	//std::cout << "Channel : " << this->_channels[msg->params[0]] << std::endl << "Client : " << this->getRefClientByName(msg->params[0])->get_userName() << std::endl;
	if (it != _channels.end())
	{
		if (!it->second->checkOperator(cli->get_userName()))
		{
			cli->get_Server()->setUpTransmission(cli, ":localhost You need to be an Operator to use MODE command.\n", cli->get_fd());
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
		if (msg->params[0][0] == '#')
		{
			cli->get_Server()->setUpTransmission(cli, ":localhost Please specify the flag(s) you want to change ([+|-]i|t|k|o|l).\n", cli->get_fd());
			cli->get_Server()->prepareMsgToClient(cli);
		}
		else
		{	
			cli->get_Server()->setUpTransmission(cli, ":localhost Please specify a valid channel for MODE command.\n", cli->get_fd());
			cli->get_Server()->prepareMsgToClient(cli);
		}
	}
}

/* ************************************************************************** */
// HANDLE OPERATOR FLAG
/* ************************************************************************** */

bool			Channel::checkOperator(std::string name)
{
	for (size_t i = 0; i < _operators.size(); i++)
	{
		if (_operators[i] == name)
		{
			std::cout << name << " is an operator of this channel." << std::endl;
			return (true);
		}
	}
	std::cout << name << " is not an operator of this channel." << std::endl;
	return (false);
};

void			Channel::addOperator(std::string name, Client* cli, bool creation)
{
	if (!cli->get_Server()->getRefClientByName(name))
	{
		std::cout << name << " : this user doesn't exist." << std::endl;
		return ;
	}
	
	if (!creation)
	{
		t_clients_map::iterator it;
		
		for (it = _clients.begin(); it != _clients.end(); it++)
		{
			if (it->second->get_userName() == name)
				break ;
		}
		
		if (it == _clients.end())
		{
			std::cout << name << " : this user is not in this channel." << std::endl;
			return ;
		}
	}
	
	for (size_t i = 0; i < _operators.size(); i++)
	{
		if (_operators[i] == name)
		{
			std::cout << name << " is already an operator of this channel." << std::endl;
			return ;
		}
	}
	std::cout << name << " is a new operator of this channel." << std::endl;
	_operators.push_back(name);
};

void			Channel::removeOperator(std::string name, Client* cli)
{
	if (!cli->get_Server()->getRefClientByName(name))
	{
		std::cout << name << " : this user doesn't exist." << std::endl;
		return ;
	}
	for (size_t i = 0; i < _operators.size(); i++)
	{
		if (_operators[i] == name)
		{
			_operators[i].erase();
			std::cout << name << " is no more an operator of this channel." << std::endl;
			return ;
		}
	}
	
	std::cout << name << " was not an operator of this channel." << std::endl;
};

/* ************************************************************************** */
// HANDLE PASSWORD FLAG
/* ************************************************************************** */

void			Channel::modPassword(std::string password)
{
	//if (!(_mode & (t_mode)K))
	
	_mode = (t_mode)_mode | (t_mode)K; 
	if ((_mode & (t_login)K))
		std::cout << "le flag a ete ajoute !" << std::endl;
	std::cout << password << " is the new password of this channel." << std::endl;
};

void			Channel::removePassword()
{
	_mode = (t_mode)_mode & (t_mode)K; 
	if (!(_mode & (t_login)K))
		std::cout << "le flag a ete enleve !" << std::endl;
	std::cout << "this channel has no more password." << std::endl;
};

/* ************************************************************************** */
// HANDLE LIMIT FLAG
/* ************************************************************************** */

void			Channel::modLimit(std::string limit)
{
	int	n_lim;
	
	if (limit.find_first_not_of("0123456789") != std::string::npos)
		return (modeError('l'));
		
	n_lim = atoi(limit.c_str());
	_limit = n_lim;
	_mode = (t_mode)_mode | (t_mode)L; 
	std::cout << limit << "is the maximum number of user allowed in this channel." << std::endl;
};

void			Channel::removeLimit()
{
	_mode = (t_mode)_mode & (t_mode)L;
	std::cout << "This channel has no more user limit." << std::endl;
};

/* ************************************************************************** */
// HANDLE INVITE FLAG
/* ************************************************************************** */

void			Channel::inviteModeOn()
{
	_mode = (t_mode)_mode | (t_mode)I; 
	std::cout << "This channel is now accessible only through invitation." << std::endl;
};

void			Channel::inviteModeOff()
{
	_mode = (t_mode)_mode & (t_mode)I; 
	std::cout << "No more need to be invited to join this channel." << std::endl;
};

/* ************************************************************************** */
// HANDLE TOPIC FLAG
/* ************************************************************************** */

void			Channel::topicModeOn()
{
	_mode = (t_mode)_mode | (t_mode)T; 
	std::cout << "Topic cmd reserved for operqtors on this channel." << std::endl;
};

void			Channel::topicModeOff()
{
	_mode = (t_mode)_mode & (t_mode)T; 
	std::cout << "Topic cmd enabled for everybody on this channel." << std::endl;
};