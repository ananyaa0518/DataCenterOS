#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "process/ProcessManager.h"
#include "process/Scheduler.h"
#include "disk/DiskScheduler.h"
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
    DiskScheduler diskScheduler;

    MemoryManager memoryManager;
    FileSystem fileSystem;

    SynchronizationManager synchronizationManager;
    DeadlockManager resourceManager;

    MetricsEngine metricsEngine;

    std::vector<DiskRequest> diskRequests;
    SchedulingResult lastSchedulingResult;
    DiskScheduleResult lastDiskResult;

    void displayDiskResult(const DiskScheduleResult& result) const;

public:
    Simulator();

    void runFCFS();

    void runRoundRobin(int timeQuantum);

    void displayProcesses();

    void resetProcesses();

    void addDiskRequest(int track, int processId = 0);

    void runDiskFCFS(int initialHead);

    void runDiskSSTF(int initialHead);

    void displayDiskRequests() const;

    void clearDiskRequests();

    void displayMetrics();

    void resetSimulation();

    ProcessManager& getProcessManager();

    MemoryManager& getMemoryManager();

    FileSystem& getFileSystem();

    SynchronizationManager& getSynchronizationManager();

    DeadlockManager& getResourceManager();

    DiskScheduler& getDiskScheduler();

    MetricsEngine& getMetricsEngine();
};

}

#endif