#ifndef CONNECT_H__
#define CONNECT_H__

#include <string>

class Connection
{
public:
    Connection(void);
    virtual ~Connection(void);

public:
    void initialize(const std::string& cfgfile);

    std::string getMarketServerIP(void);
    int getMarketServerPort(void);
    std::string getTradeServerIP(void);
    int getTradeServerPort(void);
    std::string getBrokerID(void);
    std::string getUserID(void);
    std::string getPassword(void);

private:
    std::string market_server_ip;
    int         market_server_port;
    std::string trade_server_ip;
    int         trade_server_port;
    std::string broker_id;
    std::string user_id;
    std::string password;
};

#endif
