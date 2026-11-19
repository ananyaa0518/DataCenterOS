#include "synchronization/SynchronizationManager.h"

#include <iostream>

namespace datacenteros {

SynchronizationManager::SynchronizationManager()
    : sharedResource(0) {}

void SynchronizationManager::incrementResource() {
    mutex.lock();

    sharedResource++;

    mutex.unlock();
}

int SynchronizationManager::getResource() const {
    return sharedResource;
}

void SynchronizationManager::demonstrate() {
    std::cout << "\nSynchronization Demonstration\n";

    std::cout << "Initial shared resource: "
              << sharedResource << "\n";

    incrementResource();
    incrementResource();
    incrementResource();

    std::cout << "After protected updates: "
              << sharedResource << "\n";
}

}