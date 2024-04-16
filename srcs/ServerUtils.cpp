/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:26:50 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/16 17:12:58 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

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

Client* Server::getRefClientByFd(int fd)
{
	std::deque<Client>::iterator	it = _clients.begin();
	std::deque<Client>::iterator	itend = _clients.end();

	while (it != itend)
	{
		if (it->get_fd() == fd)
			return (&(*it));
		it++;
	}
	return (NULL);
}

Client* Server::getRefClientByName(std::string name)
{
	std::deque<Client>::iterator	it = _clients.begin();
	std::deque<Client>::iterator	itend = _clients.end();

	while (it != itend)
	{
		if (it->get_userName() == name)
			return (&(*it));
		it++;
	}
	return (NULL);
}

Client* Server::getRefClientByNick(std::string nick)
{
	std::deque<Client>::iterator	it = _clients.begin();
	std::deque<Client>::iterator	itend = _clients.end();

	while (it != itend)
	{
		if (it->get_nickName() == nick)
			return (&(*it));
		it++;
	}
	return (NULL);
}