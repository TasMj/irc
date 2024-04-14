/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 13:32:13 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/14 17:59:01 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/Server.hpp"
# include "../../includes/Channel.hpp"

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
	bool					s_ok = false, r_ok = true;
	
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

	if (_mode | (t_mode)I)
	{
		std::vector<Client*>::iterator jt;

		for (jt = _operators.begin(); jt != _operators.end(); jt++)
		{
			if ((*jt)->get_userName() == sender->get_userName())
			{
				std::cout << receiver->get_nickName() << " join " << _name << std::endl;
				join(receiver, NULL, true);
				return ;
			}
		}
		std::cout << "You need to be operator on this channel to invite new members." << std::endl;
	}
	else
	{
		std::cout << receiver->get_nickName() << " join " << _name << std::endl;
		join(receiver, NULL, true);
	}
}