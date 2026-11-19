#include "synchronization/Mutex.h"

namespace datacenteros {

void Mutex::lock() {
    mutex.lock();
}

void Mutex::unlock() {
    mutex.unlock();
}

bool Mutex::tryLock() {
    return mutex.try_lock();
}

}