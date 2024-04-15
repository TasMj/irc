/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:29:06 by tmejri            #+#    #+#             */
/*   Updated: 2024/04/16 00:56:54 by tmalless         ###   ########.fr       */
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

class Client;
typedef std::map<std::string, Client*>     t_clients_map;

class Channel;
typedef std::pair<std::string, Channel*>    t_channel;
typedef std::map<std::string, Channel*>     t_channel_map;

/* typedef enum e_mode {
	START	= 0,

/******************************************************************************/
/*                                  Enum                                      */
/******************************************************************************/
/*
typedef enum e_mode {
	INVITE	= (1 << 0),
	TOPIC	= (1 << 1),
	KEY		= (1 << 2),
	LIMIT	= (1 << 3),
}	t_mode; 
*/
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
		std::vector<Client*>		_operators;
		std::vector<Client*>		_invited;
		size_t						_limit;
		//t_mode						_mode;
		bool						_inviteModeOn;
		bool						_keyModeOn;
		bool						_topicModeOn;
		bool						_limitModeOn;

    public:
        Channel(std::string name, std::string* password);
        std::string     getName(void);
        void            sendToAllClients(std::string msg, Client* cli = NULL);
        std::string*    join(Client* cli, std::string* password);
        t_channel       asPair(void);
		bool			checkOperator(Client* cli);
		void			addOperator(Client* sender, Client* receiver, bool creation);
		void			removeOperator(Client* sender, Client* receiver);
		void			modPassword(std::string password, Client* cli);
		void			removePassword(Client* cli);
		void			modLimit(std::string limit, Client* cli);
		void			removeLimit(Client* cli);
		void			inviteModeOn(Client* cli);
		void			inviteModeOff(Client* cli);
		void			topicModeOn(Client* cli);
		void			topicModeOff(Client* cli);
		bool			isInChannel(std::string name);
		bool			checkClientExist(std::string toKick);
		void    		removeCliFromChan(std::string toKick);
		void			inviteCmd(Client *sender, Client *receiver);
		bool			checkInvited(Client* cli);
};

/* t_mode			operator|(t_mode oldFlag, t_mode newFlag);


		bool			isInChannel(std::string name);
};

/******************************************************************************/
/*                                 Functions                                  */
/******************************************************************************/
/*
t_mode			operator|(t_mode oldFlag, t_mode newFlag);
t_mode			operator&(t_mode oldFlag, t_mode unsetFlag);
 */