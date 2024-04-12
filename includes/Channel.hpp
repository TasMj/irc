#pragma once

# include <string>
# include <utility>
# include <map>
# include "Client.hpp"

class Client;
typedef std::map<std::string, Client*>     t_clients_map;

class Channel;
typedef std::pair<std::string, Channel*>    t_channel;
typedef std::map<std::string, Channel*>     t_channel_map;

class Channel {
    private:
        std::string     _name;
        std::string*    _password;
        t_clients_map   _clients;

    public:
        Channel(std::string name, std::string* password);
        std::string     getName(void);
        void            sendToAllClients(std::string msg, Client* cli = NULL);
        std::string*    join(Client* cli, std::string* password);
        t_channel       asPair(void);
};


