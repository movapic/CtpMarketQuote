#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <string>
#include <map>

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        exit(1);
    }
    char* logfile = argv[1];
    char* date = argv[2];

    std::ifstream inStream(logfile);
    if(!inStream.is_open())
    {
        std::cout << "Fail to open log file " << logfile << std::endl;
        exit(1);
    }

    std::map<std::string, std::string> instFileNameMap;
    char title[1024];
    if(!inStream.eof())
    {
        inStream.getline(title, 1023);
    }

    char line[1024];
    while(!inStream.eof())
    {
        std::ofstream outStream;

        inStream.getline(line, 1023);
        char *part = strtok(line, ",");
        int index = 0;
        while(part)
        {
            if(index == 0)
            {
                std::string outfilename = "";
                std::map<std::string, std::string>::iterator it = instFileNameMap.find(part);
                if(it == instFileNameMap.end())
                {
                    outfilename = part;
                    if(date != NULL)
                    {
                        outfilename += "_";
                        outfilename += date;
                    }
                    outfilename += ".csv";
                    instFileNameMap.insert(std::make_pair(part, outfilename));
                    outStream.open(outfilename.c_str(), std::ios::app);
                    outStream << title << std::endl;
                    outStream << part;
                }
                else
                {
                    outfilename = it->second;
                    outStream.open(outfilename.c_str(), std::ios::app);
                    outStream << part;
                }
            }
            else
            {
                outStream << "," << part;
            }

            part = strtok(NULL, ",");
            ++index;
        }

        if(outStream.is_open())
        {
            outStream << std::endl;
            outStream.close();
        }
    }

    return 0;
}
