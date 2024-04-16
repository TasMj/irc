/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:26:00 by tmejri            #+#    #+#             */
/*   Updated: 2024/04/16 20:00:13 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(int fd, Server* server)
	: _fd(fd)
	, _server(server)
	, _bufferOut("")
	, _login(UNSET)
{
	std::cout << "New Client: " << _fd << std::endl;
}

Client::~Client() {
	std::map<std::string, Channel*>::iterator	it;
	for (it = _channels.begin(); it != _channels.end(); it++)
		it->second->removeClient(this);
}

Server*		Client::get_Server()
{
	return(this->_server);
}

int			Client::get_fd()
{
	return (this->_fd);
}

void		Client::set_nickName(std::string nick)
{
	this->_nickName = nick;
}

std::string Client::get_nickName()
{
	return (this->_nickName);
}

void		Client::set_userName(std::string user)
{
	this->_userName = user;
}

std::string Client::get_userName()
{
	return (this->_userName);
}

void		Client::setBufferOut(std::string buff) {
	_bufferOut.append(buff);
};

bool	Client::read_stream(std::deque<t_message*>& output) {
	char buff[1024] = { 0 };
	ssize_t bytes = recv(_fd, buff, sizeof(buff) - 1, 0);

	if (bytes <= 0) {
		_server->removeClient(*this);
		return (false);
	}
	_bufferIn.append(buff);
	
	t_message* tmp = parse_message(_bufferIn);
	while (tmp) {
		output.push_back(tmp);
		tmp = parse_message(_bufferIn);
	}
	return (true);
}

void	Client::write_stream(void) {
	if (_bufferOut.empty())
		return; 
	std::cout << YEL << _bufferOut << WHI << std::endl;
	size_t bytes = send(_fd, _bufferOut.c_str(), _bufferOut.size(), 0);
	_bufferOut.erase(0, bytes);
}

void	Client::join(Channel* channel, std::string* password) {
	if (channel->join(this, password))
		_channels.insert(channel->asPair());	
}

void	Client::isWelcomed(std::string flag) {
	if (_login == OK) {
		return;
	}
	if (flag.compare("USER") == 0)
		_login = _login | (t_login)USER;
	else if (flag.compare("NICK") == 0)
		_login = _login | (t_login)NICK;
	else if (flag.compare("PASS") == 0)
		_login = _login | (t_login)PASS;
	
	if (_login == OK) {
		std::string	welcome;
		std::string	prefixe = PREFIXE;
	
		setBufferOut(RPL_WELCOME(this));
		setBufferOut(RPL_YOURHOST());
		setBufferOut(RPL_CREATED());
		setBufferOut(RPL_MYINFO());
	}
}

t_login			Client::getLogStatus()
{
	return (_login);
};

t_login			operator|(t_login oldFlag, t_login newFlag)
{
	return ((t_login)((int)oldFlag | (int)newFlag));
}

