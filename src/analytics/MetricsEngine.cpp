#include "analytics/MetricsEngine.h"

#include <iostream>

namespace datacenteros {

SystemMetrics MetricsEngine::calculate(
    const std::vector<PCB>& processes,
    const SchedulingResult& scheduling,
    const MemoryStats& memory,
    const DiskScheduleResult& disk
) const {
    SystemMetrics metrics;

    metrics.totalProcesses = static_cast<int>(processes.size());

    for (const auto& process : processes) {
        if (process.state == ProcessState::TERMINATED) {
            metrics.completedProcesses++;
        }
    }

    metrics.averageWaitingTime =
        scheduling.averageWaitingTime;

    metrics.averageTurnaroundTime =
        scheduling.averageTurnaroundTime;

    metrics.totalExecutionTime =
        scheduling.totalExecutionTime;

    metrics.pageFaults = memory.pageFaults;
    metrics.pageHits = memory.pageHits;

    metrics.diskHeadMovement =
        disk.totalHeadMovement;

    return metrics;
}

void MetricsEngine::display(const SystemMetrics& metrics) const {
    std::cout << "\n========== SYSTEM METRICS ==========\n";

    std::cout << "Total Processes: "
              << metrics.totalProcesses << "\n";

    std::cout << "Completed Processes: "
              << metrics.completedProcesses << "\n";

    std::cout << "Average Waiting Time: "
              << metrics.averageWaitingTime << "\n";

    std::cout << "Average Turnaround Time: "
              << metrics.averageTurnaroundTime << "\n";

    std::cout << "Total Execution Time: "
              << metrics.totalExecutionTime << "\n";

    std::cout << "Page Faults: "
              << metrics.pageFaults << "\n";

    std::cout << "Page Hits: "
              << metrics.pageHits << "\n";

    std::cout << "Disk Head Movement: "
              << metrics.diskHeadMovement << "\n";

    std::cout << "==================================\n";
}

}