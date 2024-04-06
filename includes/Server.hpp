/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:29:36 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/06 19:16:58 by aclement         ###   ########.fr       */
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
//# include <sys/epoll.h>
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
	
		int					initServer(int port);
		int					serverLoop();
		void				addNewClient();
		void				receiveData(int fd);
		int					receiveFirstData(Client *cli);
		void				cleanServer();
		std::string			getPwd();
		std::vector<pollfd>	getPollfds();
		std::vector<Client> getClient();
		// std::string get_username(std::vector<Client> _clients, char *buff);

		// std::vector<Transmission>	getTransmission();
		void				exec_transmission(std::vector<Transmission> transmission);
				
		std::string const &	getPrefixServer() const;

		Client 						&getRefClientByFd(int fd);
		void						setPollCycles(std::vector<pollfd> _polls);
		void						send_transmission(int pollFd);
		std::vector<Transmission>	getTransmission();
		Transmission				Server::getFirstTransmission();
		void						prepareMsgToClient(Client *cli);
		void						setUpTransmission(Client *cli, std::string msg, int fdDest);

};

/******************************************************************************/
/*                                 Functions                                  */
/******************************************************************************/

int		checkElt(std::string serverName, int port, std::string psw);

int			execute_cmd(std::vector<Client>& _clients, int fd, std::string buff);
void    	nickCmd(std::vector<Client>& _clients, int fd, std::string buff);
size_t		FindInString(const std::string& chaine, const std::string& sousChaine);
void    	recup_nickName(std::vector<Client>& _clients, char *buff);
void    	recup_user(std::vector<Client>& _clients, char *buff);
void    	recup_data(std::vector<Client>* _clients, char *buff);
int    		check_nick_exist(std::vector<Client>& _clients, std::string nick);
std::string recup_nick_msg(std::string buff);
std::string recup_msg(std::string buff, int start);
int    		msgCmd(std::vector<Client>& _clients, std::string buff, int fd);
void 		pingCmd(std::vector<Client>& _clients, int fd);
//void 		execute_cmd(std::vector<Client>& _clients, int fd, std::string buff);
int			checkPwd(std::vector<Client>& _clients, std::string buff, int fd);
void	exitCmd(std::vector<Client> _clients, std::string buff, int fd);

void    recup_nickNamee(Client *cli, std::string buff_str);
void    recup_dataa(Client *cli, std::deque<std::string> cmds);
void    recup_userr(Client *cli, std::string buff_str);

