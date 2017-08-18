#include <fstream>
#include <sstream>
#include "connect.h"
#include "jansson.h"

Connection::Connection(void)
  : market_server_ip(),
    market_server_port(-1),
    trade_server_ip(),
    trade_server_port(-1),
    broker_id(),
    user_id(),
    password()
{
}

Connection::~Connection(void)
{
}

void Connection::initialize(const std::string& cfgfile)
{
    std::ifstream file(cfgfile);
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    json_error_t error;
    json_t* root = json_loadb(content.c_str(), content.length(), 0, &error);
    if(!root || !json_is_object(root))
        return;

    json_t* value = NULL;

    value = json_object_get(root, "market server ip");
    if(value)
        this->market_server_ip = json_string_value(value);

    value = json_object_get(root, "market server port");
    if(value)
        this->market_server_port = json_integer_value(value);

    value = json_object_get(root, "trade server ip");
    if(value)
        this->trade_server_ip = json_string_value(value);

    value = json_object_get(root, "trade server port");
    if(value)
        this->trade_server_port = json_integer_value(value);

    value = json_object_get(root, "broker id");
    if(value)
        this->broker_id = json_string_value(value);

    value = json_object_get(root, "user id");
    if(value)
        this->user_id = json_string_value(value);

    value = json_object_get(root, "password");
    if(value)
        this->password = json_string_value(value);
}

std::string Connection::getMarketServerIP(void)
{
    return market_server_ip;
}

int Connection::getMarketServerPort(void)
{
    return market_server_port;
}

std::string Connection::getTradeServerIP(void)
{
    return trade_server_ip;
}

int Connection::getTradeServerPort(void)
{
    return trade_server_port;
}

std::string Connection::getBrokerID(void)
{
    return broker_id;
}

std::string Connection::getUserID(void)
{
    return user_id;
}

std::string Connection::getPassword(void)
{
    return password;
}
