/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:26:00 by tmejri            #+#    #+#             */
/*   Updated: 2024/04/13 18:06:01 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Client.hpp"

Client::Client()
	: _bufferOut("")
	, _isOps(false)
	, _login(UNSET)
{
	//_login = (t_login)UNSET;
}

Client::~Client()
{

}

Server*	Client::get_Server()
{
	return(this->_server);
}

void	Client::set_Server(Server *server)
{
	this->_server = server;
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

bool		Client::getIsOps()
{
	return (this->_isOps);
}

void	Client::setIsOps(bool status)
{
	this->_isOps = status;
}

void		Client::setBufferOut(std::string buff) {
	_bufferOut.append(buff);
};


bool	Client::read_stream(std::deque<t_message*>& output) {
	char buff[1024] = { 0 };
	ssize_t bytes = recv(_fd, buff, sizeof(buff) - 1, 0);

	if (bytes <= 0) {
		close(_fd);
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
	std::string* response = channel->join(this, password);
	if (response) {
		_bufferOut.append(*response);
		std::cout << GRE << *response << " " << _bufferOut << WHI << std::endl;
	}
	else
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
	
		welcome = ":" + prefixe + " 001 " + get_nickName() + ": Si si la famille !\n";
		get_Server()->setUpTransmission(this, welcome, get_fd());
    	get_Server()->prepareMsgToClient(this);
		//send welcome
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

