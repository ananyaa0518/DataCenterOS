#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <unordered_map>
#include <string>
#include <vector>

#include "filesystem/File.h"

namespace datacenteros {

class FileSystem {
private:
    std::unordered_map<std::string, File> files;

public:
    bool createFile(const std::string& name);

    bool writeFile(
        const std::string& name,
        const std::string& content
    );

    std::string readFile(const std::string& name) const;

    bool deleteFile(const std::string& name);

    void listFiles() const;

    bool exists(const std::string& name) const;
};

}

#endif