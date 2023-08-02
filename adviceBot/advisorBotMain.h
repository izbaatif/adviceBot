#pragma once

#include <vector>
#include <string>
#include <algorithm>

#include "orderBookEntry.h"
#include "orderBook.h"
#include "csvReader.h"

class advisorBotMain
{
    public:
        advisorBotMain();
        /** Call this to start the sim */
        void init();
    private: 
        void help();
        void helpcmd(std::vector<std::string> Tokens);
        void getProd(std::vector<std::string> p);
        void getMin(std::vector<std::string> Tokens, std::vector<std::string> p);
        void getMax(std::vector<std::string> Tokens, std::vector<std::string> p);
        void getAvg(std::vector<std::string> Tokens, std::vector<std::string> p);
        void predict(std::vector<std::string> Tokens, std::vector<std::string> p);
        void getCommon(std::vector<std::string> Tokens, std::vector<std::string> p);
        void TimeFrame();
        void Step();

        std::vector<std::string> Products();
        std::vector<std::string> getUserOption();
        void processUserOption(std::vector<std::string> userOption, std::vector<std::string> Products);

        std::string currentTime;

        orderBook OrderBook{"20200601.csv"};

};