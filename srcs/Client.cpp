/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:26:00 by tmejri            #+#    #+#             */
/*   Updated: 2024/03/20 17:07:13 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Client.hpp"

Client::Client()
{
    
};

Client::~Client(){};

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

void	Client::set_buff(std::string nBuff)
{
	this->_buff = this->_buff + nBuff;
}

std::deque<std::string>	split(std::string str, std::string separator)
{
	std::deque<std::string> cmd;
	std::string a;
	
	size_t pos_start = 0;
	size_t pos_end = 0;
	while ((pos_end = str.find(separator)) != std::string::npos)
	{
		a = str.substr(pos_start, pos_end - pos_start);
		pos_end += separator.length();
		pos_start = pos_end;
		cmd.push_back(a);
	}
	return(cmd);
}

void	Client::set_cmd(std::string cmdline)
{
	std::string							cmd;
	std::string							args;
	std::deque<std::string>			split_cmd;

	split_cmd = split(cmdline, " ");
	args = split_cmd[0];
	split_cmd.pop_front();
	while (split_cmd.size())
	{
		args += split_cmd[0] + ' ';
		split_cmd.pop_front();
	}
	std::cout << "glouglou" << std::endl << cmd << std::endl << args << std::endl;
	//std::map<std::string, std::string>	input{cmd, args};
	this->_cmd.insert(std::pair<std::string, std::string>(cmd, args));
}

void	Client::get_cmd()
{
	while (this->_cmd.size())
	{
		
	}
}

// void	Client::set_Nick(std::string Nick)
// {
// 	this->_nickName = Nick;
// };