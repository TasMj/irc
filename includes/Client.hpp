/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:23:57 by tmejri            #+#    #+#             */
/*   Updated: 2024/04/12 18:41:31 by tmalless         ###   ########.fr       */
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

# include "Message.hpp"
# include "Channel.hpp"
# include "Transmission.hpp"


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

class Channel;

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
	bool			_isOps;
	t_login		_login;

	std::map<std::string, Channel*>	_channels;
	
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
	bool			getIsOps();
	void			setIsOps(bool status);

	bool			receive(std::deque<t_message*>& output);
	void			isWelcomed(std::string flag);
	
	void			remove();

	void			setBufferOut(std::string buff);
	void			join(Channel* channel, std::string* password);

/******************************************************************************/
/*                              Socket IO                                     */
/******************************************************************************/
	bool			read_stream(std::deque<t_message*>& output);
	void			write_stream(void);
};

	t_login			operator|(t_login oldFlag, t_login newFlag);
	
