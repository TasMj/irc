/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:23:57 by tmejri            #+#    #+#             */
/*   Updated: 2024/04/06 19:11:48 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/******************************************************************************/
/*                                 Includes                                   */
/******************************************************************************/
# include <string>
# include <sstream>
# include <fstream>
# include <unistd.h>
# include "./Transmission.hpp"
# include "Server.hpp"

/******************************************************************************/
/*                                  Class                                     */
/******************************************************************************/

class Transmission;
class Server;

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
	Server				*_server;
	// std::vector<char>	_canalOperator; //operateurs de canaux -> droit que le client possede sur un canal
	
	// std::string			_msg;
	// int					_flagMsg;

	//Transmission			*_trans;
	std::string				_bufferOut;
	bool					_flagIO;
	
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
	void		set_Server(Server *server);
	Server*		get_Server();
	bool		getFlagIO();
	void		setFlagIO(bool status);
	void		remove();
	//Transmission getTransmission();
	// void		prepareMsgToClient(Client *cli);
	void		setUpTransmission(Client *cli, std::string msg, int fdDest);

	// unsigned int	receiveMsg();

};

// class Transmission;

