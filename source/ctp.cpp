#include <signal.h>
#include <boost/thread/thread.hpp>
#include "global.h"

extern void StatusOutput( void );
extern void TickOutput( void );
extern void InstSubscribe( void );
extern void QuoteService( void );
extern void TradeService( void );

int main( int argc, char *argv[] )
{
    signal( SIGINT, Kill ); 
    CommandInterpret( argc, argv );
    ConnectionConfigure( );

    boost::thread statusOutputThread( StatusOutput );
    boost::thread quoteServiceThread( QuoteService );
    boost::thread tradeServiceThread( TradeService );
    boost::thread tickOutputThread( TickOutput );
    boost::thread instSubscribeThread( InstSubscribe );

    statusOutputThread.join( );
    quoteServiceThread.join( );
    tradeServiceThread.join( );
    tickOutputThread.join( );
    instSubscribeThread.join( );

    return 0;
}
