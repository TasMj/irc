/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:29:36 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/12 17:11:02 by tmalless         ###   ########.fr       */
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

/******************************************************************************/
/*                                  Defines                                   */
/******************************************************************************/

#include "Color.hpp"

#define MAX_EVENTS 5
#define READ_SIZE 10
#define PREFIXE "localhost"
#define INTERCEPT "WELCOME"
/*
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

		std::map<std::string, Channel*>							_channels;
				
	public:
	
		Server();
		Server(std::string password);
		~Server();
		int							initServer(int port);
		int							serverLoop();
		void						addNewClient();
		void						receiveData(int fd);
		int							receiveFirstData(Client *cli);
		void						cleanServer();

		std::string const &			getPrefixServer() const;
		Client* 						getRefClientByFd(int fd);
		Client* 						getRefClientByName(std::string name);
		void						send_transmission(int pollFd);
		std::vector<Transmission>	getTransmission();
		Transmission				getFirstTransmission();
		void						prepareMsgToClient(Client *cli);
		void						setUpTransmission(Client *cli, std::string msg, int fdDest);
		Transmission*				getTransmissionByFd(int fd);
		Channel*					getRefChannelByName(std::string chanName);


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
		void	cmd_quit(Client* cli, t_message* msg);
};

/******************************************************************************/
/*                                 Functions                                  */
/******************************************************************************/

int			checkElt(std::string serverName, int port, std::string psw);

void    	nickCmd(std::deque<Client>& _clients, int fd, std::string buff);


int    		check_nick_exist(std::deque<Client>& _clients, std::string nick);
std::string recup_nick_msg(std::string buff);
std::string recup_msg(std::string buff, int start);
int    		msgCmd(std::deque<Client>& _clients, std::string buff, int fd);
void 		pingCmd(std::deque<Client>& _clients, int fd);
int			checkPwd(std::deque<Client>& _clients, std::string buff, int fd);
void		exitCmd(std::deque<Client> _clients, std::string buff, int fd);
void    	recup_nickNamee(Client *cli, std::string buff_str);
void    	recup_dataa(Client *cli, std::deque<std::string> cmds);
void    	recup_userr(Client *cli, std::string buff_str);

bool	expect_N_Params(t_message* msg, size_t n);