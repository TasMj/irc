/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:23:57 by tmejri            #+#    #+#             */
/*   Updated: 2024/02/26 16:25:21 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP

# define CLIENT_HPP

# include "Server.hpp"

class Client
{
private:
	unsigned int	_port;
	std::string		_password;
	sockaddr_in		_sockAddr;
	int				_sockfd;
	Client();
	int				_connection[5];
	struct epoll_event event, events[MAX_EVENTS];
	int 			_epoll_fd;
	
public:
	Client(unsigned int port, std::string password);
	~Client();


};


#endif