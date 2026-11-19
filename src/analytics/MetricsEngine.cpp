#include "analytics/MetricsEngine.h"

#include <iostream>
#include <iomanip>

namespace datacenteros {

SystemMetrics MetricsEngine::calculate(
    const std::vector<PCB>& processes,
    const SchedulingResult& scheduling,
    const MemoryStats& memory,
    const DiskScheduleResult& disk
) const {
    SystemMetrics metrics;

    metrics.totalProcesses = static_cast<int>(processes.size());

    int totalBurstTime = 0;
    for (const auto& process : processes) {
        if (process.state == ProcessState::TERMINATED) {
            metrics.completedProcesses++;
            totalBurstTime += process.burstTime;
        }
    }

    metrics.averageWaitingTime = scheduling.averageWaitingTime;
    metrics.averageTurnaroundTime = scheduling.averageTurnaroundTime;
    metrics.totalExecutionTime = scheduling.totalExecutionTime;
    metrics.contextSwitches = scheduling.contextSwitches;

    if (metrics.totalExecutionTime > 0) {
        metrics.cpuUtilization = (static_cast<double>(totalBurstTime) / metrics.totalExecutionTime) * 100.0;
        if (metrics.cpuUtilization > 100.0) {
            metrics.cpuUtilization = 100.0;
        }
    } else {
        metrics.cpuUtilization = 0.0;
    }

    metrics.pageFaults = memory.pageFaults;
    metrics.pageHits = memory.pageHits;
    metrics.pageReplacements = memory.replacements;

    metrics.diskHeadMovement = disk.totalHeadMovement;

    return metrics;
}

void MetricsEngine::display(const SystemMetrics& metrics) const {
    std::cout << "\n========== SYSTEM METRICS & ANALYTICS ==========\n";
    std::cout << "--- Process & CPU Scheduling ---\n";
    std::cout << "Total Processes:           " << metrics.totalProcesses << "\n";
    std::cout << "Completed Processes:       " << metrics.completedProcesses << "\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Average Waiting Time:      " << metrics.averageWaitingTime << " time units\n";
    std::cout << "Average Turnaround Time:   " << metrics.averageTurnaroundTime << " time units\n";
    std::cout << "Total Execution Time:      " << metrics.totalExecutionTime << " time units\n";
    std::cout << "Context Switches:          " << metrics.contextSwitches << "\n";
    std::cout << "CPU Utilization:           " << metrics.cpuUtilization << "%\n";

    std::cout << "\n--- Memory Management (Paging) ---\n";
    std::cout << "Page Hits:                 " << metrics.pageHits << "\n";
    std::cout << "Page Faults:               " << metrics.pageFaults << "\n";
    std::cout << "Page Replacements:         " << metrics.pageReplacements << "\n";

    std::cout << "\n--- Storage (Disk Scheduling) ---\n";
    std::cout << "Disk Head Movement:        " << metrics.diskHeadMovement << " tracks\n";
    std::cout << "================================================\n";
}

}