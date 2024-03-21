/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:26:00 by tmejri            #+#    #+#             */
/*   Updated: 2024/03/21 22:57:31 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Client.hpp"

Client::Client()
{
	// init_nickName("NickDefault_", get_fd());
	// set_nickName("NickDefault_");
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
