#ifndef ADDRESSES_H
#define ADDRESSES_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include <iostream>
#include <vector>
#include "essentialibs.h"
using namespace std::filesystem;

class EXPORT READ {
private:
    std::string sourcePath;
    std::vector<path>list;
public:
    READ();
    void addList(path newPath);
    std::vector<path> getList();
    void setPath(std::string comingPath);
    std::string getPath();
};


#endif