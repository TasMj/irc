/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:26:00 by tmejri            #+#    #+#             */
/*   Updated: 2024/04/07 12:49:46 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Client.hpp"

Client::Client()
{
	// _trans = new Transmission();
	// std::cout << PUR << "CLIENT " << WHI << std::endl;
}

Client::~Client()
{
	// std::cout << PUR << "DESTROY CLIENT" << WHI << std::endl;
	// delete _trans;

}

Server*	Client::get_Server()
{
	return(this->_server);
}

void	Client::set_Server(Server *server)
{
	this->_server = server;
}

void	Client::remove()
{
	size_t i = 0;
	std::vector<Client>::iterator it;
	std::vector<pollfd>::iterator jt;
	for (it = this->_server->getClient().begin(); it != this->_server->getClient().end(); ++it)
	{
		if (it->get_fd() == this->get_fd())
			break ;
		i++;
	}
	close(it->get_fd());
	this->_server->getClient().erase(it);
	for (jt = this->_server->getPollfds().begin(); jt != this->_server->getPollfds().end(); ++jt)
	{
		if (it->get_fd() == this->get_fd())
			break ;
		i++;
	}
	close(jt->events);
	this->_server->getPollfds().erase(jt);
	close(this->_fd);
	
}

void	Client::set_fd(int fd)
{
	this->_fd = fd;
}

void	Client::set_ip(std::string ip)
{
	this->_ipAdd = ip;
}

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
}

void	Client::set_nickName(std::string nick)
{
	this->_nickName = nick;
}

std::string Client::get_nickName()
{
	return (this->_nickName);
}

void	Client::set_userName(std::string user)
{
	this->_userName = user;
}

std::string Client::get_userName()
{
	return (this->_userName);
}

bool		Client::getFlagIO()
{
	return (this->_flagIO);
}

void	Client::setFlagIO(bool status)
{
	this->_flagIO = status;
}

std::string	Client::getBufferOut()
{
	return (this->_bufferOut);
};

void		Client::setBufferOut(std::string buff)
{
	this->_bufferOut = buff;
};
