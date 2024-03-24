/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NewFonction.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:23:09 by tas               #+#    #+#             */
/*   Updated: 2024/03/24 14:42:27 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

void    nickCmd(std::vector<Client>& _clients, int fd, std::string buff)
{
    std::string receivedData(buff);
    
    size_t pos = receivedData.find_first_of("\r\n");
    if (pos != std::string::npos) {
        receivedData = receivedData.substr(0, pos);
    }
    std::string newNick = receivedData.substr(5, pos);
    std::string	err_msg;

	err_msg = ":localhost 001 tmejri :\nthis nickname already exist. Please try a new one.\n";
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

size_t FindInString(const std::string& chaine, const std::string& sousChaine)
{
    size_t position = chaine.find(sousChaine);
    return (position);
}

void    recup_nickName(std::vector<Client>& _clients, char *buff)
{
    std::string buff_str(buff); //char * to string
    size_t position = FindInString(buff_str, "NICK"); //obtient la position de la premiere occurence
    if (position != std::string::npos) //si le mot NICK est présent
    {
        std::string nick_data; // recup de NICK jusqu'à \n
        nick_data = buff_str.substr(position + 5, buff_str.size());
        
        size_t end = nick_data.find_first_of("\r\n");
        if (end != std::string::npos)
            nick_data = nick_data.substr(0, end);
        _clients.back().set_nickName(nick_data); //set the nicknqme

        // std::cout << PUR << nick_data << WHI << std::endl;
    }
}

void    recup_user(std::vector<Client>& _clients, char *buff)
{
    std::string buff_str(buff);
    size_t position = FindInString(buff_str, "USER");
    if (position != std::string::npos)
    {
        std::string user_data;
        user_data = buff_str.substr(position + 5, buff_str.size());
        
        size_t end = user_data.find_first_of("\r\n");
        if (end != std::string::npos)
            user_data = user_data.substr(0, end);

        position = FindInString(user_data, ":");
        std::string user_name;
        user_name = user_data.substr(position + 1, user_data.size());
        _clients.back().set_userName(user_name); //set the nicknqme
        
        // std::cout << GRE << user_name << WHI << std::endl;
        // std::cout << RED << _clients.back().get_userName() << WHI << std::endl;
    }
}

void    recup_data(std::vector<Client>& _clients, char *buff)
{
    recup_nickName(_clients, buff);
    recup_user(_clients, buff);    
}

/*pas utile car si pas 3 param, ne prend pas ne compte*/
/*
bool    check_param(std::string buff)
{
    int counter = 0;
    int i = 0;

    while (buff[i])
    {
        if (buff[i] != ' ')
            i++;
        else if (buff[i] == ' ')
        {
            counter++;
            while (buff[i] == ' ')
                i++;
        }
    }
    if (buff[i] != ' ')
        counter++;
    std::cout << RED << counter << WHI << std::endl;
    return (counter);
}*/

/*a verifier*/
int    check_nick_exist(std::vector<Client>& _clients, std::string nick)
{
    std::vector<Client>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (it->get_nickName() == nick)
            return (it->get_fd());
	}
    return (0);
}

std::string recup_nick_msg(std::string buff)
{
    std::string nick = buff.substr(8, buff.size());
        
    size_t end = nick.find_first_of(" ");
    if (end != std::string::npos)
        nick = nick.substr(0, end);
    return (nick);
}

std::string recup_msg(std::string buff, int start)
{
    std::string tmp;
    size_t end = buff.find_first_of("\r\n");
    std::cout << PUR << "start: " << start << " end: " << end << WHI << std::endl;
    if (end != std::string::npos)
        tmp = buff.substr(0, end);
    std::string msg;
    msg = tmp.substr(start, tmp.length());
    return (msg);
}

int    msgCmd(std::vector<Client>& _clients, std::string buff, int fd)
{
    /*verifier qu'il y a assez de paramètres (>3)*/
    
    // if (check_param(buff) < 3)
    // {
    //     send(fd, "Not enough parameters given\n", 28, 0);
    //     return (1);
    // }
    
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
            
            send(fd_destinataire, msg.c_str(), msg.size(), 0);
            std::cout << RED << "OK: " << fd_destinataire << WHI << std::endl;
        }
    }
    return (0);
}


void execute_cmd(std::vector<Client>& _clients, int fd, std::string buff)
{
    if (strncmp("/nick ", buff.c_str(), 5) == 0 || strncmp("NICK ", buff.c_str(), 5) == 0)
        nickCmd(_clients, fd, buff);
    if (strncmp("PRIVMSG ", buff.c_str(), 8) == 0)
        msgCmd(_clients, buff, fd);

}
