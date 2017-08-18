#ifndef QUOTE_H_
#define QUOTE_H_

#include "ThostFtdcUserApiDataType.h"
#include "ThostFtdcUserApiStruct.h"
#include "ThostFtdcMdApi.h"
#include <string>

class CtpMdSpi : public CThostFtdcMdSpi
{
public:
    CtpMdSpi( CThostFtdcMdApi *api );
    virtual ~CtpMdSpi( void );

    virtual void OnRspError( CThostFtdcRspInfoField *pRspInfo,
                             int nRequestID,
                             bool bIsLast );

    virtual void OnHeartBeatWarning( int nTimeLapse );

    virtual void OnFrontConnected( void );

    virtual void OnFrontDisconnected( int nReason );

    virtual void OnRspUserLogin( CThostFtdcRspUserLoginField *pUserLogin,
                                 CThostFtdcRspInfoField *pRspInfo,
                                 int nRequestID,
                                 bool bIsLast );

    virtual void OnRspSubMarketData( CThostFtdcSpecificInstrumentField *pSpecificInstrument,
                                     CThostFtdcRspInfoField *pRspInfo,
                                     int nRequestID,
                                     bool bIsLast );

    virtual void OnRspUnSubMarketData( CThostFtdcSpecificInstrumentField *pSpecificInstrument,
                                       CThostFtdcRspInfoField *pRspInfo,
                                       int nRequestID,
                                       bool bIsLast );

    virtual void OnRtnDepthMarketData( CThostFtdcDepthMarketDataField *pDepthMarketData );    

    virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp);
    
public:
    void ReqUserLogin( void );
    void SubscribeInstrument( const char* inst );
    bool IsErrorRspInfo( CThostFtdcRspInfoField *pRspInfo );

private:
    CThostFtdcMdApi*    _pUserApi; 
    char*               _pInstArr;

private:
    static int          _requestId;
};

extern void QuoteService( void );

#endif
