/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:23:57 by tmejri            #+#    #+#             */
/*   Updated: 2024/04/11 17:35:05 by aclement         ###   ########.fr       */
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
# include "Message.hpp"
# include "Server.hpp"

/******************************************************************************/
/*                                  Class                                     */
/******************************************************************************/

class Transmission;
class Server;

class Client
{
private:
	int				_fd;
	std::string		_ipAdd;
	std::string		_nickName;
	std::string		_userName;
	Server			*_server;
	std::string		_bufferIn, _bufferOut;
	bool			_flagIO;
	
public:
	Client();
	~Client();

	void			set_fd(int fd);
	int				get_fd();
	void			set_ip(std::string ipAdd);
	std::string		get_ip();
	void			set_nickName(std::string nick);
	void			init_nickName(std::string nick, int fd);
	std::string		get_nickName();
	void			set_userName(std::string user);
	std::string		get_userName();
	void			set_Server(Server *server);
	Server*			get_Server();
	bool			getFlagIO();
	void			setFlagIO(bool status);
	std::string&	getBufferOut();
	void			setBufferOut(std::string buff);

	bool			receive(t_message** msg);
	void			remove();
};

