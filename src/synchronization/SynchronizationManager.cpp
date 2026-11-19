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
    std::cout << "\n========== SYNCHRONIZATION DEMONSTRATION ==========\n";
    std::cout << "Note: This is a sequential simulation demonstrating\n";
    std::cout << "mutual exclusion (Mutex) critical section protection,\n";
    std::cout << "lock/unlock semantics, and deadlock prevention.\n\n";

    std::cout << "Initial shared resource value: "
              << sharedResource << "\n";

    std::cout << "\n1. Process 1 acquiring mutex lock and updating shared resource...\n";
    mutex.lock();
    sharedResource++;
    std::cout << "   [Process 1] Inside critical section. Shared resource: "
              << sharedResource << "\n";

    std::cout << "2. Process 2 attempting non-blocking tryLock() while mutex is held...\n";
    bool acquired = mutex.tryLock();
    if (!acquired) {
        std::cout << "   [Process 2] tryLock() returned FALSE -> Access safely prevented (no race condition)!\n";
    }

    std::cout << "3. Process 1 releasing mutex lock...\n";
    mutex.unlock();
    std::cout << "   [Process 1] Mutex unlocked.\n";

    std::cout << "4. Process 2 attempting tryLock() now that mutex is free...\n";
    if (mutex.tryLock()) {
        sharedResource++;
        std::cout << "   [Process 2] tryLock() succeeded! Shared resource: "
                  << sharedResource << "\n";
        mutex.unlock();
        std::cout << "   [Process 2] Mutex unlocked.\n";
    }

    std::cout << "\nFinal shared resource value: "
              << sharedResource << "\n";
    std::cout << "===================================================\n";
}

}