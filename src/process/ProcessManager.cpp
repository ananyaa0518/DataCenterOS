#include "process/ProcessManager.h"

#include <iostream>

namespace datacenteros {

ProcessManager::ProcessManager() {
    nextPID = 100;
}

int ProcessManager::createProcess(
    const std::string& name,
    int arrivalTime,
    int burstTime,
    int priority
) {
    if (burstTime <= 0 || arrivalTime < 0) {
        std::cout << "Invalid process parameters.\n";
        return -1;
    }

    int pid = nextPID++;

    PCB process(
        pid,
        name,
        arrivalTime,
        burstTime,
        priority
    );

    process.state = ProcessState::READY;

    processTable.push_back(process);

    std::cout << "Process created successfully!\n";
    std::cout << "PID: " << pid << "\n";
    std::cout << "Name: " << name << "\n";

    return pid;
}

PCB* ProcessManager::getProcess(int pid) {
    for (auto& process : processTable) {
        if (process.pid == pid) {
            return &process;
        }
    }

    return nullptr;
}

const std::vector<PCB>& ProcessManager::getAllProcesses() const {
    return processTable;
}

bool ProcessManager::updateState(
    int pid,
    ProcessState newState
) {
    PCB* process = getProcess(pid);

    if (process == nullptr) {
        return false;
    }

    process->state = newState;
    return true;
}

bool ProcessManager::terminateProcess(int pid) {
    PCB* process = getProcess(pid);

    if (process == nullptr) {
        return false;
    }

    process->state = ProcessState::TERMINATED;
    process->remainingTime = 0;

    return true;
}

void ProcessManager::displayProcesses() const {
    std::cout << "\n========== PROCESS TABLE ==========\n";

    for (const auto& process : processTable) {
        std::cout << "PID: " << process.pid
                  << " | Name: " << process.name
                  << " | Arrival: " << process.arrivalTime
                  << " | Burst: " << process.burstTime
                  << " | Remaining: " << process.remainingTime
                  << " | Priority: " << process.priority
                  << "\n";
    }

    std::cout << "================================\n";
}

}