#include "addresses.h"

READ::READ() {}

void READ::addList(path newPath){list.push_back(newPath);}
std::vector<path> READ::getList(){ return list;}
void READ::setPath(std::string comingPath){ sourcePath = comingPath;} 
std::string READ::getPath(){ return sourcePath;}