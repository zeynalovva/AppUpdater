#include <iostream>
#include <vector>
#include "../Libraries/Headers/essentialibs.h"
#include "../Libraries/Headers/addresses.h"
#include "../Libraries/Headers/checksum.h"
using namespace std::filesystem;
using json = nlohmann::json;
void checker(){
    READ src;
    src.setPath("C:\\Users\\zeyna\\Desktop\\SSHClient");
    if(!exists(src.getPath())){
        std::cerr<<"The path does not exsit!";
        return;
    }
    if(exists(src.getPath())
        && is_directory(src.getPath())){
        for(const auto& i : recursive_directory_iterator(src.getPath())){
            src.addList(i.path());
        }
    }
    json data;
    std::vector<path>v = src.getList();
    for(auto i : v){
        path k = relative(i, src.getPath());
        if(is_regular_file(i))
            data["files"][k.generic_string()] = (checksum(i));
        if(is_directory(i))
            data["folders"].push_back(k.generic_string());
    }
    std::ofstream file("data.json");
    file << data.dump(4);
    file.close();
    std::cout<<"DONE";
}