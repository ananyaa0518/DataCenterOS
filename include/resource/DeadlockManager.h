#ifndef DEADLOCK_MANAGER_H
#define DEADLOCK_MANAGER_H

#include <unordered_map>

namespace datacenteros {

class DeadlockManager {
private:
    int totalResources;
    int availableResources;

    std::unordered_map<int, int> allocatedResources;

public:
    explicit DeadlockManager(int total);

    bool allocate(int processId, int amount);

    bool release(int processId, int amount);

    int getAvailableResources() const;

    int getAllocatedResources(int processId) const;

    void displayResources() const;
};

}

#endif