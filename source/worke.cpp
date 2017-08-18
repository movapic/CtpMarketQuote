#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include "global.h"
#include "quote.h"
#include "worke.h"

boost::atomic<bool> AppRunning(true);
boost::atomic<bool> InstDone(false);
boost::atomic<bool> QuoteServiceReady(false);
boost::atomic<bool> TradeServiceReady(false);

boost::lockfree::queue<CThostFtdcInstrumentStatusField> StatusQueue(256);
boost::lockfree::queue<CThostFtdcDepthMarketDataField> TickDataQueue(1024);
boost::lockfree::queue<CThostFtdcInstrumentField> InstrumentQueue(1024);


void StatusOutput(void)
{
    while(!TradeServiceReady)
        sleep(1);

    TThostFtdcPublishPathType filePath;
    strcpy(filePath, OutputPath.c_str());
    strcat(filePath, "status.");
    strcat(filePath, TradingDate.c_str());
    strcat(filePath, ".csv");

    std::ofstream outTool;
    if(access(filePath, F_OK) != 0)
    {
        outTool.open(filePath, std::ios::out);
        outTool << "ExchangeID,InstrumentID,InstrumentStatus,EnterTime" << std::endl;
    }
    else
    {
        outTool.open(filePath, std::ios::app);
    }

    CThostFtdcInstrumentStatusField lastStatus;
    while(AppRunning)
    {
        while(StatusQueue.pop(lastStatus))
        {
            std::string status = "";
            switch(lastStatus.InstrumentStatus)
            {
                case THOST_FTDC_IS_BeforeTrading:
                status = "BeforeTrading";
                break;

                case THOST_FTDC_IS_NoTrading:
                status = "NoTrading";
                break;

                case THOST_FTDC_IS_Continous:
                status = "Continous";
                break;

                case THOST_FTDC_IS_AuctionOrdering:
                status = "AuctionOrdering";
                break;

                case THOST_FTDC_IS_AuctionBalance:
                status = "AuctionBalance";
                break;

                case THOST_FTDC_IS_AuctionMatch:
                status = "AuctionMatch";
                break;

                case THOST_FTDC_IS_Closed:
                status = "Closed";
                break;
            }

            outTool << lastStatus.ExchangeID << ","
                    << lastStatus.InstrumentID << ","
                    << status << ","
                    << lastStatus.EnterTime
                    << std::endl;
        }
    }

    while(StatusQueue.pop(lastStatus))
    {
        std::string status = "";
        switch(lastStatus.InstrumentStatus)
        {
            case THOST_FTDC_IS_BeforeTrading:
            status = "BeforeTrading";
            break;

            case THOST_FTDC_IS_NoTrading:
            status = "NoTrading";
            break;

            case THOST_FTDC_IS_Continous:
            status = "Continous";
            break;

            case THOST_FTDC_IS_AuctionOrdering:
            status = "AuctionOrdering";
            break;

            case THOST_FTDC_IS_AuctionBalance:
            status = "AuctionBalance";
            break;

            case THOST_FTDC_IS_AuctionMatch:
            status = "AuctionMatch";
            break;

            case THOST_FTDC_IS_Closed:
            status = "Closed";
            break;
        }

        outTool << lastStatus.ExchangeID << ","
                << lastStatus.InstrumentID << ","
                << status << ","
                << lastStatus.EnterTime
                << std::endl;
    }

    outTool.close( );
}

void TickOutput(void)
{
    while(!QuoteServiceReady)
        sleep(1);

    TThostFtdcPublishPathType filePath;
    strcpy(filePath, OutputPath.c_str());
    strcat(filePath, "tick.");
    strcat(filePath, TradingDate.c_str());
    strcat(filePath, ".csv");

    std::ofstream outTool;
    if(access(filePath, F_OK) != 0)
    {
        outTool.open(filePath, std::ios::out);
        outTool << "InstrumentID,TradingDate,UpdateTime,UpdateMillisec,LastPrice,Volume,Turnover,OpenPrice,HighestPrice,"
                << "LowestPrice,ClosePrice,OpenInterest,SettlementPrice,UpperLimitPrice,LowerLimitPrice,PreClosePrice,"
                << "PreOpenInterest,PreSettlementPrice,BidPrice1,AskPrice1,BidVolume1,AskVolume1" 
                << std::endl;
    }
    else
    {
        outTool.open(filePath, std::ios::app);
    }

    CThostFtdcDepthMarketDataField lastData;
    while(AppRunning)
    {
        while(TickDataQueue.pop(lastData))
        {
            outTool << lastData.InstrumentID << ","
                    << TradingDate << ","
                    << lastData.UpdateTime << "," 
                    << lastData.UpdateMillisec << ","
                    << lastData.LastPrice << ","
                    << lastData.Volume << ","
                    << lastData.Turnover << ","
                    << lastData.OpenPrice << ","
                    << lastData.HighestPrice << ","
                    << lastData.LowestPrice << ","
                    << lastData.ClosePrice << ","
                    << lastData.OpenInterest << ","
                    << lastData.SettlementPrice << ","
                    << lastData.UpperLimitPrice << ","
                    << lastData.LowerLimitPrice << ","
                    << lastData.PreClosePrice << ","
                    << lastData.PreOpenInterest << ","
                    << lastData.PreSettlementPrice << ","
                    << lastData.BidPrice1 << ","
                    << lastData.AskPrice1 << ","
                    << lastData.BidVolume1 << ","
                    << lastData.AskVolume1
                    << std::endl;
        }
    }

    while(TickDataQueue.pop(lastData))
    {
        outTool << lastData.InstrumentID << ","
                << TradingDate << ","
                << lastData.UpdateTime << "," 
                << lastData.UpdateMillisec << ","
                << lastData.LastPrice << ","
                << lastData.Volume << ","
                << lastData.Turnover << ","
                << lastData.OpenPrice << ","
                << lastData.HighestPrice << ","
                << lastData.LowestPrice << ","
                << lastData.ClosePrice << ","
                << lastData.OpenInterest << ","
                << lastData.SettlementPrice << ","
                << lastData.UpperLimitPrice << ","
                << lastData.LowerLimitPrice << ","
                << lastData.PreClosePrice << ","
                << lastData.PreOpenInterest << ","
                << lastData.PreSettlementPrice << ","
                << lastData.BidPrice1 << ","
                << lastData.AskPrice1 << ","
                << lastData.BidVolume1 << ","
                << lastData.AskVolume1
                << std::endl;
    }

    outTool.close( );
}

void InstSubscribe(void)
{
    while(!QuoteServiceReady)
        sleep(1);

    CThostFtdcInstrumentField lastInst;
    while(!InstDone)
    {
        while(InstrumentQueue.pop(lastInst))
        {
            QuoteServicePtr->SubscribeInstrument(lastInst.InstrumentID);
        }
    }

    while(InstrumentQueue.pop(lastInst))
    {
        QuoteServicePtr->SubscribeInstrument(lastInst.InstrumentID);
    }
}
