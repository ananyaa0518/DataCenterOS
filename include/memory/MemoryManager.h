#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <vector>
#include <queue>

#include "memory/Page.h"
#include "memory/PageTable.h"

namespace datacenteros {

struct MemoryStats {
    int pageHits = 0;
    int pageFaults = 0;
    int replacements = 0;
};

class MemoryManager {
private:
    int frameCount;

    std::vector<Page*> frames;
    std::queue<int> fifoQueue;

    PageTable pageTable;

    MemoryStats stats;

public:
    explicit MemoryManager(int totalFrames);

    ~MemoryManager();

    bool accessPage(int pageId, int processId);

    void displayMemory() const;

    MemoryStats getStats() const;

    int getPageFaults() const;

    int getPageHits() const;

    void reset();
};

}

#endif