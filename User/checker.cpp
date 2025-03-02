#include <iostream>
#include <algorithm>
#include <fstream>
#include <curl/curl.h>
#include "../Libraries/Headers/essentialibs.h"
#include "../Libraries/Headers/addresses.h"
#include "../Libraries/Headers/checksum.h"



using namespace std::filesystem;
using json = nlohmann::json;

bool find(std::vector<std::pair<std::string, std::string>>v, std::string folder_path){
    for(const auto& [key, value] : v){
        if(value  == folder_path) return 0;
    }
    return 1;
}



std::string translator(std::string pth){
    std::string URL = "";
    for(int i = 0;i<pth.size();i++){
        if(pth[i] == ' ') URL+="%20";
        else if(pth[i] == '!') URL+="%21";
        else if(pth[i] == '#') URL+="%23";
        else if(pth[i] == '$') URL+="%24";
        else if(pth[i] == '%') URL+="%25";
        else if(pth[i] == '&') URL+="%26";
        else if(pth[i] == '+') URL+="%2B";
        else if(pth[i] == ',') URL+="%2C";
        else if(pth[i] == '/') URL+="%2F";
        else if(pth[i] == ':') URL+="%3A";
        else if(pth[i] == ';') URL+="%3B";
        else if(pth[i] == '=') URL+="%3D";
        else if(pth[i] == '?') URL+="%3F";
        else if(pth[i] == '@') URL+="%40";
        else if(pth[i] == '[') URL+="%5B";
        else if(pth[i] == ']') URL+="%5D";
        else URL+=pth[i];
    }
    return URL;
}


bool find(std::vector<std::pair<std::string, std::string>>v, std::string file_path, std::string hash){
    for(const auto& [key, value] : v){
        if(key == file_path){
            return value != hash;
        }
    }
    return 1;
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    std::ofstream* file = static_cast<std::ofstream*>(userp);
    file->write(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}

bool downloadFile(const std::string& url, const std::string& filename) {
    CURL* curl = curl_easy_init();
    if (!curl) return false;

    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) return false;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);
    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    return (res == CURLE_OK);
}


int main(){

    string symb = "/";
    #ifdef _WIN32
        symb = "\\";
    #endif
    std::string server = "http://192.168.152.129/test/";
    READ src;
    src.setPath("C:\\Users\\zeyna\\Desktop\\UpdateTest");
    std::string filename = "data.json";
    if (downloadFile(server + "data.json", filename)) {
        std::cout << "Download successful: Hashtable" << std::endl;
    } else {
        std::cout << "Download failed: Hashtable" << std::endl;
    }
    std::ifstream f("data.json");
    json data = json::parse(f);
    f.close();
    std::vector<std::pair<std::string, std::string> >file, folder;
    auto& pt = data["files"];
    for(const auto& [key, value] : pt.items()){ file.push_back({key, value}); }
    pt = data["folders"];
    for(const auto& [key, value] : pt.items()){ folder.push_back({key, value});}


    //Delete altered or non-exsisting files and folders


    for(const auto& i : recursive_directory_iterator(src.getPath())){
        path t = relative(i, src.getPath());

        if(is_directory(i)){
            if(find(folder, t.generic_string()))
                remove_all(i);                   
        }
        else{
            if(find(file, t.generic_string(), checksum(i)))
                remove(i);
        }
    }

    //Create non-exsisting folders
    for(auto [key, value] : folder){
        for(int i = 0;i<value.size();i++){
            if(value[i] == '/' or value[i] == '\\') value[i] = symb[0];
        }
        std::string pth = src.getPath() + symb + value;     
        if(!exists(pth)){
            create_directories(pth);
            std::cout<<"Directory created: "<<pth<<std::endl;
        }
    }

    //Download files from the web-server
    for(auto [key, value] : file){
        std::string saveKey = key;
        for(int i = 0;i<key.size();i++){
            if(key[i] == '/' or key[i] == '\\') key[i] = symb[0];
        }
        std::string pth = src.getPath() + symb + key; 
        if(!exists(pth)){
            if (downloadFile(server + translator(saveKey), pth)) {
                std::cout << "Download successful: " << saveKey << std::endl;
            } else {
                std::cout << "Download failed!" << std::endl;
            }
        }
    }
    

}