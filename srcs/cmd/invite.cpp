/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 13:32:13 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/17 02:50:45 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Server.hpp"
# include "Channel.hpp"

void	Server::cmd_invite(Client *cli, t_message *msg)
{
	if (0
		|| !expect_N_Params(msg, 2)
	) { return; }
	
	std::string	chan, user, response;

	user = msg->params[0];
	chan = msg->params[1];

	if (chan[0] == '#' || chan[0] == '&')
		chan.erase(0,1);

	t_channel_map::iterator it = _channels.find(chan);

	if (it == _channels.end())
	{
		response = ERR_NOSUCHCHANNEL(cli->get_nickName(), chan, "This channel doesn't exist.");
		cli->setBufferOut(response);
		return ;
	}
	
	Channel *chanRef = it->second;
	Client	*userRef = getRefClientByNick(user);
	
	if (!userRef)
	{
		response = ERR_NOSUCHNICK(cli->get_nickName(), user, "The user you try to invite doesn't exist.");
		cli->setBufferOut(response);
		return ;
	}
	chanRef->inviteCmd(cli, userRef);
}

void	Channel::inviteCmd(Client *sender, Client *receiver)
{
	t_clients_map::iterator it;
	bool					s_ok = false, r_ok = true; /* need_ops = false */

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
		response = ERR_NOTONCHANNEL(sender->get_nickName(), _name, "You're not on this channel.");
			sender->setBufferOut(response);
		return ;
	}
	
	if (!r_ok)
	{
		response = ERR_USERONCHANNEL(sender->get_nickName(), _name, "User already member of this channel");
		sender->setBufferOut(response);
		return ;
	}

	if (_limitModeOn)
	{
		if (_clients.size() + 1 > _limit)
		{
			response = ERR_CHANNELISFULL(sender->get_nickName(), _name, "Cannot invite in this channel, it is full.");
			sender->setBufferOut(response);
			return ;
		}
	}

	if (_inviteModeOn || _keyModeOn)
	{
		std::vector<Client*>::iterator jt;

		for (jt = _operators.begin(); jt != _operators.end(); jt++)
		{
			if ((*jt)->get_userName() == sender->get_userName())
			{
				response = RPL_INVITE(sender->get_nickName(), receiver->get_nickName(), _name);
				sender->setBufferOut(response);	

				if (!checkInvited(receiver))
					_invited.push_back(receiver);
				return ;
			}
		}
		response = ERR_CHANOPRIVSNEEDED(sender->get_nickName(), _name);
		sender->setBufferOut(response);
	}
	else
	{
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
			return (true);
	}
	return (false);
};