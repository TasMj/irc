
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

bool			Channel::checkOperator(std::string name)
{
	for (size_t i = 0; i < _operators.size(); i++)
	{
		if (_operators[i] == name)
		{
			std::cout << name << " is an operator of this channel." << std::endl;
			return (true);
		}
	}
	std::cout << name << " is not an operator of this channel." << std::endl;
	return (false);
};

void			Channel::addOperator(std::string name)
{
	for (size_t i = 0; i < _operators.size(); i++)
	{
		if (_operators[i] == name)
		{
			std::cout << name << " is already an operator of this channel." << std::endl;
			return ;
		}
	}
	std::cout << name << " is already an operator of this channel." << std::endl;
	_operators.push_back(name);
};

void			Channel::removeOperator(std::string name)
{
	for (size_t i = 0; i < _operators.size(); i++)
	{
		if (_operators[i] == name)
		{
			_operators[i].erase();
			return ;
		}
	}
	
	std::cout << name << " was not an operator of this channel." << std::endl;
};

void			Channel::modPassword(std::string password)
{
	if (!(_mode & (t_mode)K))
	//_mode = _mode | (t_mode)K; 
	std::cout << password << " is the new password of this channel." << std::endl;
};

void			Channel::removePassword()
{
	std::cout << "this channel has no more password." << std::endl;
};

void			Channel::modLimit(std::string limit)
{
	std::cout << limit << "is the maximum number of user allowed in this channel." << std::endl;
};

void			Channel::removeLimit()
{
	std::cout << "This channel has no more user limit." << std::endl;
};

void			Channel::inviteModeOn()
{
	std::cout << "This channel is now accessible only through invitation." << std::endl;
};

void			Channel::inviteModeOff()
{
	std::cout << "No more need to be invited to join this channel." << std::endl;
};

void			Channel::topicModeOn()
{
	std::cout << "Topic cmd reserved for operqtors on this channel." << std::endl;
};

void			Channel::topicModeOff()
{
	std::cout << "Topic cmd enabled for everybody on this channel." << std::endl;
};
