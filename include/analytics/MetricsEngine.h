#ifndef METRICS_ENGINE_H
#define METRICS_ENGINE_H

#include <vector>

#include "common/PCB.h"
#include "process/Scheduler.h"
#include "memory/MemoryManager.h"
#include "disk/DiskScheduler.h"

namespace datacenteros {

struct SystemMetrics {
    int totalProcesses = 0;
    int completedProcesses = 0;

    double averageWaitingTime = 0.0;
    double averageTurnaroundTime = 0.0;

    int totalExecutionTime = 0;

    int pageFaults = 0;
    int pageHits = 0;

    int diskHeadMovement = 0;
};

class MetricsEngine {
public:
    SystemMetrics calculate(
        const std::vector<PCB>& processes,
        const SchedulingResult& scheduling,
        const MemoryStats& memory,
        const DiskScheduleResult& disk
    ) const;

    void display(const SystemMetrics& metrics) const;
};

}

#endif