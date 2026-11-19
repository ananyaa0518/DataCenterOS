#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "process/ProcessManager.h"
#include "process/Scheduler.h"
#include "memory/MemoryManager.h"
#include "filesystem/FileSystem.h"
#include "synchronization/SynchronizationManager.h"
#include "resource/DeadlockManager.h"
#include "analytics/MetricsEngine.h"

namespace datacenteros {

class Simulator {
private:
    ProcessManager processManager;
    Scheduler scheduler;

    MemoryManager memoryManager;
    FileSystem fileSystem;

    SynchronizationManager synchronizationManager;
    DeadlockManager resourceManager;

    MetricsEngine metricsEngine;

public:
    Simulator();

    void runFCFS();

    void runRoundRobin(int timeQuantum);

    void displayProcesses();

    ProcessManager& getProcessManager();

    MemoryManager& getMemoryManager();

    FileSystem& getFileSystem();

    SynchronizationManager& getSynchronizationManager();

    DeadlockManager& getResourceManager();
};

}

#endif