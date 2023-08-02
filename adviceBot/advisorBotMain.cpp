#include <iostream>

#include "advisorBotMain.h"


advisorBotMain::advisorBotMain()
{

};

void advisorBotMain::init()
{
    std::cout<< "Write the command 'help' to know more " <<std::endl;

    //Vector inputs which would store the tokens
    std::vector<std::string> inputs;
    std::vector<std::string> products;

    //Get the time now using function from orderBook
    currentTime = OrderBook.getEarliestTime();

    //So loop keeps running
    while(true)
    {
        products = Products();
        inputs = getUserOption();
        processUserOption(inputs , products);
        
    }

};


void advisorBotMain::help()
{
    // 1. Print help
    std::cout << "The available commands are help, help cmd, prod, min, max, avg, predict, common, time, step" << std:: endl;
};

void advisorBotMain::helpcmd(std::vector<std::string> Tokens)
{

    if(Tokens[1] == "prod")
    {
        //Print help for prod
        std::cout<< "prod -> ETH/BTC,DOGE/BTC " <<std::endl;
    }

    if(Tokens[1] == "min")
    {
        //Print help for min
        std::cout<< "min ETH/BTC ask -> The min ask for ETH/BTC is 1.0" <<std::endl;
    }

    if(Tokens[1] == "max")
    {
        //Print help for max
        std::cout<< "max ETH/BTC ask -> The max ask for ETH/BTC is 1.0 " <<std::endl;
    }

    if(Tokens[1] == "avg")
    {
        //Print help for average
        std::cout<< "avg ETH/BTC bid 10 -> average ETH/BTC bid over last 10 time steps " <<std::endl;
    }

    if(Tokens[1] == "predict")
    {
        //Print help for predict
        std::cout<< "predict ETH/BTC bid 10->  The average ETH/BTC ask price over the last 10 timesteps was 1.0 " <<std::endl;
    }

    if(Tokens[1]== "common")
    {
        //Print help for mid
        std::cout<< "common ETH/BTC bid -> The values of ETH/BTC bid appearing more than 1 time in current timestamp" <<std::endl;
    }

    if(Tokens[1] == "time")
    {
        //Print help for time
        std::cout<< "time -> 2020/03/17 17:01:24 " <<std::endl;
    }

    if(Tokens[1] == "step")
    {
        //Print help for step
        std::cout<< "step -> now at 2020/03/17 17:01:30" <<std::endl;
    }

};

void advisorBotMain::getProd(std::vector<std::string> p)
{
    std::cout << "Products: " << std::endl;
    
    //Loops through all values and prints them out
    for(int i=0; i<p.size(); i++)
    {
        std::cout << p[i] << std::endl;
    };
};

void advisorBotMain::getMin(std::vector<std::string> Tokens, std::vector<std::string> p)
{
    //Only run if product is in productNames vector, else give an error  
    if (std::count(p.begin(), p.end(), Tokens[1])) 
    {
        //if its an ask 
        if(Tokens[2]=="ask" || Tokens[2]=="Ask" || Tokens[2]== "ASK")
        {
            //Makes a vector Min which gets the price using product and ask
            std::vector<orderBookEntry> Mins = OrderBook.AdvisorBot(Tokens[1] , orderBookType::ask);
            //The minimum price is found using the getLowPrice function
            std::cout<<"The minimum ask for " << Tokens[1] << " is " << orderBook::getLowPrice(Mins) << std::endl;    
        }
        
        //if its bid
        else if(Tokens[2]=="bid" || Tokens[2]=="Bid" || Tokens[2]=="BID")
        {
            //Makes a vector Min which gets the price using product and bid
            std::vector<orderBookEntry> Mins = OrderBook.AdvisorBot(Tokens[1] , orderBookType::bid);
            //The minimum price is found using the getLowPrice function
            std::cout<<"The minimum bid for " << Tokens[1] << " is " << orderBook::getLowPrice(Mins) << std::endl;
        }

        //else gives an error
        else
        {
            std::cout << "Write bid or ask only" <<std::endl;
        }
    }

    else
    {
        std::cout << "Wrong product" <<std::endl;
    }
       
};

void advisorBotMain::getMax(std::vector<std::string> Tokens, std::vector<std::string> p )
{
    //Only run if product is in productNames vector  
    if (std::count(p.begin(), p.end(), Tokens[1])) 
    {
        //If its an ask
        if(Tokens[2]=="ask" || Tokens[2]=="Ask" || Tokens[2]== "ASK")
        {
            //Makes a vector Max which gets the price using product and ask
            std::vector<orderBookEntry> Max = OrderBook.AdvisorBot(Tokens[1] , orderBookType::ask);
            //The maximum price is found using the getHighPrice function
            std::cout<<"The maximum ask for " << Tokens[1] << " is "  << orderBook::getHighPrice(Max) << std::endl;    
        }
        
        //If its a bid
        else if(Tokens[2]=="bid" || Tokens[2]=="Bid" || Tokens[2]=="BID")
        {
            //Makes a vector Min which gets the price using product and bid
            std::vector<orderBookEntry> Max = OrderBook.AdvisorBot(Tokens[1] , orderBookType::bid);
            //The maximum price is found using the getHighPrice function
            std::cout<<"The maximum bid for " << Tokens[1] << " is "  << orderBook::getHighPrice(Max) << std::endl;
        }

        //else gives error
        else
        {
            std::cout << "Write bid or ask only" <<std::endl;
        }
    }

    else
    {
        std::cout << "Wrong product" <<std::endl;
    }
       
};


void advisorBotMain::getAvg(std::vector<std::string> Tokens , std::vector<std::string> p)
{
    //vector to store timestamps
    std::vector<std::string> timeStamps;

    //Set the nowTime as currentTime
    std::string nowTime = currentTime;

    //Get a vector of all the timestamps
    std::vector<std::string> allTimes;
    
    //Covert fourth token to int
    int Tot = std::stoi(Tokens[3]);

    //Get all the times and store them in allTimes
    for(std::string const& t : OrderBook.getKnownTimes())
    {
        allTimes.push_back(t);
    };

    //Now look for the i position of current time
    auto it = find(allTimes.begin(), allTimes.end(), currentTime);
 
    int index;
    // If currentTime was found
    if (it != allTimes.end())
    {
        // calculating the index of current Time
        index = it - allTimes.begin();
    };

    int last= allTimes.size();
    //use a for loop to get time stamps
    for(int i=0; i<Tot;  i++)
    {
        if(index - i < 0)
        {
            index = last - 1;
        }
        //Get the last tokens[3] timestamps
        //push them to timeStamps vector
        timeStamps.push_back(allTimes[index - i]);
    };

    //Make 2 vectors, one for sums and one for sizes
    std::vector<double>SumsForAvg; 
    std::vector<double>CountForAvg; 

    //Only run if product is in prod
    if (std::count(p.begin(), p.end(), Tokens[1])) 
    {
        //For asks
        if(Tokens[2]=="ask" || Tokens[2]=="Ask" || Tokens[2]== "ASK")
        {
            //Loops through each time stamp and finds values for it
            for( int i=0; i<timeStamps.size(); i++)
            {
                //Gets price when all conditions are met
                std::vector<orderBookEntry> Average = OrderBook.getOrders(orderBookType::ask, Tokens[1] , timeStamps[i]);
                //Pushes the total to sumForAvg
                SumsForAvg.push_back(orderBook::getTotal(Average));
                //Pushes the count to CountForAvg
                CountForAvg.push_back(Average.size());
            }
        }
        
        //For bids
        else if(Tokens[2]=="bid" || Tokens[2]=="Bid" || Tokens[2]== "BID")
        {
            //Loops through each time stamp and finds values for it
            for( int i=0; i<timeStamps.size(); i++)
            {
                //Gets price when all conditions are met
                std::vector<orderBookEntry> Average = OrderBook.getOrders(orderBookType::ask, Tokens[1] , timeStamps[i]);
                //Pushes the total to sumForAvg
                SumsForAvg.push_back(orderBook::getTotal(Average));
                //Pushes the count to CountForAvg
                CountForAvg.push_back(Average.size());
            }
        }
        //Give error        
        else
        {
            std::cout << "Write bid or ask only" <<std::endl;
        };
            
    }
    //Give error
    else
    {
        std::cout << "Wrong product" <<std::endl;
    };
    

    //Add the counts and sums and input them in TotSum and TotCount
    double TotSum=0;
    double TotCount=0;
    for(int i=0; i<SumsForAvg.size(); i++)
    {
        TotSum = TotSum + SumsForAvg[i];
    };

    for(int i=0; i<CountForAvg.size(); i++)
    {
        TotCount = TotCount + CountForAvg[i];
    };

    //Find the overall average
    double OverallAvg = TotSum/TotCount;
    std::cout << "Average " << Tokens[1] << " " << Tokens[2] << " over the last " << Tokens[3] << " timestamps is: "<< OverallAvg << std::endl;

    
};

void advisorBotMain::predict(std::vector<std::string> Tokens , std::vector<std::string> p)
{

    //vector to store timestamps
    std::vector<std::string> timeStamps;

    //Get a vector of all the timestamps
    std::vector<std::string> allTimes;
    
    //Get all times
    for(std::string const& t : OrderBook.getKnownTimes())
    {
        allTimes.push_back(t);
    };

    //Covert fourth token to int
    int Tot = std::stoi(Tokens[3]);

    //Store the rest of the tokens in strings
    std::string prodName = Tokens[1];
    std::string AskBid = Tokens[2];

    //Get last number of timestamps specified by user
    int last = allTimes.size();

    for(int i=last; i>last-Tot; i--)
    {
        timeStamps.push_back(allTimes[i]);
    };

    //Make an Averages vector
    std::vector<double> Averages;
        
    //For every timestamp get the average using getAverage function in orderBook 
    //Store it in Averages vector
    for(int i=0; i<timeStamps.size(); i++)
    {
        double EachAverage = OrderBook.getAverage(p , timeStamps[i], prodName, AskBid );
        Averages.push_back(EachAverage);
    };
        
    //Take an average of these average of the values for prediction
    double totalForAvg;

    //Add the values
    for(int i=0; i<Averages.size(); i++)
    {
        totalForAvg = totalForAvg + Averages[i];
    }

    //Get average
    double FinalPrice= totalForAvg/Tot;

    std::cout<<"The prediction for " << AskBid << " for next timestamp for " << prodName << " using the last " << Tot << " timestamps is: " <<FinalPrice <<std::endl;   
    
};

void advisorBotMain::getCommon(std::vector<std::string> Tokens , std::vector<std::string> p)
{  
    //vector for storing the common prices
    std::vector<double> CP; 

    //Only run if product is in productName
    if (std::count(p.begin(), p.end(), Tokens[1])) 
    {
        //For ask
        if(Tokens[2]=="ask" || Tokens[2]=="Ask" || Tokens[2]== "ASK")
        {
            //Gets price using product time and ask
            std::vector<orderBookEntry> Prices = OrderBook.getOrders(orderBookType::ask, Tokens[1] , currentTime);
            //Gets the common prices using function from orderBook
            CP=OrderBook.getCommonPrice(Prices);    
        }
        
        //For bid
        else if(Tokens[2]=="bid" || Tokens[2]=="Bid" || Tokens[2]== "BID")
        {
            //Gets price using product time and bid
            std::vector<orderBookEntry> Prices = OrderBook.getOrders(orderBookType::bid, Tokens[1] ,currentTime);
            //Gets the common prices using function from orderBook
            CP=OrderBook.getCommonPrice(Prices);
        }
        
        //Else error
        else
        {
            std::cout << "Write bid or ask only" <<std::endl;
        }
    }

    //Else error
    else
    {
            std::cout << "Wrong product" <<std::endl;
    };

    //When there is no common value
    if(CP.size()==0)
    {
        std::cout<<"No price appearing more than 1 times" <<std::endl;
    }
    //When common values, loops through array and displays each value
    else
    {
        for(int i=0; i<CP.size(); i++)
        {
            std::cout<<CP[i] << " , "  ;
        };

        std::cout<<" "<<std::endl;
    }
    

};


void advisorBotMain::TimeFrame()
{
    //Outputs the current time
    std::cout<< currentTime <<std::endl;
};

void advisorBotMain::Step()
{
    //Sets current time to next time using getNextTime function from orderBook
    currentTime=OrderBook.getNextTime(currentTime);
    std::cout << "Now at: " << currentTime <<std::endl;
}

std::vector<std::string> advisorBotMain::Products()
{
    std::vector<std::string>productNames;
    for(std::string const& p : OrderBook.getKnownProducts())
    {
        productNames.push_back(p);
    };

    return productNames;
};

std::vector<std::string> advisorBotMain::getUserOption()
{
    std::string userOption;

    std::cout << "Type an option" << std::endl;
    
    std::getline(std::cin, userOption);
    
    std::cout << "You chose: " << userOption << std::endl;

    //Tokenise with ' ' to read values separately
    std::vector<std::string> AdvisorBotTokens = csvReader::tokenise(userOption , ' ');

    //To check that maximum of 4 values are entered 
    if(AdvisorBotTokens.size() > 4)
    {
        std::cout << "Bad input: " << userOption << std::endl;
    }

    return AdvisorBotTokens;
};



void advisorBotMain::processUserOption( std::vector<std::string> AdvisorBotTokens , std::vector<std::string> productNames)
{
    if(AdvisorBotTokens.size()==1 && AdvisorBotTokens[0]== "help")
    {
        help();
    }

    else if(AdvisorBotTokens.size()==2 && AdvisorBotTokens[0]== "help")
    {
        helpcmd(AdvisorBotTokens);
    }


    else if(AdvisorBotTokens.size()==1 && AdvisorBotTokens[0]== "prod")
    {
        getProd(productNames);
    }

    else if(AdvisorBotTokens.size()==3 && AdvisorBotTokens[0]== "min")
    {
        getMin(AdvisorBotTokens , productNames);
    }

    else if(AdvisorBotTokens.size()==3 && AdvisorBotTokens[0]== "max")
    {
        getMax(AdvisorBotTokens , productNames);
    }

    else if(AdvisorBotTokens.size()==4 && AdvisorBotTokens[0]== "avg")
    {
        getAvg(AdvisorBotTokens , productNames);
    }

    else if(AdvisorBotTokens.size()==4 && AdvisorBotTokens[0]== "predict")
    {
        predict(AdvisorBotTokens , productNames);
    }

    else if(AdvisorBotTokens.size()==3 && AdvisorBotTokens[0]== "common")
    {
        getCommon(AdvisorBotTokens , productNames);
    }

    else if(AdvisorBotTokens.size()==1 && AdvisorBotTokens[0]== "time")
    {
        TimeFrame();
    }

    else if(AdvisorBotTokens.size()==1 && AdvisorBotTokens[0]== "step")
    {
        Step();
    }
    
    else
    {
        std::cout << "Enter a valid input" <<std::endl;
    }

    
};

