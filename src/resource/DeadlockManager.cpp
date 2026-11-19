#include "resource/DeadlockManager.h"

#include <iostream>

namespace datacenteros {

DeadlockManager::DeadlockManager(int total)
    : totalResources(total),
      availableResources(total) {
    if (totalResources < 0) {
        totalResources = 0;
        availableResources = 0;
    }
}

bool DeadlockManager::allocate(int processId, int amount) {
    if (processId <= 0 || amount <= 0 || amount > availableResources) {
        return false;
    }

    allocatedResources[processId] += amount;
    availableResources -= amount;

    return true;
}

bool DeadlockManager::release(int processId, int amount) {
    if (processId <= 0 || amount <= 0) {
        return false;
    }

    auto it = allocatedResources.find(processId);

    if (it == allocatedResources.end() ||
        amount > it->second) {
        return false;
    }

    it->second -= amount;
    availableResources += amount;

    if (it->second == 0) {
        allocatedResources.erase(it);
    }

    return true;
}

int DeadlockManager::getAvailableResources() const {
    return availableResources;
}

int DeadlockManager::getAllocatedResources(int processId) const {
    auto it = allocatedResources.find(processId);

    if (it == allocatedResources.end()) {
        return 0;
    }

    return it->second;
}

void DeadlockManager::displayResources() const {
    std::cout << "\n========== RESOURCES ==========\n";
    std::cout << "Total Resources: " << totalResources << "\n";
    std::cout << "Available: " << availableResources << "\n";

    for (const auto& entry : allocatedResources) {
        std::cout << "PID " << entry.first
                  << " allocated: " << entry.second << "\n";
    }

    std::cout << "============================\n";
}

}