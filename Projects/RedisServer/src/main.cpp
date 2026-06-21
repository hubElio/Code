#include "../include/RedisServer.h"
#include "../include/RedisCommandHandler.h"
#include "../include/RedisDatabase.h"
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

/**
 * @file main.cpp
 * @brief main
 */


/**
 * @brief main
 * @details runs the server
 * @param 
 * @return 
 */

int main(int argc, char * argv[]) {
    int port = 6379;

    if (argc > 1) {
        port = std::stoi(argv[1]);
    }
    
    RedisServer server(port);

    //Background persistance! dump the database every 300 seconds. (5*60 save database)
    std::thread persistanceThread([](){
        while(true) {
            std::this_thread::sleep_for(std::chrono::seconds(10)); //300
            //dump the database
            if(!RedisDatabase::getInstance().dump("dump.my_rdb"))
                std::cerr << "Error Dumping Database\n";
            else
                std::cout << "Database Dumped to dump.my_rdb\n";

        }
    });
    persistanceThread.detach();

    server.run();

    return 0;
}