/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:23:57 by tmejri            #+#    #+#             */
/*   Updated: 2024/03/11 16:24:58 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP

# define CLIENT_HPP

# include <string>

class Client
{
private:
/* 	unsigned int	_port; */
	int				_fd;
	std::string		_ipAdd;
/* 	std::string		_password;
	sockaddr_in		_sockAddr;
	int				_sockfd; */
	/* int				_connection[5];
	struct epoll_event event, events[MAX_EVENTS];
	int 			_epoll_fd; */
	
public:
	Client();
	//Client(unsigned int port, std::string password);
	~Client();

	void		set_fd(int fd);
	int			get_fd();
	void		set_ip(std::string ipAdd);
	std::string	get_ip();


};


#endif