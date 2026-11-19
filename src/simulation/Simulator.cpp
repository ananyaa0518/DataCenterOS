#include "simulation/Simulator.h"

#include <iostream>

namespace datacenteros {

Simulator::Simulator()
    : memoryManager(4),
      resourceManager(10) {
}

void Simulator::runFCFS() {
    std::cout << "\nRunning FCFS Simulation...\n";

    auto& processes = processManager.getAllProcesses();

    if (processes.empty()) {
        std::cout << "No processes available. Please create a process first.\n";
        return;
    }

    lastSchedulingResult = scheduler.FCFS(processes);

    if (lastSchedulingResult.executionOrder.empty()) {
        return;
    }

    std::cout << "\nFCFS Execution Order:\n";

    for (size_t i = 0; i < lastSchedulingResult.executionOrder.size(); ++i) {
        std::cout << "P" << lastSchedulingResult.executionOrder[i];
        if (i + 1 < lastSchedulingResult.executionOrder.size()) {
            std::cout << " -> ";
        }
    }

    std::cout << " -> END\n";

    std::cout << "Context Switches: "
              << lastSchedulingResult.contextSwitches << "\n";

    std::cout << "Average Waiting Time: "
              << lastSchedulingResult.averageWaitingTime << " time units\n";

    std::cout << "Average Turnaround Time: "
              << lastSchedulingResult.averageTurnaroundTime << " time units\n";

    std::cout << "Total Execution Time: "
              << lastSchedulingResult.totalExecutionTime << " time units\n";

    processManager.displayProcesses();
}

void Simulator::runRoundRobin(int timeQuantum) {
    std::cout << "\nRunning Round Robin Simulation (Quantum = "
              << timeQuantum << ")...\n";

    auto& processes = processManager.getAllProcesses();

    if (processes.empty()) {
        std::cout << "No processes available. Please create a process first.\n";
        return;
    }

    lastSchedulingResult =
        scheduler.RoundRobin(processes, timeQuantum);

    if (lastSchedulingResult.executionOrder.empty()) {
        return;
    }

    std::cout << "\nRound Robin Execution Order:\n";

    for (size_t i = 0; i < lastSchedulingResult.executionOrder.size(); ++i) {
        std::cout << "P" << lastSchedulingResult.executionOrder[i];
        if (i + 1 < lastSchedulingResult.executionOrder.size()) {
            std::cout << " -> ";
        }
    }

    std::cout << " -> END\n";

    std::cout << "Context Switches: "
              << lastSchedulingResult.contextSwitches << "\n";

    std::cout << "Average Waiting Time: "
              << lastSchedulingResult.averageWaitingTime << " time units\n";

    std::cout << "Average Turnaround Time: "
              << lastSchedulingResult.averageTurnaroundTime << " time units\n";

    std::cout << "Total Execution Time: "
              << lastSchedulingResult.totalExecutionTime << " time units\n";

    processManager.displayProcesses();
}

void Simulator::displayProcesses() {
    processManager.displayProcesses();
}

void Simulator::resetProcesses() {
    processManager.resetProcesses();
    std::cout << "Processes reset to READY state with full burst time.\n";
}

void Simulator::addDiskRequest(int track, int processId) {
    if (track < 0) {
        std::cout << "Invalid track number. Track must be non-negative.\n";
        return;
    }

    int reqId = static_cast<int>(diskRequests.size()) + 1;
    diskRequests.emplace_back(reqId, track, processId);

    std::cout << "Disk request added: Request ID " << reqId
              << " for track " << track
              << " (PID: " << processId << ")\n";
}

void Simulator::displayDiskResult(const DiskScheduleResult& result) const {
    std::cout << "\nDisk Service Order: ";
    for (size_t i = 0; i < result.serviceOrder.size(); ++i) {
        std::cout << "Req" << result.serviceOrder[i];
        if (i + 1 < result.serviceOrder.size()) {
            std::cout << " -> ";
        }
    }

    std::cout << "\nHead Movement Path: ";
    for (size_t i = 0; i < result.headPath.size(); ++i) {
        std::cout << result.headPath[i];
        if (i + 1 < result.headPath.size()) {
            std::cout << " -> ";
        }
    }

    std::cout << "\nTotal Head Movement: "
              << result.totalHeadMovement << " tracks\n";
    std::cout << "Average Seek Distance: "
              << result.averageSeekDistance << " tracks/request\n";
}

void Simulator::runDiskFCFS(int initialHead) {
    if (initialHead < 0) {
        std::cout << "Invalid initial head position. Must be non-negative.\n";
        return;
    }

    if (diskRequests.empty()) {
        std::cout << "No disk requests available. Add requests first.\n";
        return;
    }

    std::cout << "\nRunning Disk FCFS Scheduling (Initial Head: "
              << initialHead << ")...\n";

    lastDiskResult = diskScheduler.FCFS(diskRequests, initialHead);
    displayDiskResult(lastDiskResult);
}

void Simulator::runDiskSSTF(int initialHead) {
    if (initialHead < 0) {
        std::cout << "Invalid initial head position. Must be non-negative.\n";
        return;
    }

    if (diskRequests.empty()) {
        std::cout << "No disk requests available. Add requests first.\n";
        return;
    }

    std::cout << "\nRunning Disk SSTF Scheduling (Initial Head: "
              << initialHead << ")...\n";

    lastDiskResult = diskScheduler.SSTF(diskRequests, initialHead);
    displayDiskResult(lastDiskResult);
}

void Simulator::displayDiskRequests() const {
    std::cout << "\n========== DISK REQUEST QUEUE ==========\n";
    if (diskRequests.empty()) {
        std::cout << "No pending disk requests.\n";
    }
    for (const auto& req : diskRequests) {
        std::cout << "Request ID: " << req.requestId
                  << " | Track: " << req.track
                  << " | Process ID: " << req.processId << "\n";
    }
    std::cout << "========================================\n";
}

void Simulator::clearDiskRequests() {
    diskRequests.clear();
    std::cout << "Disk request queue cleared.\n";
}

void Simulator::displayMetrics() {
    SystemMetrics metrics = metricsEngine.calculate(
        processManager.getAllProcesses(),
        lastSchedulingResult,
        memoryManager.getStats(),
        lastDiskResult
    );
    metricsEngine.display(metrics);
}

void Simulator::resetSimulation() {
    processManager.resetProcesses();
    memoryManager.reset();
    diskRequests.clear();
    lastSchedulingResult = SchedulingResult{};
    lastDiskResult = DiskScheduleResult{};
    std::cout << "\nSimulation reset complete: processes reset to READY, memory cleared, disk queue cleared.\n";
}

ProcessManager& Simulator::getProcessManager() {
    return processManager;
}

MemoryManager& Simulator::getMemoryManager() {
    return memoryManager;
}

FileSystem& Simulator::getFileSystem() {
    return fileSystem;
}

SynchronizationManager& Simulator::getSynchronizationManager() {
    return synchronizationManager;
}

DeadlockManager& Simulator::getResourceManager() {
    return resourceManager;
}

DiskScheduler& Simulator::getDiskScheduler() {
    return diskScheduler;
}

MetricsEngine& Simulator::getMetricsEngine() {
    return metricsEngine;
}

}