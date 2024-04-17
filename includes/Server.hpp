/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:29:36 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/16 20:08:00 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/******************************************************************************/
/*                                 Includes                                   */
/******************************************************************************/
# include <string>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <cstdlib>
# include <iostream>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <poll.h>
# include <vector>
# include <map>
# include <deque>
# include <cerrno>
# include <csignal>
# include <fstream>

# include "Channel.hpp"
# include "Message.hpp"
# include "Utils.hpp"
# include "Responses.hpp"

/******************************************************************************/
/*                                  Defines                                   */
/******************************************************************************/

#include "Color.hpp"

#define MAX_EVENTS 5
#define READ_SIZE 10
#define PREFIXE "localhost"

#define INTERCEPT "                                                                     \n\
                                                                     \n\
                   Téma la taille du welcome !                       \n\
                                                                     \n\
██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗    ██╗\n\
██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝    ██║\n\
██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗      ██║\n\
██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝      ╚═╝\n\
╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗    ██╗\n\
 ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝    ╚═╝\n\
                                                                     \n\
                                par tmejri, aclement et tmalless     \n\
                                                                     \n\
																	 \n"
/*\
#define INTERCEPT "                                                         c=====c\n\
                                                            H\n\
   ____________                                         _,,_H__\n\
  (__((__((___()                                       //|     |\n\
 (__((__((___()()_____________________________________// |ACME |\n\
(__((__((___()()()------------------------------------'  |_____|\n"
*/
extern bool g_isRunning;

/******************************************************************************/
/*                                   Class                                    */
/******************************************************************************/


class Client;
typedef std::map<std::string, Client*>     t_clients_map;

class Channel;

class Server
{
	private:
		std::string					_password;
		sockaddr_in					_sockAddr;
		int							_sockfd;

		std::deque<Client>			_clients;
		std::vector<pollfd>			_polls;
		std::string					_prefixServer;

			
		typedef	void (Server::*function)(Client*, t_message*);
		typedef std::map<std::string, function> t_cmd_list;
		t_cmd_list								_cmd_list;

		std::map<std::string, Channel*>			_channels;
				
	public:	
		Server(std::string password, int port);
		~Server();
		
		void						addNewClient();
		void						removeClient(Client& cli);

		Client* 					getRefClientByFd(int fd);
		Client* 					getRefClientByName(std::string name);
		Client* 					getRefClientByNick(std::string nick);
		Channel*					getRefChannelByName(std::string chanName);



/******************************************************************************/
/*                                 Commandes                                  */
/******************************************************************************/
		int		serverLoop();
		int		execute_cmd(Client* cli, t_message* msg);
		
		void    cmd_nick(Client* cli, t_message* msg);
		void    cmd_user(Client* cli, t_message* msg);
		void	cmd_pass(Client* cli, t_message* msg);
		void	cmd_ping(Client* cli, t_message* msg);
		void	cmd_join(Client* cli, t_message* msg);
		void	cmd_mode(Client* cli, t_message* msg);
		void    cmd_privmsg(Client* cli, t_message* msg);
		void	cmd_invite(Client* cli, t_message* msg);
		void	cmd_quit(Client* cli, t_message* msg);
		void	cmd_kick(Client* cli, t_message* msg);
		void	cmd_topic(Client* cli, t_message* msg);
};

/******************************************************************************/
/*                                 Functions                                  */
/******************************************************************************/

bool		expect_N_Params(t_message* msg, size_t n);
bool		expect_At_Least_N_Params(t_message* msg, size_t n);
bool		expect_LastParams(t_message* msg);

std::string	kickMsg(std::string user, std::string channel, std::string kickedUser, std::string reason);


/*ERRORS*/
std::string ERR_CHANOPRIVSNEEDED(std::string nickname, std::string channel, std::string reason);
std::string kickMsg(std::string nickname, std::string channel, std::string reason);

//TOPICS
std::string ERR_NEEDMOREPARAMS(std::string channel, std::string cmd, std::string reason);
std::string RPL_NOTOPIC(std::string nickname, std::string channel, std::string reason);
std::string	RPL_TOPIC(std::string nickname, std::string channel, std::string topic);