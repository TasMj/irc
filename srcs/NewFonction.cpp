/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NewFonction.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:23:09 by tas               #+#    #+#             */
/*   Updated: 2024/03/22 14:34:25 by tmejri           ###   ########.fr       */
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
    std::string newNick = receivedData.substr(6, pos);
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

void execute_cmd(std::vector<Client>& _clients, int fd, std::string buff)
{
    if (strncmp("/nick ", buff.c_str(), 5) == 0 || strncmp("/NICK ", buff.c_str(), 5) == 0)
        nickCmd(_clients, fd, buff);
}

std::string get_username(std::vector<Client> _clients, char *buff)
{
    // std::cout << PUR << buff << WHI << std::endl;
    return ("TEST");
}
