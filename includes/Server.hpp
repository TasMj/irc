/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:29:36 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/16 00:45:24 by tmalless         ###   ########.fr       */
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
# include "Transmission.hpp"

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

class Transmission;

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
		std::vector<Transmission>	_transmission;
		std::string					_prefixServer;

			
		typedef	void (Server::*function)(Client*, t_message*);
		typedef std::map<std::string, function> t_cmd_list;
		t_cmd_list								_cmd_list;

		std::map<std::string, Channel*>			_channels;
				
	public:
	
		Server();
		Server(std::string password);
		~Server();
		int							initServer(int port);
		int							serverLoop();
		void						addNewClient();
		void						cleanServer();

		std::string const &			getPrefixServer() const;
		Client* 						getRefClientByFd(int fd);
		Client* 						getRefClientByName(std::string name);
		Client* 						getRefClientByNick(std::string nick);
		void						send_transmission(int pollFd);
		std::vector<Transmission>	getTransmission();
		Transmission				getFirstTransmission();
		void						sendToAll(Client* sender, std::string msg, t_clients_map _clients);
		void						prepareMsgToClient(Client *cli);
		void						setUpTransmission(Client *cli, std::string msg, int fdDest);
		Transmission*				getTransmissionByFd(int fd);
		Channel*					getRefChannelByName(std::string chanName);


		Client*	findNickName(std::string nickName);
void	removeClient(Client& cli);
/******************************************************************************/
/*                                 Commandes                                  */
/******************************************************************************/
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
};




/******************************************************************************/
/*                                 Functions                                  */
/******************************************************************************/

int			checkElt(std::string serverName, int port, std::string psw);

void    	nickCmd(std::deque<Client>& _clients, int fd, std::string buff);


std::string recup_nick_msg(std::string buff);
std::string recup_msg(std::string buff, int start);
int    		msgCmd(std::deque<Client>& _clients, std::string buff, int fd);
void 		pingCmd(std::deque<Client>& _clients, int fd);
int			checkPwd(std::deque<Client>& _clients, std::string buff, int fd);
void		exitCmd(std::deque<Client> _clients, std::string buff, int fd);
void    	recup_nickNamee(Client *cli, std::string buff_str);
void    	recup_userr(Client *cli, std::string buff_str);


bool		expect_N_Params(t_message* msg, size_t n);
bool		expect_At_Least_N_Params(t_message* msg, size_t n);
bool		expect_LastParams(t_message* msg);

std::string	kickMsg(std::string user, std::string channel, std::string kickedUser, std::string reason);


/*ERRORS*/
std::string	errChannel(std::string nickname, std::string channel, std::string reason);
std::string errOperator(std::string nickname, std::string channel, std::string reason);
std::string errClient(std::string nickname, std::string channel, std::string reason);
std::string kickMsg(std::string nickname, std::string channel, std::string reason);
