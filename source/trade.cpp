#include <iostream>
#include <cstring>
#include <sys/time.h>
#include "global.h"
#include "worke.h"
#include "trade.h"

int CtpTraderSpi::_requestId = 0; 

CtpTraderSpi::CtpTraderSpi( CThostFtdcTraderApi* api,
                            const CThostFtdcReqUserLoginField &loginInfo )
    : _pUserApi( api ),
      _frontID( 0 ),
      _sessionID( 0 )
{
    memset( &_loginInfo, 0, sizeof( _loginInfo ) );
    strcpy( _loginInfo.BrokerID, loginInfo.BrokerID );
    strcpy( _loginInfo.UserID, loginInfo.UserID );
    strcpy( _loginInfo.Password, loginInfo.Password );
}

CtpTraderSpi::~CtpTraderSpi( void )
{
}

void 
CtpTraderSpi::OnFrontConnected( void )
{
    this->ReqUserLogin( );
}

void 
CtpTraderSpi::ReqUserLogin( void )
{
	_pUserApi->ReqUserLogin( &_loginInfo, ++_requestId );
}

void 
CtpTraderSpi::OnRspUserLogin( CThostFtdcRspUserLoginField *pRspUserLogin,
                              CThostFtdcRspInfoField *pRspInfo, 
                              int nRequestID, 
                              bool bIsLast )
{
    if ( !IsErrorRspInfo( pRspInfo ) ) {
        if ( pRspUserLogin ) {  
            _frontID = pRspUserLogin->FrontID;
            _sessionID = pRspUserLogin->SessionID;
            TradingDate = _pUserApi->GetTradingDay();
            TradeServiceReady = true;
            this->ReqQryInstruments( );
        }
    } else {
        std::cout << "Fail to Log in Trade Front Server Due to Error "
                  << pRspInfo->ErrorID
                  << std::endl;
    }
}

void 
CtpTraderSpi::ReqQryInstruments( void )
{
    CThostFtdcQryInstrumentField req;
    memset(&req, 0, sizeof(req));
    _pUserApi->ReqQryInstrument(&req, ++_requestId);
}

void
CtpTraderSpi::OnRspQryInstrument( CThostFtdcInstrumentField *pInstrument,
                                  CThostFtdcRspInfoField *pRspInfo,
                                  int nRequestID,
                                  bool bIsLast )
{
    while(!InstrumentQueue.push(*pInstrument));
    if ( bIsLast )
    {
        InstDone = true;
    }
}

void
CtpTraderSpi::OnRspOrderInsert( CThostFtdcInputOrderField *pInputOrder, 
                                CThostFtdcRspInfoField *pRspInfo, 
                                int nRequestID, 
                                bool bIsLast )
{
}

void 
CtpTraderSpi::OnRspOrderAction( CThostFtdcInputOrderActionField *pInputOrderAction, 
                                CThostFtdcRspInfoField *pRspInfo, 
                                int nRequestID, 
                                bool bIsLast )
{
}

void
CtpTraderSpi::OnRtnOrder( CThostFtdcOrderField *pOrder )
{
}

void 
CtpTraderSpi::OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo)
{
}

void
CtpTraderSpi::OnRtnTrade( CThostFtdcTradeField *pTrade )
{
}

void 
CtpTraderSpi::OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus)
{
    while(!StatusQueue.push(*pInstrumentStatus));
}

void 
CtpTraderSpi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp)
{
}

void 
CtpTraderSpi::OnFrontDisconnected( int nReason )
{
    std::cout << "Disconnected with the Trade Front Server Due to Reason = " 
              << nReason 
              << std::endl;
}
                
void
CtpTraderSpi::OnRspError( CThostFtdcRspInfoField *pRspInfo, 
                          int nRequestID, 
                          bool bIsLast )
{
    IsErrorRspInfo( pRspInfo );
}

bool 
CtpTraderSpi::IsErrorRspInfo( CThostFtdcRspInfoField *pRspInfo )
{
    // ErrorID != 0 means that something is wrong with the response
    bool ret = ( pRspInfo && pRspInfo->ErrorID != 0 );
    return ret;
}

void TradeService( void )
{
    std::cout << OutputPath.c_str();
    CThostFtdcTraderApi *pTdUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi(OutputPath.c_str());

    CThostFtdcReqUserLoginField loginAccount;
    strcpy(loginAccount.BrokerID, ConnectConfigure.getBrokerID().c_str());
    strcpy(loginAccount.UserID, ConnectConfigure.getUserID().c_str());
    strcpy(loginAccount.Password, ConnectConfigure.getPassword().c_str());
    CtpTraderSpi *tdUserSpi = new CtpTraderSpi( pTdUserApi, loginAccount );
    pTdUserApi->RegisterSpi( ( CThostFtdcTraderSpi* )tdUserSpi );
    pTdUserApi->SubscribePublicTopic( THOST_TERT_QUICK );
    pTdUserApi->SubscribePrivateTopic( THOST_TERT_QUICK );

    char sServerAddress[64];
    std::string ip = ConnectConfigure.getTradeServerIP();
    int port = ConnectConfigure.getTradeServerPort();
    snprintf(sServerAddress, 64, "tcp://%s:%d", ip.c_str(), port);
    pTdUserApi->RegisterFront( sServerAddress );
    std::cout << sServerAddress << std::endl;

    pTdUserApi->Init( );
    pTdUserApi->Join( );
}
