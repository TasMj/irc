/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:23:57 by tmejri            #+#    #+#             */
/*   Updated: 2024/04/12 13:09:37 by tmalless         ###   ########.fr       */
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

typedef enum e_login {
	UNSET	= 0,
	USER	= (1 << 0),
	NICK	= (1 << 1),
	PASS	= (1 << 2),
	OK		= USER | NICK | PASS,
}	t_login;


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
	bool			_authentified;
	bool			_alreadyKnown;
	t_login		_login;
	
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
	bool			getAuthentified();
	void			setAuthentified(bool status);
	bool			getAlreadyKnown();
	void			setAlreadyKnown(bool status);
	std::string&	getBufferOut();
	void			setBufferOut(std::string buff);

	bool			receive(std::deque<t_message*>& output);
	void			isWelcomed(std::string flag);
	
	void			remove();
};

	t_login			operator|(t_login oldFlag, t_login newFlag);
	
