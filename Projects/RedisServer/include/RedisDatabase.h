#ifndef REDIS_DATABAS_H
#define REDIS_DATABAS_H

#include <string>
#include <mutex>
#include <unordered_map>
#include <vector>

class RedisDatabase {
public:
    static  RedisDatabase& getInstance(); // get singleton instance
    // persistance : dump / load the database in a file
    bool dump(const std::string& filename);
    bool load(const std::string& filename);
private:
    RedisDatabase() = default; // constructor only in the good scope
    ~RedisDatabase() = default; // destructor only in the good scope
    RedisDatabase(const RedisDatabase&) = delete; //Copy is not allowed (RedisDatabase b = a;  // error)
    RedisDatabase& operator= (const RedisDatabase&) = delete; //Not allowed to assign an object to another RedisDatabase a; RedisDatabase b;a = b;   // this uses operator=
    
    std::mutex db_mutex;
    std::unordered_map<std::string, std::string> kv_store;
    std::unordered_map<std::string, std::vector<std::string>> list_store; // the first is a string, the second a vector of strings
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> hash_store; // so the first item is a string and the second is a kv_store
};


#endif