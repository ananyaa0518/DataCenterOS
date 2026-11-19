#include "simulation/Simulator.h"

#include <iostream>

namespace datacenteros {

Simulator::Simulator()
    : memoryManager(4),
      resourceManager(10) {
}

void Simulator::runFCFS() {
    std::cout << "\nRunning FCFS Simulation...\n";

    auto processes = processManager.getAllProcesses();

    if (processes.empty()) {
        std::cout << "No processes available.\n";
        return;
    }

    SchedulingResult result = scheduler.FCFS(processes);

    std::cout << "\nFCFS Execution Order:\n";

    for (int pid : result.executionOrder) {
        std::cout << "P" << pid << " -> ";
    }

    std::cout << "END\n";

    std::cout << "Average Waiting Time: "
              << result.averageWaitingTime << "\n";

    std::cout << "Average Turnaround Time: "
              << result.averageTurnaroundTime << "\n";

    std::cout << "Total Execution Time: "
              << result.totalExecutionTime << "\n";

    processManager.displayProcesses();
}

void Simulator::runRoundRobin(int timeQuantum) {
    std::cout << "\nRunning Round Robin Simulation...\n";

    auto processes = processManager.getAllProcesses();

    if (processes.empty()) {
        std::cout << "No processes available.\n";
        return;
    }

    SchedulingResult result =
        scheduler.RoundRobin(processes, timeQuantum);

    std::cout << "\nRound Robin Execution Order:\n";

    for (int pid : result.executionOrder) {
        std::cout << "P" << pid << " -> ";
    }

    std::cout << "END\n";

    std::cout << "Average Waiting Time: "
              << result.averageWaitingTime << "\n";

    std::cout << "Average Turnaround Time: "
              << result.averageTurnaroundTime << "\n";

    std::cout << "Total Execution Time: "
              << result.totalExecutionTime << "\n";

    processManager.displayProcesses();
}

void Simulator::displayProcesses() {
    processManager.displayProcesses();
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

}