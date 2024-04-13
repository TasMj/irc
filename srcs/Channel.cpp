
#include "Channel.hpp"

Channel::Channel(std::string name, std::string* password)
    : _name(name)
    , _password(NULL)
{
	_mode = (t_mode)0;
    if (password != NULL) {
        _password = new std::string(*password);
		_mode = (t_mode)K;
    }
}

std::string*    Channel::join(Client* cli, std::string* password) {
    if (_password) {
        if (password == NULL || (password != NULL && _password->compare(*password) != 0)) {
            return (new std::string("bad password\r\n"));
        }
        //send THE RIGHT ERROR MSG
    }
    _clients.insert(std::make_pair(cli->get_nickName(), cli));
    return (NULL);
}

void        Channel::sendToAllClients(std::string msg, Client* cli) {
	t_clients_map::iterator	it;

	for (it = _clients.begin(); it != _clients.end(); it++)
	{
		if (it->second == cli)
			continue ;
		it->second->setBufferOut(msg);
	}
}

std::string Channel::getName(void) {
    return (_name);
}

t_channel   Channel::asPair(void) {
    return (std::make_pair(_name, this));
}

t_mode			operator|(t_mode oldFlag, t_mode newFlag)
{
	return ((t_mode)((int)oldFlag | (int)newFlag));
}

t_mode			operator&(t_mode oldFlag, t_mode unsetFlag)
{
	return ((t_mode)((int)oldFlag & ~(int)unsetFlag));
}