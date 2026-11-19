#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H

#include <unordered_map>

namespace datacenteros {

class PageTable {
private:
    std::unordered_map<int, int> pageToFrame;

public:
    bool contains(int pageId) const;

    int getFrame(int pageId) const;

    void mapPage(int pageId, int frameId);

    void removePage(int pageId);

    void clear();
};

}

#endif