/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:26:00 by tmejri            #+#    #+#             */
/*   Updated: 2024/03/22 22:35:08 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Client.hpp"

Client::Client()
{

};

Client::~Client()
{
	
};

void	Client::set_fd(int fd)
{
	this->_fd = fd;
};

void	Client::set_ip(std::string ip)
{
	this->_ipAdd = ip;
};

int		Client::get_fd()
{
	return (this->_fd);
}

std::string Client::get_ip()
{
	return (this->_ipAdd);
}

void	Client::init_nickName(std::string nick, int fd)
{
	std::stringstream ss;
	ss << fd;
	 
	std::string fd_str = ss.str();
	
	this->_nickName = nick.append(fd_str);
};

void	Client::set_nickName(std::string nick)
{
	this->_nickName = nick;
};


std::string Client::get_nickName()
{
	return (this->_nickName);
}

void	Client::set_userName(std::string user)
{
	this->_userName = user;
};

std::string Client::get_userName()
{
	return (this->_userName);
}
