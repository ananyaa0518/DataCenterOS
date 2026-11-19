#include "filesystem/FileSystem.h"

#include <iostream>

namespace datacenteros {

bool FileSystem::createFile(const std::string& name) {
    if (name.empty() || files.find(name) != files.end()) {
        return false;
    }

    files.emplace(name, File(name));
    return true;
}

bool FileSystem::writeFile(
    const std::string& name,
    const std::string& content
) {
    auto it = files.find(name);

    if (it == files.end()) {
        return false;
    }

    it->second.content = content;
    it->second.size = static_cast<int>(content.size());

    return true;
}

std::string FileSystem::readFile(const std::string& name) const {
    auto it = files.find(name);

    if (it == files.end()) {
        return "";
    }

    return it->second.content;
}

bool FileSystem::deleteFile(const std::string& name) {
    return files.erase(name) > 0;
}

void FileSystem::listFiles() const {
    std::cout << "\n========== FILE SYSTEM ==========\n";

    if (files.empty()) {
        std::cout << "No files found.\n";
    }

    for (const auto& entry : files) {
        std::cout << "File: " << entry.second.name
                  << " | Size: " << entry.second.size << " bytes\n";
    }

    std::cout << "==============================\n";
}

bool FileSystem::exists(const std::string& name) const {
    return files.find(name) != files.end();
}

}