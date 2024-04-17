/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:29:06 by tmejri            #+#    #+#             */
/*   Updated: 2024/04/17 05:17:20 by tmejri           ###   ########.fr       */
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
# include <algorithm>
# include "Client.hpp"

class Client;
typedef std::map<std::string, Client*>     t_clients_map;

class Channel;
typedef std::pair<std::string, Channel*>    t_channel;
typedef std::map<std::string, Channel*>     t_channel_map;

/******************************************************************************/
/*                                  Class                                     */
/******************************************************************************/
class Client;

class Channel;
typedef std::pair<std::string, Channel*>    t_channel;
typedef std::map<std::string, Channel*>     t_channel_map;

class Channel {
   
    private:
        std::string    				_name;
        std::string*   				_password;
		std::deque<Client*>			_clients;
		std::vector<Client*>		_operators;
		std::vector<Client*>		_invited;
		size_t						_limit;
		std::string					_topic;

    public:
        Channel(std::string name, std::string* password);
		~Channel();

        std::string     getName(void);
        void            sendToAllClients(std::string msg, Client* cli = NULL);
        bool    		join(Client* cli, std::string* password);
        t_channel       asPair(void);
		
		bool			checkOperator(Client* cli);
		void			addOperator(Client* cli, bool creation);
		void			removeOperator(Client* cli);
		
		void			modLimit(std::string limit);
		void			removeLimit();
		
		
		
		bool			checkTopicExist();
		void			setTopic(std::string topic);
		std::string		getTopic();
		
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

		bool						_inviteModeOn;
		bool						_keyModeOn;
		bool						_topicModeOn;
		bool						_limitModeOn;

		void			removeClient(Client* cli);



std::deque<Client*>::iterator		findClientByNIckName(std::string name);

};
