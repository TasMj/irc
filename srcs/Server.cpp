/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:26:50 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/07 17:32:46 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"
#include "../includes/Transmission.hpp"

Server::Server(unsigned int port, std::string password) : _port(port), _password(password), _prefixServer(":localhost")
{
	std::cout << RED << std::endl << std::endl << password << std::endl << std::endl << WHI;
}

Server::~Server()
{
	std::cout << "The server has been shutdown." << std::endl;
}

std::string const &	Server::getPrefixServer() const
{
	return (this->_prefixServer);
}

std::string Server::getPwd()
{
	return(this->_password);
}

std::vector<pollfd> Server::getPollfds()
{
	return(this->_polls);
}

std::vector<Client> Server::getClient()
{
	return(this->_clients);
}

int Server::initServer(int port)
{
	struct pollfd new_poll;

	this->_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_sockfd == -1)
	{
		std::cout << "Failed to create socket. errno: " << errno << std::endl;
		return (1);
	}

	this->_sockAddr.sin_family = AF_INET;
	this->_sockAddr.sin_addr.s_addr = INADDR_ANY;
	this->_sockAddr.sin_port = htons(port);
	int reuseAddr = 1;
	if (setsockopt(this->_sockfd, SOL_SOCKET, SO_REUSEADDR, &reuseAddr, sizeof(reuseAddr)) == -1)
	{
		std::cout << "Failed to set SO_REUSEADDR option" << std::endl;
		return (1);
	}

	if (bind(this->_sockfd, (struct sockaddr *)&this->_sockAddr, sizeof(sockaddr)) < 0)
	{
		std::cout << "Failed to bind to port " << port << ". errno: " << errno << std::endl;
		return (1);
	}

	if (listen(this->_sockfd, 10) < 0)
	{
		std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
		return (1);
	}

	new_poll.fd = this->_sockfd;
	new_poll.events = POLLIN;
	new_poll.revents = 0;
	this->_polls.push_back(new_poll);
	return (0);
}

void Server::addNewClient()
{
	Client cli;

	struct sockaddr_in cliAdd;
	struct pollfd new_poll;
	socklen_t len = sizeof(cliAdd);

	int receiving_fd = accept(this->_sockfd, (sockaddr *)&(cliAdd), &len);
	fcntl(receiving_fd, F_SETFL, O_NONBLOCK);

	new_poll.fd = receiving_fd;
	new_poll.events = POLLIN;
	new_poll.revents = 0;

	cli.set_fd(receiving_fd);
	cli.set_ip(inet_ntoa(cliAdd.sin_addr));
	cli.set_Server(this);
	this->_clients.push_back(cli);
	this->_polls.push_back(new_poll);
	
	std::cout << "CLIENT " << receiving_fd << " CONNECTED" << std::endl;

	std::vector<Client>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); ++it)
	{
		std::cout << "fd : " << it->get_fd() << ", Nickname : " << it->get_nickName() << std::endl;
	}
	
	if (receiveFirstData(&cli))
	{
		std::string prefixe = PREFIXE;
		std::string welcome_msg;
		welcome_msg = ":" + prefixe + " 001 " + cli.get_nickName() + " :Welcome\n" + INTERCEPT + "\n";
		// std::cout << RED << "welcome msg :" <<std::endl << std::endl << cli.get_nickName() <<std::endl << std::endl << WHI;
		// handleMsg(&cli, welcome_msg);
		// welcome_msg.clear();
		// welcome_msg = ":" + prefixe + " 002 " + cli.get_nickName() + " :Your host is " + PREFIXE + "\n";
		// std::cout << RED << "welcome msg :" <<std::endl << std::endl << cli.get_nickName() <<std::endl << std::endl << WHI;
		// handleMsg(&cli, welcome_msg);
		// welcome_msg.clear();
		// welcome_msg = ":" + prefixe + " 003 " + cli.get_nickName() + " ::This server was created Mon Aug 11 2014 at 17:47:17 GMT \n";
		// std::cout << RED << "welcome msg :" <<std::endl << std::endl << cli.get_nickName() <<std::endl << std::endl << WHI;
		// handleMsg(&cli, welcome_msg);
		// welcome_msg.clear();
		// welcome_msg = ":" + prefixe + " 004 " + cli.get_nickName() + " :" + PREFIXE + " tasambthe1.0 dgikoswx itkol bko \n" ;
		// std::cout << RED << "welcome msg :" <<std::endl << std::endl << cli.get_nickName() <<std::endl << std::endl << WHI;
		// handleMsg(&cli, welcome_msg);
		// welcome_msg.clear();
		// welcome_msg = ":" + prefixe + " 005 " + cli.get_nickName() + " MAP SILENCE=15 WHOX WALLCHOPS WALLVOICES USERIP CPRIVMSG "
			// "CNOTICE MODES=6 MAXCHANNELS=10 MAXBANS=45 NICKLEN=9 TOPICLEN=160 AWAYLEN=160 KICKLEN=160 CHANTYPES=#& PREFIX=(ov)@+ "\
			// "CHANMODES=b,k,l,rimnpst CASEMAPPING=rfc1459 :are supported by this server \n";
		// std::cout << RED << "welcome msg :" <<std::endl << std::endl << cli.get_nickName() <<std::endl << std::endl << WHI;
		// handleMsg(&cli, welcome_msg);
		// welcome_msg.clear();
		// welcome_msg = ":" + prefixe + " 372 " + cli.get_nickName() + " :Bien le bonjour du jour ! \n";
		// std::cout << RED << "welcome msg :" <<std::endl << std::endl << cli.get_nickName() <<std::endl << std::endl << WHI;
		// handleMsg(&cli, welcome_msg);
		// welcome_msg.clear();
		// send(cli.get_fd(), welcome_msg.c_str(), welcome_msg.size(), 0);
		/* welcome_msg = ":" + prefixe + " 422 " + cli.get_nickName() + " :MOTD File is missing";
		std::cout << RED << "welcome msg :" <<std::endl << std::endl << cli.get_nickName() <<std::endl << std::endl << WHI;
		handleMsg(&cli, welcome_msg);
		welcome_msg.clear();	 */
			
	}

}

Client &Server::getRefClientByFd(int fd)
{
	std::vector<Client>::iterator	it = _clients.begin();
	std::vector<Client>::iterator	itend = _clients.end();

	while (it != itend)
	{
		if (it->get_fd() == fd)
			return (*it);
		it++;
	}
	return (*it);
}

void	Server::prepareMsgToClient(Client *cli)
{
	// std::vector<int> ref = cli->getTransmission().getFdDest();
	// std::vector<int>::iterator it = getTransmissionByFd(cli->get_fd()).getFdDest().begin();
	// std::vector<int>::iterator itend = getTransmissionByFd(cli->get_fd()).getFdDest().end();

	std::cout << BLU << "sizeDest : " << this->getTransmissionByFd(cli->get_fd()).getFdDest().size() << WHI << std::endl;
	for (size_t i = 0; i < this->getTransmissionByFd(cli->get_fd()).getFdDest().size(); i++)
	// while (it != itend)
	{
		// client ? 
		Client &dest = this->getRefClientByFd(this->getTransmissionByFd(cli->get_fd()).getFdDest()[i]);
		std::cout << "sageme : " << this->getTransmissionByFd(cli->get_fd()).getMsg() << std::endl;
		dest.setBufferOut(this->getTransmissionByFd(cli->get_fd()).getMsg());
		dest.setFlagIO(0);
		// it++;
	}
	std::vector<Transmission>::iterator	it;
	
	for (it = this->getTransmission().begin(); it < this->getTransmission().end(); it++)
	{
		if (it->getFdEmitter() == cli->get_fd())
			break ;
	}
	std::cout << "taille avant : " << this->_transmission.size() << std::endl;
	this->_transmission.erase(it);
	std::cout << "taille apres : " << this->_transmission.size() << std::endl;
}

void Server::setTransmission(const Transmission &newTrans) {
    // this->getTransmission().push_back(newTrans);
    this->_transmission.push_back(newTrans);
}

void Server::setUpTransmission(Client *cli, std::string msg, int fdDest) {
    Transmission newTrans;
    
    newTrans.setFdEmitter(cli->get_fd());
    newTrans.setMsg(msg);
    newTrans.addNewFdDest(fdDest);

	// std::cout << PUR << "FD : " << this->getTransmission().at(0).getFdDest().at(0) << WHI << std::endl;
	// std::cout << PUR << "FD : " << this->_transmission.at(0).getFdDest().at(0) << WHI << std::endl;

    this->setTransmission(newTrans);
}


// void	Server::setTransmission(Transmission newTrans)
// {
// 	this->getTransmission().push_back(newTrans);
// }

// void	Server::setUpTransmission(Client *cli, std::string msg, int fdDest)
// {
// 	Transmission	newTrans;
	
// 	newTrans.setFdEmitter(cli->get_fd());
// 	newTrans.setMsg(msg);
// 	std::cout << "mes : " << newTrans.getMsg() << std::endl;
// 	//
// 	newTrans.addNewFdDest(fdDest);

// 	std::cout << YEL << "sizeDest : " << newTrans.getFdDest()[0] << WHI << std::endl;
	
// 	this->setTransmission(newTrans);
// 	// std::cout << YEL << "sizeDest : " << this->getFirstTransmission().getFdDest().size() << WHI << std::endl;

// }

std::deque<std::string>	split(std::string str, std::string separator)
{
	std::deque<std::string> cmd;
	std::string a;
	
	size_t pos = 0;
	while ((pos = str.find(separator)) != std::string::npos)
	{
		a = str.substr(0, pos);
		std::cout << "ici : " << a << std::endl;
		pos += separator.length();
		str.erase(0, pos);
		cmd.push_back(a);
	}
	return(cmd);
}

int Server::receiveFirstData(Client *cli)
{
	std::cout << GRE << std::endl << std::endl << "Poll status :     " << this->_pollStatus << std::endl << std::endl << WHI << std::endl;
	char buff[1024];
	memset(buff, 0, sizeof(buff));

	ssize_t bytes = recv(cli->get_fd(), buff, sizeof(buff) - 1, 0);
	std::cout << YEL << "le fd : " << cli->get_fd() << WHI << std::endl;
	std::cout << BLU << "le poll : " << this->_poll.events << WHI << std::endl;
	std::cout << RED << "les bytes : " << bytes << WHI << std::endl; 

	if (bytes <= 0)
	{
		std::cout << RED << "Client <" << cli->get_fd() << "> Disconnected" << WHI << std::endl;
		close(cli->get_fd()); //-> close the client socket
	}
	else
	{
		bool is_pwd = false;
		buff[bytes + 1] = '\0';
		std::deque<std::string> cmds = split(buff, "\r\n");
		std::cout << cmds.size() << std::endl;
		for (size_t i = 0; i < cmds.size(); i++)
		{
			std::cout << PUR << "COUCOU : " << WHI << cmds.at(i) << std::endl;
			if (strncmp("PASS ", cmds.at(i).c_str(), 5) == 0)
				is_pwd = true;
		}
		recup_dataa(cli, cmds);
		if (!is_pwd)
		{
			std::string error_msg;
			std::string miss_pw = "You need a password to connect.\n";
			error_msg = ":localhost DISCONECT localhost: \n" + miss_pw;

			this->setUpTransmission(cli, error_msg, cli->get_fd());
			this->prepareMsgToClient(cli);
			return (0);
		}
	}
	//setPollStatus(POLLOUT);
	return (1);
}

void Server::receiveData(int fd)
{
	char buff[1024];
	memset(buff, 0, sizeof(buff));

	ssize_t bytes = recv(fd, buff, sizeof(buff) - 1, 0);
	std::cout << YEL << "le fd : " << fd << WHI << std::endl;
	std::cout << RED << "les bytes : " << bytes << WHI << std::endl;

	if (bytes <= 0)
	{
		std::cout << RED << "Client <" << fd << "> Disconnected" << WHI << std::endl;
		close(fd); //-> close the client socket
	}
	else
	{
		buff[bytes] = '\0';

		std::vector<Client>::iterator it;
		Client tmp;
		for (it = _clients.begin(); it != _clients.end(); ++it)
		{
			if (it->get_fd() == fd)
			{
				tmp = *it;
				break;
			}
		}
		Client cli = getRefClientByFd(fd);
		this->setUpTransmission(&cli, buff, cli.get_fd());
		this->prepareMsgToClient(&cli);
		execute_cmd(_clients, fd, buff);
	}
}

void Server::cleanServer()
{
	std::vector<pollfd>::iterator it;

	for (it = this->_polls.begin(); it != this->_polls.end(); it++)
	{
		close(it->fd);
	}
	delete this;
}

void	Server::exec_transmission(std::vector<Transmission> transmission)
{
	std::vector<Transmission>::iterator it;
	
	for (it = this->getTransmission().begin(); it != this->getTransmission().end(); ++it)
		execute_cmd(_clients , it->getFdEmitter(), it->getMsg());
	transmission.clear();
}

void	Server::setPollCycles(std::vector<pollfd> _polls)
{
	std::vector<pollfd>::iterator it = _polls.begin();
	std::vector<pollfd>::iterator itend = _polls.end();


	if (this->_polls.size() == 1)
		return ;
	while (it != itend)
	{
		//std::cout << PUR << "COUCOUCOUCOUC " << it->events << WHI <<std::endl;
		if (getRefClientByFd(it->fd).getFlagIO() == 1)
			it->events = POLLIN;
		if (getRefClientByFd(it->fd).getFlagIO() == 0)
			it->events = POLLOUT;
		it++;
	}
}

Transmission	Server::getTransmissionByFd(int fd)
{
	std::vector<Transmission>::iterator	it;
	Transmission						ret;

	for (it = _transmission.begin(); it < _transmission.end(); it++)
	{
		if (it->getFdEmitter() == fd)
		{
			ret = *it;
			break ;
		}
	}
	return (ret);
}

void	Server::send_transmission(int pollFd)
{
	std::string msg = this->getRefClientByFd(pollFd).getBufferOut();
	std::cout << "le message : " << msg << std::endl;
	if (!msg.empty())
	{
		send(pollFd, msg.c_str(), msg.size(), 0);
		getRefClientByFd(pollFd).setFlagIO(0);
	}
}


int Server::serverLoop()
{
	g_isRunning = true;
	size_t 			i;
	while (g_isRunning)
	{
		// std::cout << "\nPolling for inpu...\n" << std::endl;
		setPollCycles(_polls);
		
		for (i = 0; i < this->_polls.size(); i++)
		{
			if (poll(&this->_polls[0], this->_polls.size(), -1) == -1 && g_isRunning)
				throw(std::runtime_error("poll() failed"));
			
			if (this->_polls[i].revents & POLLIN)
			{
				if (this->_polls[i].fd == this->_sockfd)
				{
					std::cout << GRE << ":::" << WHI << std::endl;
					this->addNewClient();
				}
				else
				{
					std::cout << GRE << "..." << WHI << std::endl;	
					this->receiveData(this->_polls[i].fd);
					//this->receiveFirstData(&(getRefClientByFd(this->_polls[i].fd)));
				}
			}
			if (this->_polls[i].revents & POLLOUT)
			{
				this->send_transmission(_polls[i].fd);
			}
			_polls[i].revents = 0;
		}
	}
	this->cleanServer();
	return (0);
}

std::vector<Transmission> Server::getTransmission()
{
	return (this->_transmission);
}

Transmission Server::getFirstTransmission()
{
	Transmission ret;
	ret = this->_transmission[0];
	this->_transmission.erase(this->_transmission.begin());
	return (ret);
}
