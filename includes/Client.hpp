/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:23:57 by tmejri            #+#    #+#             */
/*   Updated: 2024/03/20 17:06:26 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP

# define CLIENT_HPP

# include <string>
# include <map>
# include <vector>
# include <deque>
# include <iostream>

class Client
{
private:
/* 	unsigned int	_port; */
	int						_fd;
	std::string				_ipAdd;
	std::multimap<std::string, std::string>	_cmd;
	std::string				_buff;
/* 	std::string		_password;
	sockaddr_in		_sockAddr;
	int				_sockfd; */
	/* int				_connection[5];
	struct epoll_event event, events[MAX_EVENTS];
	int 			_epoll_fd; */

	// std::string		_nickName;
	
public:
	Client();
	//Client(unsigned int port, std::string password);
	~Client();

	void		set_fd(int fd);
	int			get_fd();
	void		set_ip(std::string ipAdd);
	std::string	get_ip();
	void		set_cmd(std::string);
	void		get_cmd();
	void		set_buff(std::string);
};


#endif