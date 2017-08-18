#ifndef STORE_H_
#define STORE_H_

#include <boost/lockfree/queue.hpp>
#include <boost/atomic.hpp>
#include "ThostFtdcUserApiStruct.h"

extern boost::atomic<bool> AppRunning;
extern boost::atomic<bool> InstDone;
extern boost::atomic<bool> QuoteServiceReady;
extern boost::atomic<bool> TradeServiceReady;

extern boost::lockfree::queue<CThostFtdcInstrumentStatusField> StatusQueue;
extern boost::lockfree::queue<CThostFtdcDepthMarketDataField> TickDataQueue;
extern boost::lockfree::queue<CThostFtdcInstrumentField> InstrumentQueue;

extern void StatusOutput(void);
extern void TickOutput(void);
extern void InstSubscribe(void);

#endif
