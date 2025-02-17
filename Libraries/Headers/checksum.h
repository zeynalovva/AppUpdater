#ifndef CHECKSUM_H
#define CHECKSUM_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "essentialibs.h"


using namespace std;
namespace fs = filesystem;
using json = nlohmann::json;


std::string checksum(const fs::path& filePath);


#endif