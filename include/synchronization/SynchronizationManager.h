#ifndef SYNCHRONIZATION_MANAGER_H
#define SYNCHRONIZATION_MANAGER_H

#include "synchronization/Mutex.h"

namespace datacenteros {

class SynchronizationManager {
private:
    Mutex mutex;
    int sharedResource;

public:
    SynchronizationManager();

    void incrementResource();

    int getResource() const;

    void demonstrate();
};

}

#endif