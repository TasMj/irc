/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:23:57 by tmejri            #+#    #+#             */
/*   Updated: 2024/03/26 23:51:05 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

/******************************************************************************/
/*                                 Includes                                   */
/******************************************************************************/
# include <string>
# include <sstream>

/******************************************************************************/
/*                                  Class                                     */
/******************************************************************************/

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

	std::string			_nickName;
	std::string			_userName;
	// std::vector<char>	_canalOperator; //operateurs de canaux -> droit que le client possede sur un canal
	
	
public:
	Client();
	//Client(unsigned int port, std::string password);
	~Client();

	void		set_fd(int fd);
	int			get_fd();
	void		set_ip(std::string ipAdd);
	std::string	get_ip();
	void		set_nickName(std::string nick);
	void		init_nickName(std::string nick, int fd);
	std::string	get_nickName();
	void		set_userName(std::string user);
	std::string	get_userName();

};


#endif