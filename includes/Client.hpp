/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:23:57 by tmejri            #+#    #+#             */
/*   Updated: 2024/04/17 02:04:35 by aclement         ###   ########.fr       */
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
# include "Responses.hpp"


/******************************************************************************/
/*                                  Class                                     */
/******************************************************************************/

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
	std::string		_nickName;
	std::string		_userName;
	Server			*_server;
	std::string		_bufferIn, _bufferOut;
	bool			_authentified;
	bool			_alreadyKnown;
	t_login			_login;

	std::map<std::string, Channel*>	_channels;
	
public:
	Client(int fd, Server* server);
	~Client();

	int				get_fd();
	
	void			set_nickName(std::string nick);
	std::string		get_nickName();
	void			set_userName(std::string user);
	std::string		get_userName();
	Server*			get_Server();

	t_login			getLogStatus();
	
	bool			getAuthentified();
	void			setAuthentified(bool status);
	bool			getAlreadyKnown();
	void			setAlreadyKnown(bool status);

	bool			receive(std::deque<t_message*>& output);
	void			isWelcomed(std::string flag);
	
	void			setBufferOut(std::string buff);
	void			join(Channel* channel, std::string* password);

/******************************************************************************/
/*                              Socket IO                                     */
/******************************************************************************/
	bool			read_stream(std::deque<t_message*>& output);
	void			write_stream(void);

	void			leaveAllChannels(void);

};

t_login			operator|(t_login oldFlag, t_login newFlag);
	
