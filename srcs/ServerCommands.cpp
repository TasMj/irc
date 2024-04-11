/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerCommands.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:26:50 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/11 03:07:50 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

int Server::execute_cmd(Client* cli, int fd, std::string buff)
{
	(void)cli;
	(void)fd;
	(void)buff;
	std::cout << "COMMANDE TO CHECK" << std::endl;
    // if (strncmp("NICK ", buff.c_str(), 5) == 0)
        // nickCmd(cli, fd, buff);
    // else if (strncmp("PRIVMSG ", buff.c_str(), 8) == 0)
        // msgCmd(cli, fd, buff);
    // else if (strncmp("PING ", buff.c_str(), 5) == 0)
        // pingCmd(cli, fd);
	// else if (strncmp("PASS ", buff.c_str(), 5) == 0)
		// return (checkPwd(cli, fd, buff));
	// else if (strncmp("EXIT ", buff.c_str(), 5) == 0)
		// exitCmd(cli, fd, buff);
	return (0);
}

static Client* findNickName(std::deque<Client>& clients, std::string nickName) {
	std::deque<Client>::iterator first, last;

	first = clients.begin();
	last = clients.end();
	while (first != last) {
    	if (nickName.compare(first->get_nickName()))
			return (&(*first));
		++first;
	}
	return (NULL);
}

void    Server::nickCmd(Client* cli, int fd, std::string buff)
{
	// PARSING
    std::string receivedData(buff);
    
    size_t pos = receivedData.find_first_of("\r\n");
    if (pos != std::string::npos) {
        receivedData = receivedData.substr(0, pos);
    }
    std::string newNick = receivedData.substr(5, pos);

    std::string nickName = cli->get_nickName();
	
	std::string response;
	// CHECKING
    if (findNickName(_clients, newNick))
        response = ":localhost NICK " + nickName + " :\nthis nickname already exist. Please try a new one.\n";
	else {
		cli->set_nickName(newNick);
    	response = ":localhost NICK " + newNick + " :Your nick name is now : " + newNick + "\n"; 
	}

	// SENDING
    cli->get_Server()->setUpTransmission(cli, response, fd);
    cli->get_Server()->prepareMsgToClient(cli);
}

void    Server::msgCmd(Client* cli, int fd, std::string buff)
{
    /*on check si nick ou channel*/
    if (buff[9] && buff[9] == '#')
    {
        /*si channel*/
        /*recup nom du chennel*/
        /*recup msg du chennel*/
        /*on verifie que le nickname existe*/
        /*on envoie le msg au nickname*/
    }
    else
    {
        /*si nick*/
        std::string nick;
        nick = recup_nick_msg(buff);
        
        /*on isole le nick et le msg du buffer*/
        std::string msg;
        int start = nick.length() + 10;
        msg = recup_msg(buff, start);
        std::cout << msg << std::endl;
        std::string prefixe = ":localhost PRIVMSG ";
	   
	   	std::string response;

		int		fd_to_send;
		Client* found = findNickName(_clients, nick);
        if (found)
		{
        	response = prefixe + nick + " :" + msg + "\n";
			fd_to_send = found->get_fd();
        }
		else
        {
			response = prefixe + nick + " :" + "no nick matching\n";
			fd_to_send = fd;
        }
		cli->get_Server()->setUpTransmission(cli, response, fd_to_send);
        cli->get_Server()->prepareMsgToClient(cli);
    }
}

void	Server::pingCmd(Client* cli, int fd)
{
	(void)fd;
	if (cli == NULL)
		return ;

    std::string msg = ":localhost PONG localhost: " + cli->get_nickName() + "\n";
    cli->get_Server()->setUpTransmission(cli, msg, cli->get_fd());
    cli->get_Server()->prepareMsgToClient(cli);
}

int		Server::checkPwd(Client* cli, int fd, std::string buff)
{
	(void)cli;
	int pos = buff.find(" ");
	buff.erase(0, pos + 1);
	if (_password.compare(buff) != 0)
		return (0);

	std::string err_msg =":localhost DISCONNECT localhost: \n Wrong password.\n";
	send(fd, err_msg.c_str(), err_msg.size(), 0);
	return (1);

}

void	Server::exitCmd(Client* cli, int fd, std::string buff)
{
	(void) buff;
	(void) cli;
	std::deque<Client>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (it->get_fd() == fd)
		{
			it->remove();
			break ;
		}
	}
}

