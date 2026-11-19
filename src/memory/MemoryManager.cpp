#include "memory/MemoryManager.h"

#include <iostream>

namespace datacenteros {

MemoryManager::MemoryManager(int totalFrames)
    : frameCount(totalFrames) {
    if (frameCount < 1) {
        frameCount = 1;
    }

    frames.resize(frameCount, nullptr);
}

MemoryManager::~MemoryManager() {
    reset();
}

bool MemoryManager::accessPage(int pageId, int processId) {
    // Page already exists in memory
    if (pageTable.contains(pageId)) {
        stats.pageHits++;
        return true;
    }

    // Page fault
    stats.pageFaults++;

    // Find an empty frame
    for (int i = 0; i < frameCount; i++) {
        if (frames[i] == nullptr) {
            frames[i] = new Page(pageId, processId);

            pageTable.mapPage(pageId, i);
            fifoQueue.push(i);

            return false;
        }
    }

    // FIFO replacement
    int frameToReplace = fifoQueue.front();
    fifoQueue.pop();

    Page* oldPage = frames[frameToReplace];

    if (oldPage != nullptr) {
        pageTable.removePage(oldPage->pageId);
        delete oldPage;
        stats.replacements++;
    }

    frames[frameToReplace] = new Page(pageId, processId);

    pageTable.mapPage(pageId, frameToReplace);
    fifoQueue.push(frameToReplace);

    return false;
}

void MemoryManager::displayMemory() const {
    std::cout << "\n========== MEMORY ==========\n";

    for (int i = 0; i < frameCount; i++) {
        std::cout << "Frame " << i << ": ";

        if (frames[i] != nullptr) {
            std::cout << "Page " << frames[i]->pageId
                      << " (PID " << frames[i]->processId << ")";
        } else {
            std::cout << "Empty";
        }

        std::cout << "\n";
    }

    std::cout << "Page Hits: " << stats.pageHits << "\n";
    std::cout << "Page Faults: " << stats.pageFaults << "\n";
    std::cout << "Replacements: " << stats.replacements << "\n";

    std::cout << "==========================\n";
}

MemoryStats MemoryManager::getStats() const {
    return stats;
}

int MemoryManager::getPageFaults() const {
    return stats.pageFaults;
}

int MemoryManager::getPageHits() const {
    return stats.pageHits;
}

void MemoryManager::reset() {
    for (int i = 0; i < frameCount; i++) {
        delete frames[i];
        frames[i] = nullptr;
    }

    while (!fifoQueue.empty()) {
        fifoQueue.pop();
    }

    pageTable.clear();
    stats = MemoryStats{};
}

}