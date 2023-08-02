#pragma once

#include "orderBookEntry.h"
#include <vector>
#include <string>

class csvReader
{
    public:
     csvReader();

     static std::vector<orderBookEntry> readCSV(std::string csvFile);
     static std::vector<std::string> tokenise(std::string csvLine, char separator);
    
     static orderBookEntry stringsToOBE(std::string price, 
                                        std::string amount, 
                                        std::string timestamp, 
                                        std::string product, 
                                        orderBookType OrderBookType);

    private:
     static orderBookEntry stringsToOBE(std::vector<std::string> strings);
     
};