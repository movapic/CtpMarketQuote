#ifndef TRADE_H_
#define TRADE_H_

#include "ThostFtdcTraderApi.h"

class CtpTraderSpi : public CThostFtdcTraderSpi
{
public:
    CtpTraderSpi( CThostFtdcTraderApi* api, 
                  const CThostFtdcReqUserLoginField &loginInfo );

    virtual ~CtpTraderSpi( void );

    /// Be invoked after the client is connected to the CTP server
    /// Called before login
    virtual void OnFrontConnected( void );

    /// Notify the client whether the login was accepted by the srever
    virtual void OnRspUserLogin( CThostFtdcRspUserLoginField *pRspUserLogin,
                                 CThostFtdcRspInfoField *pRspInfo, 
                                 int nRequestID, 
                                 bool bIsLast );

    /// Response the request of order insertion
    virtual void OnRspOrderInsert( CThostFtdcInputOrderField *pInputOrder, 
                                   CThostFtdcRspInfoField *pRspInfo, 
                                   int nRequestID, 
                                   bool bIsLast );

    /// Response the request of order cancellation
    virtual void OnRspOrderAction( CThostFtdcInputOrderActionField *pInputOrderAction, 
                                   CThostFtdcRspInfoField *pRspInfo, 
                                   int nRequestID, 
                                   bool bIsLast );

    /// Error notification caused by the client request
    virtual void OnRspError( CThostFtdcRspInfoField *pRspInfo, 
                             int nRequestID, 
                             bool bIsLast );
        
    /// Called when the client and the server are disconnected
    virtual void OnFrontDisconnected( int nReason );
                
    /// Notify the client about the change of order status
    virtual void OnRtnOrder( CThostFtdcOrderField *pOrder );

    virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo);

    /// Notify the client when the trade is done
    virtual void OnRtnTrade( CThostFtdcTradeField *pTrade );

    virtual void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus);

    virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument,
                                    CThostFtdcRspInfoField *pRspInfo,
                                    int nRequestID,
                                    bool bIsLast);

    virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp);

public:
    void ReqUserLogin( void );

    void ReqQryInstruments(void);

    bool IsErrorRspInfo( CThostFtdcRspInfoField *pRspInfo );

private:

private:
    CThostFtdcTraderApi *_pUserApi;
    CThostFtdcReqUserLoginField _loginInfo;

    int _frontID;
    int _sessionID;
    
private:
    static int _requestId;
};

extern void TradeService( void );

#endif
