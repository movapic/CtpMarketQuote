#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "connect.h"

class CtpMdSpi;

//data
extern CtpMdSpi* QuoteServicePtr;
extern std::string TradingDate;
extern std::string OutputPath;
extern std::string ConnectionFile;
extern Connection  ConnectConfigure;

//interface
extern void CommandInterpret( int argc, char *argv[] );
extern void ConnectionConfigure(void);
extern void Kill( int );

#endif
