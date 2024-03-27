/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:55:54 by tmejri            #+#    #+#             */
/*   Updated: 2024/03/27 09:57:40 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

void    recup_nickNamee(Client *cli, char *buff)
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
        cli->set_nickName(nick_data); //set the nicknqme
    }
    std::cout << PUR << "nick: " << cli->get_nickName() << WHI << std::endl;
}

// void    recup_nickName(std::vector<Client>* _clients, char *buff)
// {
//     std::string buff_str(buff); //char * to string
//     size_t position = FindInString(buff_str, "NICK"); //obtient la position de la premiere occurence
//     if (position != std::string::npos) //si le mot NICK est présent
//     {
//         std::string nick_data; // recup de NICK jusqu'à \n
//         nick_data = buff_str.substr(position + 5, buff_str.size());
        
//         size_t end = nick_data.find_first_of("\r\n");
//         if (end != std::string::npos)
//             nick_data = nick_data.substr(0, end);
//         _clients->back().set_nickName(nick_data); //set the nicknqme
//     }
//     std::cout << PUR << "nick: " << _clients->back().get_nickName() << WHI << std::endl;
// }

void    recup_userr(Client *cli, char *buff)
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
        cli->set_userName(user_name); //set the nicknqme
    }
    std::cout << PUR << "user: " << cli->get_userName() << WHI << std::endl;
}

// void    recup_user(std::vector<Client>* _clients, char *buff)
// {
//     std::string buff_str(buff);
//     size_t position = FindInString(buff_str, "USER");
//     if (position != std::string::npos)
//     {
//         std::string user_data;
//         user_data = buff_str.substr(position + 5, buff_str.size());
        
//         size_t end = user_data.find_first_of("\r\n");
//         if (end != std::string::npos)
//             user_data = user_data.substr(0, end);

//         position = FindInString(user_data, ":");
//         std::string user_name;
//         user_name = user_data.substr(position + 1, user_data.size());
//         _clients->back().set_userName(user_name); //set the nicknqme
//     }
//     std::cout << PUR << "user: " << _clients->back().get_userName() << WHI << std::endl;
// }

void    recup_dataa(Client *cli, char *buff)
{
    if (cli->get_nickName().empty())
        recup_nickNamee(cli, buff);
    if (cli->get_userName().empty())
        recup_userr(cli, buff);    
    std::cout << cli->get_fd() << std::endl;
}


// void    recup_data(std::vector<Client>* _clients, char *buff)
// {
//     if (_clients->back().get_nickName().empty())
//         recup_nickName(_clients, buff);
//     if (_clients->back().get_userName().empty())
//         recup_user(_clients, buff);    
//     std::cout << _clients->back().get_fd() << std::endl;
// }

/*check if the nickname exist in the container
if it exist -> retunr the fd
if not -> return 0 */
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