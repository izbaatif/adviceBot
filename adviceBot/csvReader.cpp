#include "csvReader.h"
#include<iostream>
#include<fstream>

csvReader::csvReader()
{

};

std::vector<orderBookEntry> csvReader:: readCSV(std::string csvFilename)
{
    std::vector<orderBookEntry> entries;

    std::ifstream csvFile{csvFilename};
    std::string line;

     if (csvFile.is_open())
    {
        
        while(std::getline( csvFile , line))
        {
            try{
                orderBookEntry obe = stringsToOBE(tokenise ( line , ','));
                entries.push_back(obe);
            }
            catch(std::exception& e)
            {
                std::cout << "csvReader:: readCSV bad data"  <<  std::endl;
            }
            
            
            /*for(std::string& t : tokens)
            {
                std::cout << t << std::endl;
            };*/
        };

        std::cout << "csvReader:: readCSV read " << entries.size() << " entries" <<  std::endl;
        //csvFile.close();
    }

    /*else
    {
        std::cout << "Could not open" << std:: endl;
    }*/

    return entries;
};

std::vector<std::string> csvReader:: tokenise(std::string csvLine , char separator)
{
    //stores the tokens
    std::vector <std::string> tokens;
  
    //int start and end for position. The values can be positive if its there and negative otherwise
    //stores token
    signed int start,end;
    std::string token;

    //finds strings that dont start with separator(,) or 0 and stores it in start
    start = csvLine.find_first_not_of( separator , 0 );

    //do while loop
    do{
        //sets end as next separator after start by finding first separator after start
        end = csvLine.find_first_of( separator, start );

        //checks if line has ended
        if(start == csvLine.length() || start == end) break;

        //finds token if line hasn't ended
        if(end>=0) token = csvLine.substr( start, end-start );

        //for end
        else token = csvLine.substr( start , csvLine.length() - start);

        //saves token in tokens
        tokens.push_back(token);

        //move past this token
        start = end + 1;

    }while(end>0);

    return tokens;
};

orderBookEntry csvReader:: stringsToOBE(std::vector<std::string> tokens)
{
    double price, amount;

    if(tokens.size() != 5)
            {
                std::cout << "csvReader::stringsToOBE : Bad line" << std::endl;
                throw std::exception{};
            };

            try{

                price = std::stod(tokens[3]);
                amount = std::stod(tokens[4]);

            }
            catch(const std::exception& e)
            {
                std::cout << "csvReader::stringsToOBE : Bad float" << std::endl;
                throw;
            };

    
    orderBookEntry obe{price,
                       amount,
                       tokens[0],
                       tokens[1],
                       orderBookEntry::strToOBT(tokens[2])};
    return obe;
};

orderBookEntry csvReader::stringsToOBE(std::string priceString,
                                           std::string amountString,
                                           std::string timestamp,
                                           std::string product,
                                           orderBookType orderType)
{
    double price, amount;
    try{
            price = std::stod(priceString);
            amount = std::stod(amountString);

        }
    catch(const std::exception& e)
        {
            std::cout << "csvReader::stringsToOBE : Bad float" << priceString << " and/or " << amountString<< std::endl;
            throw;
        };

    orderBookEntry obe{price,
                       amount,
                       timestamp,
                       product,
                       orderType};
    return obe;
};