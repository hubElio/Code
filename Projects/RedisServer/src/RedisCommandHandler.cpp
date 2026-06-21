#include "../include/RedisCommandHandler.h"
#include "../include/RedisDatabase.h"


/**
 * @file RedisCommandHandler.cpp
 * @brief RedisCommandHandler handles command sent to the server. it parses it and sends a response
 */


/**
 * @brief Parses the inputs
 * @details RESP parser : 
 * \*2\\r\\n$4\\r\\n\\PING\\r\\n$4\\r\\nTEST\\r\\n2\* means 2 elements (here ping and test), $4 is for 4 caracters (T E S T and P I N G)
 * @param input a string
 * @return tokens vector of strings with the commands
 */

std::vector<std::string> parseRespCommand(const std::string &input) {
    std::vector<std::string> tokens;
    if(input.empty()) return tokens;
    //if it doesn't start with '*', fallback to splitting by whitesapces
    if(input[0] != '*') {
        std::istringstream iss(input);
        std::string token;
        while(iss >> token)
            tokens.push_back(token);
        return tokens;
    }

    size_t pos = 0;
    //expect '*' followed by number of elements
    if (input[pos] != '*') return tokens;
    pos++; // skip '*'

    //crlf = Carriage Return (\r), line feed (\n)
    size_t crlf = input.find("\r\n", pos);
    if(crlf == std::string::npos) return tokens;

    int numElements = std::stoi(input.substr(pos, crlf - pos));
    pos = crlf + 2;

    for(int i = 0; i < numElements; i++) {
        if(pos >= input.size() || input[pos] != '$') break; //format error
        pos++; // skip '$'

        crlf = input.find("\r\n", pos);
        if(crlf == std::string::npos) break;
        int len = std::stoi(input.substr(pos, crlf - pos));
        pos = crlf +2;

        if(pos + len > input.size()) break;
        std::string token = input.substr(pos, len);
        tokens.push_back(token);
        pos += len+2;
    }
    return tokens;
}

RedisCommandHandler::RedisCommandHandler() {}

/**
 * @brief Retrieves sent input, uses the parse function and Generates a response
 * @details 
 * @param commandline a string like *2\r\n$4\r\n\PING\r\n$4\r\nTEST\r\n
 * @return response an ostringstream
 */

std::string RedisCommandHandler::processCommand(const std::string& commandline) {

    //use RESP parser
    auto tokens = parseRespCommand(commandline);
    if(tokens.empty()) return "-Error: Empty command\r\n";

    // std::string out;
    // for(auto& t : tokens) {
    //     out += t + " ";
    //     std::cout << out << std::endl;
    // }

    std::string cmd = tokens[0];
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
    std::ostringstream response;
    // connect to database
    RedisDatabase& db = RedisDatabase::getInstance();
    
    // checkcommand
    if(cmd == "PING") {
        response << "Pong\r\n";
    } else if(cmd == "ECHO") {

    } else{
        response << "Error: Unknown copmmand \r\n";
    }

    return response.str();
}