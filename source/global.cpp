#include <unistd.h>
#include <string>
#include "worke.h"
#include "global.h"

CtpMdSpi* QuoteServicePtr = NULL;
std::string TradingDate;
std::string OutputPath;
std::string ConnectionFile;
Connection  ConnectConfigure;

void CommandInterpret( int argc, char *argv[] )
{
    std::string curPath = get_current_dir_name();

    const char * outpath = "--outpath=";
    const char * cfgfile = "--cfgfile=";
    int outlen = strlen(outpath);
    int cfglen = strlen(cfgfile);
    for ( int idx = 1; idx < argc; ++idx )
    {
        if(strncmp(argv[idx], outpath, outlen) == 0)
        {
            if(argv[idx][outlen] != '/')
            {
                OutputPath = curPath + "/";
                OutputPath += argv[idx]+outlen;
            }
            else
            {
                OutputPath = argv[idx]+outlen;
            }
            OutputPath += "/";
        }
        else if(strncmp(argv[idx], cfgfile, cfglen) == 0)
        {
            if(argv[idx][cfglen] != '/')
            {
                ConnectionFile = curPath + "/";
                ConnectionFile += argv[idx]+cfglen;
            }
            else
            {
                ConnectionFile = argv[idx]+cfglen;
            }
        }
    }
}

void ConnectionConfigure(void)
{
    if(ConnectionFile.empty())
        return;

    ConnectConfigure.initialize(ConnectionFile);
}

void Kill( int )
{
    AppRunning = false;
    sleep(1);
    exit(0);
}

