TARGET := tickquote
CC := g++ -std=c++11
DFLAG = -g
CFLAG := -c
INCLUDE := ../include
BOOSTLIB := -lboost_thread -lboost_system
THIRDLIB := -L../dynlib -lthostmduserapi -lthosttraderapi -ljansson

all :
	$(CC) $(DFLAG) $(CFLAG) -o global.o global.cpp -I$(INCLUDE)
	$(CC) $(DFLAG) $(CFLAG) -o connect.o connect.cpp -I$(INCLUDE)
	$(CC) $(DFLAG) $(CFLAG) -o worke.o worke.cpp -I$(INCLUDE)
	$(CC) $(DFLAG) $(CFLAG) -o quote.o quote.cpp -I$(INCLUDE)
	$(CC) $(DFLAG) $(CFLAG) -o trade.o trade.cpp -I$(INCLUDE)
	$(CC) $(DFLAG) -o $(TARGET) ctp.cpp *.o -I$(INCLUDE) $(BOOSTLIB) $(THIRDLIB)
	@rm *.o

clean :
	rm -f $(TARGET)
