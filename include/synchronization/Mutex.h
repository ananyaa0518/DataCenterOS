#ifndef MUTEX_H
#define MUTEX_H

#include <mutex>

namespace datacenteros {

class Mutex {
private:
    std::mutex mutex;

public:
    void lock();

    void unlock();

    bool tryLock();
};

}

#endif