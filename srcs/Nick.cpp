/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:55:54 by tmejri            #+#    #+#             */
/*   Updated: 2024/04/08 23:49:03 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

void    recup_nickNamee(Client *cli, std::string buff_str)
{
    
    size_t position = FindInString(buff_str, "NICK"); //obtient la position de la premiere occurence
    if (position != std::string::npos) //si le mot NICK est présent
    {
        std::string nick_data; // recup de NICK jusqu'à \n
        nick_data = buff_str.substr(position + 5, buff_str.size());
        
        size_t end = nick_data.find_first_of("\r\n");
        if (end != std::string::npos)
            nick_data = nick_data.substr(0, end);
        cli->set_nickName(nick_data); //set the nicknqme
    }
}

void    recup_userr(Client *cli, std::string buff_str)
{
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
        cli->set_userName(user_name); //set the nicknqme
    }
}

static void	first_com(int fd, Client &cli)
{
	std::string prefixe = PREFIXE;
	std::string welcome_msg;
	
	welcome_msg.append(":" + prefixe + " 001 " + cli.get_nickName() + " :Welcome\n" + INTERCEPT + "\n");
	cli.get_Server()->setUpTransmission(&cli, welcome_msg, fd);
	cli.get_Server()->prepareMsgToClient(&cli);
	welcome_msg.clear();
}

void    recup_dataa(Client *cli, std::deque<std::string> cmds)
{
    for (size_t i = 0; i < cmds.size(); i++)
    {
        if (strncmp(cmds.at(i).c_str(), "NICK ", 5) == 0)
            recup_nickNamee(cli, cmds.at(i).c_str());
        else if (strncmp(cmds.at(i).c_str(), "USER ", 5) == 0)
            recup_userr(cli, cmds.at(i).c_str());
	}
	first_com(cli->get_fd(), *cli);
}


/*check if the nickname exist in the container
if it exist -> retunr the fd
if not -> return 0 */
int    check_nick_exist(std::deque<Client>& _clients, std::string nick)
{
    std::deque<Client>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (it->get_nickName() == nick)
            return (it->get_fd());
	}
    return (0);
}