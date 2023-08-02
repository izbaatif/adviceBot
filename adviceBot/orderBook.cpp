#include "orderBook.h"
#include "csvReader.h"
#include <map>
#include <algorithm>
#include<iostream>

orderBook::orderBook(std::string filename)
{
    orders = csvReader::readCSV(filename);
};
        
        
std::vector<std::string> orderBook::getKnownProducts()
{
    //Vector for storing
    std::vector<std::string> products;

    std::map<std::string,bool> prodMap;

    for(orderBookEntry& e : orders)
    {
        prodMap[e.product] = true;
    };

    for(auto const& e : prodMap)
    {
        products.push_back(e.first);
    };

    return products;
};

std::vector<std::string> orderBook::getKnownTimes()
{
    //Vector for storing
    std::vector<std::string> times;

    std::map<std::string,bool> timeMap;

    for(orderBookEntry& e : orders)
    {
        timeMap[e.timestamp] = true;
    };

    for(auto const& e : timeMap)
    {
        times.push_back(e.first);
    };

    return times;
};



std::vector<orderBookEntry> orderBook:: getOrders(orderBookType type,
                                               std::string product,
                                               std::string timestamp)
{
    //Vector for storing
    std::vector<orderBookEntry> orders_sub;
    
    //Loops through orderBookEntry
    for(orderBookEntry& e : orders)
    {
        //If products and type match then add to the vector
        if(e.orderType==type && e.product==product && e.timestamp==timestamp)
        {
            orders_sub.push_back(e);
        }
    };

    //returns the vector
    return orders_sub;
};

std::vector<orderBookEntry> orderBook:: AdvisorBot(std::string product, orderBookType type)
{
    //Vector for storing
    std::vector<orderBookEntry> advisor;
    
    //Loops through orderBookEntry
    for(orderBookEntry& e : orders)
    {
        //If products and type match then add to the vector
        if(e.product==product && e.orderType==type)
        {
            advisor.push_back(e);
        }
    };

    //returns the vector
    return advisor;
};


double orderBook:: getHighPrice( std::vector<orderBookEntry>& orders)
{
    //Sets max as first price
    double max = orders[0].price;

    //Loops through orders and if price is higher than max, sets it as max
    for(orderBookEntry& e : orders)
    {
        if(e.price > max)
        {
            max=e.price;
        }
    }

    return max;
};


double orderBook:: getLowPrice( std::vector<orderBookEntry>& orders)
{
    //Sets min as first price
    double min = orders[0].price;

    //Loops through orders and if price is higher than max, sets it as min
    for(orderBookEntry& e : orders)
    {
        if(e.price < min)
        {
            min=e.price;
        }
    }
    
    return min;
};

std::vector<double> orderBook:: getCommonPrice( std::vector<orderBookEntry>& orders)
{
    //Prices
    std::vector<double>Prices;

    //Vector for storing prices with duplicates
    std::map<double, bool> DPrices;

    //Vector for storing prices without duplicates
    std::vector<double> CommonPrices;

    //Loops through orders
    for(int i=0; i<orders.size(); i++)
    {
        //Sets initial count as 1
        int count=1;

        //Loops through orders again and compares the each entry with every other entry
        for(int j=0; j<orders.size(); j++)
        {
            //If 2 entries are the same count is increased by 1
            if (i==j)
            {
                count+=1;
            } 
        };
        
        //If count is greater than 1, that prices is added to the vector
        if(count>1)
        {
            Prices.push_back(orders[i].price);
        }
    };

    //Removing duplicates
    for(double& e : Prices)
    {
        DPrices[e]=true;
    };

    for(auto const& e : DPrices)
    {
        CommonPrices.push_back(e.first);
    };

    return CommonPrices;
};

double orderBook::getTotal(std::vector<orderBookEntry> & orders)
{
    //Sets it as 0
    double total=0;
    
    //Loops through orders
    for(orderBookEntry& e: orders)
    {
        //Add the price to total at each iteration
        total = total + e.price;
    }

    return total;
};

double orderBook::getAverage(std::vector<std::string>p , std::string t , std::string pName, std::string BA)
{
    //Make 2 vectors, one for sums and one for sizes
    std::vector<double>SumsForAvg; 
    std::vector<double>CountForAvg; 

    //Check if product is in vector p
    if (std::count(p.begin(), p.end(), pName)) 
    {
        //Compares BA to ask
        if(BA=="ask")
        {
            //Gets orders for ask type and product and timestamp and store them in a vector average
            std::vector<orderBookEntry> Average = getOrders(orderBookType::ask, pName , t);
            //Get their total using getTotal and store it in SumsForAvg
            SumsForAvg.push_back(orderBook::getTotal(Average));
            //Add size to CountForAvg
            CountForAvg.push_back(Average.size());
               
        }
        
        //Compares BA to bid
        else if(BA=="bid")
        {
            //Gets orders for bid type and product and timestamp
            std::vector<orderBookEntry> Average = getOrders(orderBookType::ask, pName , t);
            //Get their total using getTotal and store it in SumsForAvg
            SumsForAvg.push_back(orderBook::getTotal(Average));
            //Add size to CountForAvg
            CountForAvg.push_back(Average.size());
        }

        //else error        
        else
        {
            std::cout << "Write bid or ask only" <<std::endl;
        };
            
    }

    //else error
    else
    {
        std::cout << "Wrong product" <<std::endl;
    };
    

    //Add the counts and sums
    double TotSum=0;
    double TotCount=0;
    //Use loop to add
    for(int i=0; i<SumsForAvg.size() + 1; i++)
    {
        TotSum = TotSum + SumsForAvg[i];
    };
    //Use loop to add
    for(int i=0; i<CountForAvg.size() + 1; i++)
    {
        TotCount = TotCount + CountForAvg[i];
    };
    //Calculate their average
    double OverallAvg = TotSum/TotCount;
    return OverallAvg;
};

std::string orderBook::getEarliestTime()
{
    //Since ascending order so get first timestamp
    return orders[0].timestamp;
};

std::string orderBook::getNextTime(std::string timestamp)
{
    std::string next_timestamp="";
    for(orderBookEntry& e : orders)
    {
        if(e.timestamp > timestamp)
        {
            next_timestamp=e.timestamp;
            break;
        };
    };

    if(next_timestamp=="")
    {
        next_timestamp = orders[0].timestamp;
    };

    return next_timestamp;

};

/*std::string orderBook::getPreviousTime(std::string timestamp)
{
    std::string prev_timestamp="";
    while(prev_timestamp != "")
    {
        for(orderBookEntry& e : orders)
        {
            if(e.timestamp < timestamp)
            {
                prev_timestamp=e.timestamp;
                break;
            };
        }
        
    };

    int last = orders.size();
    if(prev_timestamp=="")
    {
        prev_timestamp = orders[last - 1].timestamp;;
    };

    return prev_timestamp;
};*/

