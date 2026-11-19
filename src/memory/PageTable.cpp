#include "memory/PageTable.h"

namespace datacenteros {

bool PageTable::contains(int pageId) const {
    return pageToFrame.find(pageId) != pageToFrame.end();
}

int PageTable::getFrame(int pageId) const {
    auto it = pageToFrame.find(pageId);

    if (it == pageToFrame.end()) {
        return -1;
    }

    return it->second;
}

void PageTable::mapPage(int pageId, int frameId) {
    pageToFrame[pageId] = frameId;
}

void PageTable::removePage(int pageId) {
    pageToFrame.erase(pageId);
}

void PageTable::clear() {
    pageToFrame.clear();
}

}