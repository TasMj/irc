/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:01:47 by tmejri            #+#    #+#             */
/*   Updated: 2024/04/05 17:36:19 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

int execute_cmd(std::vector<Client>& _clients, int fd, std::string buff)
{
    std::cout << YEL << "buff: " << buff << WHI << std::endl;
    
    if (strncmp(":localhost 001 ", buff.c_str(), 15) == 0)
		send(fd, buff.c_str(), buff.size(), 0);
    else if (strncmp(":localhost DISCONECT localhost: ", buff.c_str(), 32) == 0)
		send(fd, buff.c_str(), buff.size(), 0);
    else if (strncmp("NICK ", buff.c_str(), 5) == 0)
        nickCmd(_clients, fd, buff);
    else if (strncmp("PRIVMSG ", buff.c_str(), 8) == 0)
        msgCmd(_clients, buff, fd);
    else if (strncmp("PING ", buff.c_str(), 5) == 0)
        pingCmd(_clients, fd);
	else if (strncmp("PASS ", buff.c_str(), 5) == 0)
		return (checkPwd(_clients, buff, fd));
	else if (strncmp("EXIT ", buff.c_str(), 5) == 0)
		exitCmd(_clients, buff, fd);
	return (0);
}

void	exitCmd(std::vector<Client> _clients, std::string buff, int fd)
{
	(void) buff;
	std::vector<Client>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (it->get_fd() == fd)
		{
			it->remove();
			break ;
		}
	}
}

int	checkPwd(std::vector<Client>& _clients, std::string buff, int fd)
{
	std::string serv_pwd;
	std::vector<Client>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (it->get_fd() == fd)
		{
			std::cout << YEL << "laaaaaaaaaaaaaaaaaaaaaaaaaa" << it->get_Server()->getPwd() << WHI << std::endl;
			serv_pwd = it->get_Server()->getPwd();
			break ;
		}
	}
	std::cout << YEL << serv_pwd << WHI << std::endl;
	std::string pwd;
	std::string err_msg;
	int pos = buff.find(" ");
	buff.erase(0, pos + 1);
	std::cout << CYA << buff << WHI << std::endl;
	if (strncmp(buff.c_str(), serv_pwd.c_str(), 4))
	{
		std::cout << RED << "Password bad !" << WHI << std::endl;
		err_msg =":localhost DISCONNECT localhost: \n Wrong password.\n";
		send(fd, err_msg.c_str(), err_msg.size(), 0);
		return (1);
	}
	else
	{
		std::cout << GRE << "Password good !" << WHI << std::endl;
		return (0);	
	}
}

void    nickCmd(std::vector<Client>& _clients, int fd, std::string buff)
{
    std::string receivedData(buff);
    
    size_t pos = receivedData.find_first_of("\r\n");
    if (pos != std::string::npos) {
        receivedData = receivedData.substr(0, pos);
    }
    std::string newNick = receivedData.substr(5, pos);
    std::string	err_msg;

	err_msg = ":localhost NICK tmejri :\nthis nickname already exist. Please try a new one.\n";
    std::vector<Client>::iterator it;
    for (it = _clients.begin(); it != _clients.end(); ++it)
    {
        if ((it->get_nickName().size() == newNick.length())
            && (strncmp(it->get_nickName().c_str(), newNick.c_str(), it->get_nickName().size()) == 0))
        {
	        send(fd, err_msg.c_str(), err_msg.size(), 0);
            break;
        }
        else
        {
            std::vector<Client>::iterator ite;
            for (ite = _clients.begin(); ite != _clients.end(); ++ite)
            {
                if (it->get_fd() == fd)
                    it->set_nickName(newNick);
                break;
            }
        }
    }
}

int    msgCmd(std::vector<Client>& _clients, std::string buff, int fd)
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
	   
        std::string full_msg = prefixe + nick + " :\n" + msg + "\n";
        
    std::cout << GRE << "nick: <" << WHI << nick << BLU << "> msg: <" << WHI << msg << ">" << WHI << std::endl;
        
        /*on verifie que le nickname existe*/
        int fd_destinataire = check_nick_exist(_clients, nick);
        /*on envoie le msg au nickname*/
        if (fd_destinataire == 0)
        {
            std::cout << RED << "KO" << WHI << std::endl;
            send(fd, "no nick matching\n", 17, 0);
        }
        else
        {
            std::cout << PUR << full_msg << WHI << std::endl;
            send(fd_destinataire, full_msg.c_str(), full_msg.size(), 0);
            std::cout << RED << "OK: " << fd_destinataire << WHI << std::endl;
        }
    }
    return (0);
}

void pingCmd(std::vector<Client>& _clients, int fd)
{
    std::string nick;
    
    std::vector<Client>::iterator it;
    for (it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (it->get_fd() == fd)
        {
            nick =it->get_nickName();
            break ;
        }
    }
    std::string msg = ":localhost PONG localhost: " + nick + "\n";
    std::cout << BLU << msg << WHI << std::endl;
    send(fd, msg.c_str(), msg.size(), 0);
}
