//
//  main.cpp
//  Task-2.2-Proxy
//
//  Created by Маргарет  on 31.07.2024.
//

#include <iostream>
#include <map>
#include <memory>

class VeryHeavyDatabase {
public:
    std::string GetData(const std::string& key) const noexcept {
        return "VeryHeavyDatabase: " + key;
    }
};

class OneShotDB : public VeryHeavyDatabase {
public:
    explicit OneShotDB (std::unique_ptr<VeryHeavyDatabase> real_object, size_t shots) : real_object_(std::move(real_object)), shots_(shots){}
    
    std::string GetData(const std::string& key) noexcept {
        if(cache.find(key) == cache.end() && limit_shots <= shots_) {
            limit_shots +=1;
            return "value";
        } else {
            return "error";
        }
    }
private:
    std::unique_ptr<VeryHeavyDatabase> real_object_;
    size_t shots_ = 0;
    size_t limit_shots = 1;
    std::map<std::string,std::string> cache;
    
};

int main(int argc, const char * argv[]) {
    auto ptr = std::make_unique<VeryHeavyDatabase>();
    auto limit_db = OneShotDB(std::move(ptr), 2);
    std::cout << limit_db.GetData("key") << std::endl;
    std::cout << limit_db.GetData("key") << std::endl;
    std::cout << limit_db.GetData("key") << std::endl;
    return 0;
}
