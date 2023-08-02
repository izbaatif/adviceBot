#pragma once
#include "orderBookEntry.h"
#include "csvReader.h"
#include <string>
#include <vector>

class orderBook
{
    public:
        orderBook(std::string filename);
        std::vector<std::string> getKnownProducts();
        std::vector<std::string> getKnownTimes();

        std::vector<orderBookEntry> getOrders(orderBookType type, 
                                              std::string product, 
                                              std::string timestamp);

        std::vector<orderBookEntry> AdvisorBot(std::string product, orderBookType type);

        std::string getEarliestTime();
       
        std::string getNextTime(std::string timestamp);
        //std::string getPreviousTime(std::string timestamp);

        static double getHighPrice(std::vector<orderBookEntry>& orders);
        static double getLowPrice(std::vector<orderBookEntry>& orders);
        std::vector<double> getCommonPrice(std::vector<orderBookEntry>& orders);

        static double getTotal(std::vector<orderBookEntry> & orders);
        double getAverage(std::vector<std::string>p , std::string t , std::string pName, std::string BA);

    private:
        std::vector<orderBookEntry> orders;

};