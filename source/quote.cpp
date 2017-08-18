#include <iostream>
#include <cstring>
#include <sys/time.h>
#include "global.h"
#include "quote.h"
#include "worke.h"

int CtpMdSpi::_requestId = 0;

CtpMdSpi::CtpMdSpi( CThostFtdcMdApi *api )
    : _pUserApi( api )
{
    _pInstArr = new char[64];
    memset(_pInstArr, 0, 64);
}

CtpMdSpi::~CtpMdSpi( void )
{
    delete [] _pInstArr;
    _pInstArr = NULL;
}

void
CtpMdSpi::OnRspError( CThostFtdcRspInfoField *pRspInfo, 
                      int nRequestID, 
                      bool bIsLast )
{
    IsErrorRspInfo( pRspInfo );
}

void
CtpMdSpi::OnHeartBeatWarning( int nTimeLapse )
{
}

void
CtpMdSpi::OnFrontConnected( )
{
    this->ReqUserLogin( );
}

void
CtpMdSpi::OnFrontDisconnected( int nReason )
{
    std::cout << "Disconnected with Market Data Front Server Because of Reason " 
              << nReason 
              << std::endl;
}

void
CtpMdSpi::ReqUserLogin( void )
{
    CThostFtdcReqUserLoginField loginInfo;
    _pUserApi->ReqUserLogin( &loginInfo, ++_requestId );
}

void
CtpMdSpi::OnRspUserLogin( CThostFtdcRspUserLoginField *pRspUserLogin,
                          CThostFtdcRspInfoField *pRspInfo, 
                          int nRequestID, 
                          bool bIsLast )
{
    if ( !IsErrorRspInfo( pRspInfo ) ) {
        if ( pRspUserLogin ) {
            QuoteServiceReady = true;
        }
    } else {
        std::cout << "Fail to Log in Market Data Front Server Due to Error "
                  << pRspInfo->ErrorID
                  << std::endl;
    }
}

void
CtpMdSpi::OnRspSubMarketData( CThostFtdcSpecificInstrumentField *pSpecificInstrument, 
                              CThostFtdcRspInfoField *pRspInfo, 
                              int nRequestID, 
                              bool bIsLast)
{
    if ( !IsErrorRspInfo( pRspInfo ) ) {
        if ( pSpecificInstrument ) {
#if 0
            std::cout << "Subscribing the Instrument " 
                      << pSpecificInstrument->InstrumentID 
                      << "...Done"
                      << std::endl;
#endif
        }
    } else {
        std::cout << "Fail to Subscribe the Instrument "
                  << pSpecificInstrument->InstrumentID
                  << " Due to Error "
                  << pRspInfo->ErrorID
                  << std::endl;
    }
}

void
CtpMdSpi::OnRspUnSubMarketData( CThostFtdcSpecificInstrumentField *pSpecificInstrument,
                                CThostFtdcRspInfoField *pRspInfo, 
                                int nRequestID, 
                                bool bIsLast )
{
    if ( !IsErrorRspInfo( pRspInfo ) ) {
        if ( pSpecificInstrument ) {
            std::cout << "Unsubscribing the Instrument " 
                      << pSpecificInstrument->InstrumentID 
                      << "...Done"
                      << std::endl;
        }
    } else {
        std::cout << "Fail to Unsubscribe the Instrument "
                  << pSpecificInstrument->InstrumentID
                  << " Due to Error "
                  << pRspInfo->ErrorID
                  << std::endl;
    }
}

void
CtpMdSpi::OnRtnDepthMarketData( CThostFtdcDepthMarketDataField *pDepthMarketData )
{
    while(!TickDataQueue.push(*pDepthMarketData));
}

void 
CtpMdSpi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp)
{
    std::cout << pForQuoteRsp->InstrumentID << ", " << pForQuoteRsp->ForQuoteSysID << ", " << pForQuoteRsp->ForQuoteTime << std::endl;
}

bool
CtpMdSpi::IsErrorRspInfo( CThostFtdcRspInfoField *pRspInfo )
{        
    bool ret = ( pRspInfo && pRspInfo->ErrorID != 0 );
    return ret;
}

void 
CtpMdSpi::SubscribeInstrument( const char* inst )
{
    strncpy(_pInstArr, inst, 64);
    _pUserApi->SubscribeMarketData( &_pInstArr, 1 );
}

void QuoteService( void )
{
    sleep( 1 );
    CThostFtdcMdApi *pMdUserApi = CThostFtdcMdApi::CreateFtdcMdApi( OutputPath.c_str() );
    QuoteServicePtr = new CtpMdSpi( pMdUserApi );
    pMdUserApi->RegisterSpi( QuoteServicePtr );

    char sServerAddress[64];
    std::string ip = ConnectConfigure.getMarketServerIP();
    int port = ConnectConfigure.getMarketServerPort();
    snprintf(sServerAddress, 64, "tcp://%s:%d", ip.c_str(), port);
    pMdUserApi->RegisterFront( sServerAddress );

    pMdUserApi->Init( ); 
    pMdUserApi->Join( );
}
