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

    //Delete altered or non-exsisting files and folders
    READ src;
    src.setPath("C:\\Users\\zeyna\\Desktop\\UpdateTest");
    std::string url = "http://qayidiss.lovestoblog.com/data.txt", filename = "data.json";
    if (downloadFile(url, filename)) {
        std::cout << "Download successful!" << std::endl;
    } else {
        std::cout << "Download failed!" << std::endl;
    }
    std::ifstream f("data.json");
    json data = json::parse(f);
    f.close();
    std::vector<std::pair<std::string, std::string> >file, folder;
    auto& pt = data["files"];
    for(const auto& [key, value] : pt.items()){ file.push_back({key, value}); }
    pt = data["folders"];
    for(const auto& [key, value] : pt.items()){ folder.push_back({key, value});}

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


}