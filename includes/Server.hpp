/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:29:36 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/08 13:06:37 by tas              ###   ########.fr       */
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
# include "Client.hpp"

/******************************************************************************/
/*                                  Defines                                   */
/******************************************************************************/

/*COLORS*/
#define RED "\e[1;31m"
#define WHI "\e[0;37m"
#define GRE "\e[1;32m"
#define YEL "\e[1;33m"
#define BLU "\e[0;34m"
#define PUR "\e[0;35m"
#define CYA "\e[0;36m"

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

class Server
{
	private:
	
		unsigned int				_port;
		std::string					_password;
		sockaddr_in					_sockAddr;
		int							_sockfd;
		int							_connection[5];
		struct pollfd				_poll;
		int 						_epoll_fd;
		std::vector<Client>			_clients;
		std::vector<pollfd>			_polls;
		std::vector<Transmission>	_transmission;
		unsigned int				_pollStatus;
		std::string					_prefixServer;
		
	public:
	
		Server();
		Server(unsigned int port, std::string password);
		~Server();
		int							initServer(int port);
		int							serverLoop();
		void						addNewClient();
		void						receiveData(int fd);
		int							receiveFirstData(Client *cli);
		void						cleanServer();
		std::string					getPwd();
		std::vector<pollfd>			getPollfds();
		std::vector<Client> 		getClient();
		std::string const &			getPrefixServer() const;
		Client 						&getRefClientByFd(int fd);
		void						setPollCycles(std::vector<pollfd> _polls);
		void						send_transmission(int pollFd);
		std::vector<Transmission>	getTransmission();
		Transmission				getFirstTransmission();
		void						prepareMsgToClient(Client *cli);
		void						setUpTransmission(Client *cli, std::string msg, int fdDest);
		Transmission				getTransmissionByFd(int fd);
		void 						setTransmission(const Transmission &newTrans);
};

/******************************************************************************/
/*                                 Functions                                  */
/******************************************************************************/

int			checkElt(std::string serverName, int port, std::string psw);
int			execute_cmd(std::vector<Client>& _clients, int fd, std::string buff);
void    	nickCmd(std::vector<Client>& _clients, int fd, std::string buff);
size_t		FindInString(const std::string& chaine, const std::string& sousChaine);
int    		check_nick_exist(std::vector<Client>& _clients, std::string nick);
std::string recup_nick_msg(std::string buff);
std::string recup_msg(std::string buff, int start);
int    		msgCmd(std::vector<Client>& _clients, std::string buff, int fd);
void 		pingCmd(std::vector<Client>& _clients, int fd);
int			checkPwd(std::vector<Client>& _clients, std::string buff, int fd);
void		exitCmd(std::vector<Client> _clients, std::string buff, int fd);
void    	recup_nickNamee(Client *cli, std::string buff_str);
void    	recup_dataa(Client *cli, std::deque<std::string> cmds);
void    	recup_userr(Client *cli, std::string buff_str);
void		first_com(int fd, Client &cli);

