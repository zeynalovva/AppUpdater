#include <iostream>
#include <fstream>
#include "../Libraries/Headers/essentialibs.h"

size_t read_callback(void *ptr, size_t size, size_t nmemb, void *stream) {
    FILE *file = (FILE *)stream;
    return fread(ptr, size, nmemb, file);
}
void loader(){
    std::ifstream f("options.txt");
    if(!f.is_open()){
        std::cerr<<"Error occured while loading options!"<<std::endl;
        return;
    }

    std::string line;

    while(getline(f, line)){
        std::string k = "",t = "";
        bool flag = false;
        for(int i = 0;i<line.size();i++){
            if(flag == true){
                t+=line[i];
            }
            if(line[i] != '=' and flag == false){
                k+=line[i];
            }
            if(line[i] == '=') flag = true;
        }
        //if(k == "FTP_SERVER") ftp_url = t;
    }
}


int main() {
    //loader();
    const char *ftp_url = "ftp://ftpupload.net/htdocs/data.json"; 
    const char *username = "if0_36997317";
    const char *password = "hEQwR6EsdkMwS";
    const char *file_path = "data.json"; 
    CURL *curl;
    CURLcode res;
    FILE *file;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        file = fopen(file_path, "rb"); 
        if (!file) {
            std::cerr << "Failed to open file." << std::endl;
            return 1;
        }
        curl_easy_setopt(curl, CURLOPT_URL, ftp_url);
        curl_easy_setopt(curl, CURLOPT_USERPWD, (std::string(username) + ":" + password).c_str());
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl, CURLOPT_READDATA, file);
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "File uploaded successfully!" << std::endl;
        }

        fclose(file);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}
