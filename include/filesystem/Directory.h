#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <string>
#include <vector>

namespace datacenteros {

struct Directory {
    std::string name;
    std::vector<std::string> files;

    explicit Directory(const std::string& directoryName)
        : name(directoryName) {}
};

}

#endif