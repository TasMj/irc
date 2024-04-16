/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 13:32:13 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/16 17:30:51 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Server.hpp"
# include "Channel.hpp"

void	Server::cmd_invite(Client *cli, t_message *msg)
{
	if (0
		|| !expect_N_Params(msg, 2)
	) { return; }
	
	std::string	chan, user;

	user = msg->params[0];
	chan = msg->params[1];

	if (chan[0] == '#' || chan[0] == '&')
		chan.erase(0,1);

	t_channel_map::iterator it = _channels.find(chan);

	if (it == _channels.end())
	{
		std::cout << "This channel doesn't exist." << std::endl;
		return ;
	}
	
	Channel *chanRef = it->second;//cli->get_Server()->getRefChannelByName(chan);
	Client	*userRef = getRefClientByNick(user);
	
	if (!userRef)
	{
		std::cout << "The user you try to invite doesn't exist." << std::endl;
		return ;
	}
	chanRef->inviteCmd(cli, userRef);
}

void	Channel::inviteCmd(Client *sender, Client *receiver)
{
	t_clients_map::iterator it;
	bool					s_ok = false, r_ok = true; /* need_ops = false */
	std::string				password;
	std::string				response;
	
	for (it = _clients.begin(); it != _clients.end(); it++)
	{
		if (it->second->get_nickName() == sender->get_nickName())
			s_ok = true;
		if (it->second->get_nickName() == receiver->get_nickName())
			r_ok = false;
	}
	

	if (!s_ok)
	{
		std::cout << "You need to be a member of the channel to invite a user." << std::endl;
		return ;
	}
	
	if (!r_ok)
	{
		std::cout << "The user you try to invite is already a member of this channel." << std::endl;
		return ;
	}

	if (_limitModeOn/* _mode & (t_mode)LIMIT */)
	{
		if (_clients.size() + 1 > _limit)
		{
			response = ERR_CHANNELISFULL(sender->get_nickName(), _name, "Cannot invite in this channel, it is full.");
			sender->setBufferOut(response);
		}
	}

	if (_keyModeOn/* _mode & (t_mode)KEY */)
	{
		std::cout << "KEY PAS ACTIF" << std::endl;
		password = 	_password->c_str();
		//need_ops = true;
		std::cout << "KEY ACTIF" << std::endl;
	}

	if (/* (_mode & (t_mode)INVITE) */_inviteModeOn || _keyModeOn /* need_ops */)
	{
		std::vector<Client*>::iterator jt;

		std::cout << "INVITE ACTIF" << std::endl;
		for (jt = _operators.begin(); jt != _operators.end(); jt++)
		{
			if ((*jt)->get_userName() == sender->get_userName())
			{
				if (!password.empty())
				{
					response = "Invitation send to " + receiver->get_nickName() +", password is : " + password;
					response = RPL_INVITE(sender->get_nickName(), receiver->get_nickName(), _name);
					sender->setBufferOut(response);
				}
				else	
					std::cout << receiver->get_nickName() << " join " << _name << std::endl;
				if (!checkInvited(receiver))
					_invited.push_back(receiver);
				return ;
			}
		}
		response = ERR_CHANPRIVSNEEDED(sender->get_nickName(), _name);
		sender->setBufferOut(response);
	}
	else
	{
		response = " Invitation send to " + receiver->get_nickName();
		response = RPL_INVITE(sender->get_nickName(), receiver->get_nickName(), _name);
		sender->setBufferOut(response);
	}
}

bool			Channel::checkInvited(Client* cli)
{
	if (!cli)
		return (false);
	for (size_t i = 0; i < _invited.size(); i++)
	{
		if (_invited[i]->get_nickName() == cli->get_nickName())
		{
			std::cout << cli->get_nickName() << " is invited in this channel." << std::endl;
			return (true);
		}
	}
	std::cout << cli->get_nickName() << " is not invited in this channel." << std::endl;
	return (false);
};