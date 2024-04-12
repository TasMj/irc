#include "Message.hpp"

static std::deque<std::string> parse_params(std::string& input, std::string del) {
    std::deque<std::string> output;
    std::string word;

    int start, end = -1* del.size();
    do 
    {
        start = end + del.size();
        end = input.find(del, start);
        word = input.substr(start, end - start);
        if (!word.empty())
            output.push_back(word);
    } while (end != -1);
    return (output);
}

static bool    parse_last_params(std::string& output, std::string& input) {
    size_t  found = input.find(":");
    if (found == std::string::npos)
        return (false);
    output = input.substr(found);
    input.erase(found);
    std::cout << input << std::endl;
    return (true);
}

static bool    parse_prefix_host(std::string& output, std::string& input) {
    size_t found = input.rfind("@");
    if (found == std::string::npos)
        return (false);
    output = input.substr(found);
    input.erase(found);
    return (true);
}

static bool    parse_prefix_user(std::string& output, std::string& input) {

    size_t found = input.rfind("!");
    if (found == std::string::npos)
        return (false);
    output = input.substr(found);
    input.erase(found);
    return (true);
}

static bool    parse_prefix(t_prefix& output, std::string& input) {
    if (input[0] != ':')
        return (false);
    size_t found = input.find(" ");
    if (found == std::string::npos)
        throw std::invalid_argument("Invalid syntax on prefix parssing. Missing space in the input");
    std::string toOperate = input.substr(1, found);
    input.erase(0, found + 1);
    output.has_host = parse_prefix_host(output.host, toOperate);
    output.has_user = parse_prefix_user(output.user, toOperate);
    output.nickname = toOperate;
    return (true);
}

t_message*   parse_message(std::string& input) {
    t_message* output;
    size_t found;
    
    found = input.find("\r\n");
    if (found == std::string::npos)
        return (NULL);
    output = new t_message;
    if (output == NULL)
        throw std::runtime_error("Unable to allocate memory for a incomming message");
    std::string toParse = input.substr(0, found);
	output->raw = toParse;
    input.erase(0, found + 2);
    output->has_last_params = false; // not the best way, but ok
    output->has_prefix = parse_prefix(output->prefix, toParse);
    found = toParse.find(" ");
    if (found == std::string::npos) {
        output->command = toParse;
        return (output);
    }
    output->command = toParse.substr(0, found);
    toParse.erase(0, found);
    output->has_last_params = parse_last_params(output->last_params, toParse);
    output->params = parse_params(toParse, " ");
    return (output);
}

std::ostream& operator<<(std::ostream& os, t_message& msg) {
    os << PUR;
	os << msg.raw << "\n";
    os << "MESSAGE: {\n";
    if (msg.has_prefix) {
        os << "\tPREFIX: {\n";
        os << "\t\tnickname: " << msg.prefix.nickname << "\n";
        if (msg.prefix.has_user)
            os << "\t\tuser: " << msg.prefix.user << "\n";
        if (msg.prefix.has_host)
            os << "\t\thost: " << msg.prefix.host << "\n";
        os << "\t}\n";
    }
    os << "\tCOMMAND: " << msg.command << "\n";
    if (!msg.params.empty()) {
        os << "\tPARAMS: [";
        for (size_t i = 0; i < msg.params.size(); i++) {
            os << msg.params[i] << ",";
        }
        os << "\b]\n";
    }
    if (msg.has_last_params)
        os << "\tLAST PARAM: " << msg.last_params << "\n";
    os << "}\n"; 
    os << WHI;
    return (os);
}
