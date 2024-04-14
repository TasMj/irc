/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:29:06 by tmejri            #+#    #+#             */
/*   Updated: 2024/04/14 19:30:44 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/******************************************************************************/
/*                                 Includes                                   */
/******************************************************************************/
# include <string>
# include <utility>
# include <map>
# include <vector>
# include "Client.hpp"

/******************************************************************************/
/*                                  Enum                                      */
/******************************************************************************/
typedef enum e_mode {
	I	= (1 << 0),
	T	= (1 << 1),
	K	= (1 << 2),
	L	= (1 << 3),
}	t_mode;

/******************************************************************************/
/*                                  Class                                     */
/******************************************************************************/
class Client;
typedef std::map<std::string, Client*>     t_clients_map;

class Channel;
typedef std::pair<std::string, Channel*>    t_channel;
typedef std::map<std::string, Channel*>     t_channel_map;

class Channel {
   
    private:
        std::string    				_name;
        std::string*   				_password;
        t_clients_map  				_clients;
		std::vector<Client*>	_operators;
		int							_limit;
		t_mode						_mode;

    public:
        Channel(std::string name, std::string* password);
        std::string     getName(void);
        void            sendToAllClients(std::string msg, Client* cli = NULL);
        std::string*    join(Client* cli, std::string* password, bool fromInvite);
        t_channel       asPair(void);
		bool			checkOperator(Client* cli);
		void			addOperator(Client* cli, bool creation);
		void			removeOperator(Client* cli);
		void			modPassword(std::string password);
		void			removePassword();
		void			modLimit(std::string limit);
		void			removeLimit();
		void			inviteModeOn();
		void			inviteModeOff();
		void			topicModeOn();
		void			topicModeOff();
		
		bool			checkClientExist(std::string toKick);
		void    		removeCliFromChan(std::string toKick);
		void			inviteCmd(Client *sender, Client *receiver);
};

/******************************************************************************/
/*                                 Functions                                  */
/******************************************************************************/
t_mode			operator|(t_mode oldFlag, t_mode newFlag);
t_mode			operator&(t_mode oldFlag, t_mode unsetFlag);
