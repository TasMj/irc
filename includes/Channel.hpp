#pragma once

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

typedef enum e_mode {
	I	= (1 << 0),
	T	= (1 << 1),
	K	= (1 << 2),
	L	= (1 << 3),
}	t_mode;

class Channel {
    private:
        std::string    				_name;
        std::string*   				_password;
        t_clients_map  				_clients;
		std::vector<std::string>	_operators;
		int							_limit;
		t_mode						_mode;

    public:
        Channel(std::string name, std::string* password);
        std::string     getName(void);
        void            sendToAllClients(std::string msg, Client* cli = NULL);
        std::string*    join(Client* cli, std::string* password);
        t_channel       asPair(void);
		bool			checkOperator(std::string name);
		void			addOperator(std::string name, Client* cli, bool creation);
		void			removeOperator(std::string name, Client* cli);
		void			modPassword(std::string password);
		void			removePassword();
		void			modLimit(std::string limit);
		void			removeLimit();
		void			inviteModeOn();
		void			inviteModeOff();
		void			topicModeOn();
		void			topicModeOff();
};

t_mode			operator|(t_mode oldFlag, t_mode newFlag);

t_mode			operator&(t_mode oldFlag, t_mode unsetFlag);
