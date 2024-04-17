
#include "Channel.hpp"

Channel::Channel(std::string name, std::string* password)
    : _name(name)
    , _password(NULL)
	, _inviteModeOn(false)
	, _keyModeOn(false)
	, _topicModeOn(false)
	, _limitModeOn(false)
{
    _topic = "";
    if (password != NULL) {
        _password = new std::string(*password);
		_keyModeOn = true;
    }
}

Channel::~Channel() {
	delete _password;
}

bool		Channel::join(Client* cli, std::string* password) {
	std::string nickName = cli->get_nickName();
    if (_password) {
        if (password == NULL || (password != NULL && _password->compare(*password) != 0)) {
			cli->setBufferOut (ERR_CHANWRONGPASS(nickName, _name, "Cannot join channel (+k)"));
			return (false);
		}
    }
	if (_inviteModeOn && !checkInvited(cli)) {
		cli->setBufferOut (ERR_CHANNELUSERNOTINVIT(nickName, _name, "Cannot join channel (+i)"));
		return (false);
	}

	if (_limitModeOn && _clients.size() + 1 >= _limit) {
		cli->setBufferOut (ERR_CHANNELISFULL(nickName, _name, "Cannot join channel, it is full."));
		return (false);
	}

    _clients.insert(std::make_pair(cli->get_nickName(), cli));
	sendToAllClients(RPL_JOIN(cli, _name));
    return (true);
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

bool		Channel::isInChannel(std::string name)
{
    if (_clients.find(name) != _clients.end())
        return (true);
    return (false);
}

t_channel   Channel::asPair(void) {
    return (std::make_pair(_name, this));
}

void	Channel::removeClient(Client* cli) {
	if (cli == NULL)
		return; // TODO should never happend
	std::vector<Client*>::iterator invited;
	invited = std::find(_invited.begin(), _invited.end(), cli);
	if (invited != _invited.end())
		_invited.erase(invited);

	std::vector<Client*>::iterator operators;
	operators = std::find(_operators.begin(), _operators.end(), cli);
	if (operators != _operators.end())
		_operators.erase(operators);

	t_clients_map::iterator	it;
	it = _clients.find(cli->get_nickName());
	if (it != _clients.end())
		_clients.erase(it);
}
