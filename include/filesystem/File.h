#ifndef FILE_H
#define FILE_H

#include <string>

namespace datacenteros {

struct File {
    std::string name;
    std::string content;
    int size;

    File(const std::string& fileName)
        : name(fileName), content(""), size(0) {}
};

}

#endif