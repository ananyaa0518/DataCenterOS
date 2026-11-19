#include "process/Scheduler.h"
#include "process/ContextSwitch.h"

#include <algorithm>
#include <queue>
#include <iostream>

namespace datacenteros {

SchedulingResult Scheduler::FCFS(std::vector<PCB>& processes) {
    SchedulingResult result;

    if (processes.empty()) {
        return result;
    }

    // Prevent re-executing if all processes have already terminated
    bool anyToRun = false;
    for (const auto& process : processes) {
        if (process.state != ProcessState::TERMINATED && process.remainingTime > 0) {
            anyToRun = true;
            break;
        }
    }

    if (!anyToRun) {
        std::cout << "All processes have already completed execution.\n"
                  << "Please reset processes before running scheduling again.\n";
        return result;
    }

    // Sort processes by arrival time, then PID
    std::sort(processes.begin(), processes.end(),
        [](const PCB& a, const PCB& b) {
            if (a.arrivalTime == b.arrivalTime) {
                return a.pid < b.pid;
            }
            return a.arrivalTime < b.arrivalTime;
        });

    int currentTime = 0;
    double totalWaitingTime = 0;
    double totalTurnaroundTime = 0;
    int scheduledCount = 0;

    ContextSwitch contextSwitcher(1);
    PCB* lastProcess = nullptr;

    for (auto& process : processes) {
        if (process.state == ProcessState::TERMINATED || process.remainingTime <= 0) {
            continue;
        }

        // CPU remains idle if no process has arrived
        if (currentTime < process.arrivalTime) {
            currentTime = process.arrivalTime;
        }

        // Context switch when switching to a different process
        if (lastProcess != nullptr && lastProcess->pid != process.pid) {
            contextSwitcher.switchProcess(*lastProcess, process);
        } else {
            process.state = ProcessState::RUNNING;
        }

        int waitingTime = currentTime - process.arrivalTime;
        currentTime += process.burstTime;

        int completionTime = currentTime;
        int turnaroundTime = completionTime - process.arrivalTime;

        process.remainingTime = 0;
        process.state = ProcessState::TERMINATED;

        totalWaitingTime += waitingTime;
        totalTurnaroundTime += turnaroundTime;
        scheduledCount++;

        result.executionOrder.push_back(process.pid);
        lastProcess = &process;
    }

    if (scheduledCount > 0) {
        result.averageWaitingTime = totalWaitingTime / scheduledCount;
        result.averageTurnaroundTime = totalTurnaroundTime / scheduledCount;
    }

    result.totalExecutionTime = currentTime;
    result.contextSwitches = contextSwitcher.getTotalContextSwitches();

    return result;
}


// ---------------- ROUND ROBIN ----------------

SchedulingResult Scheduler::RoundRobin(
    std::vector<PCB>& processes,
    int timeQuantum
) {
    SchedulingResult result;

    if (processes.empty()) {
        std::cout << "No processes to schedule.\n";
        return result;
    }

    if (timeQuantum <= 0) {
        std::cout << "Invalid time quantum. Time quantum must be greater than 0.\n";
        return result;
    }

    // Prevent re-executing if all processes have already terminated
    bool anyToRun = false;
    for (const auto& process : processes) {
        if (process.state != ProcessState::TERMINATED && process.remainingTime > 0) {
            anyToRun = true;
            break;
        }
    }

    if (!anyToRun) {
        std::cout << "All processes have already completed execution.\n"
                  << "Please reset processes before running scheduling again.\n";
        return result;
    }

    // Sort by arrival time, then PID
    std::sort(processes.begin(), processes.end(),
        [](const PCB& a, const PCB& b) {
            if (a.arrivalTime == b.arrivalTime) {
                return a.pid < b.pid;
            }
            return a.arrivalTime < b.arrivalTime;
        });

    std::queue<int> readyQueue;
    std::vector<int> completionTime(processes.size(), 0);

    int currentTime = 0;
    int completed = 0;
    int nextProcess = 0;

    ContextSwitch contextSwitcher(1);
    int lastRunningIndex = -1;

    // Advance time to first process arrival if idle
    if (nextProcess < static_cast<int>(processes.size()) &&
        processes[nextProcess].arrivalTime > currentTime) {
        currentTime = processes[nextProcess].arrivalTime;
    }

    // Add processes that have arrived at or before currentTime
    while (nextProcess < static_cast<int>(processes.size()) &&
           processes[nextProcess].arrivalTime <= currentTime) {
        processes[nextProcess].state = ProcessState::READY;
        readyQueue.push(nextProcess);
        nextProcess++;
    }

    while (completed < static_cast<int>(processes.size())) {

        // CPU idle if no process is ready
        if (readyQueue.empty()) {
            if (nextProcess < static_cast<int>(processes.size())) {
                currentTime = processes[nextProcess].arrivalTime;

                while (nextProcess < static_cast<int>(processes.size()) &&
                       processes[nextProcess].arrivalTime <= currentTime) {
                    processes[nextProcess].state = ProcessState::READY;
                    readyQueue.push(nextProcess);
                    nextProcess++;
                }
            } else {
                break;
            }
            continue;
        }

        int index = readyQueue.front();
        readyQueue.pop();

        PCB& process = processes[index];

        // Trigger context switch only when switching to a different process
        if (lastRunningIndex != -1 && lastRunningIndex != index) {
            contextSwitcher.switchProcess(processes[lastRunningIndex], process);
        } else {
            process.state = ProcessState::RUNNING;
        }
        lastRunningIndex = index;

        // Run process for quantum or until it finishes
        int executionTime = std::min(
            timeQuantum,
            process.remainingTime
        );

        currentTime += executionTime;
        process.remainingTime -= executionTime;

        // Record execution
        result.executionOrder.push_back(process.pid);

        // Add newly arrived processes to ready queue
        while (nextProcess < static_cast<int>(processes.size()) &&
               processes[nextProcess].arrivalTime <= currentTime) {
            processes[nextProcess].state = ProcessState::READY;
            readyQueue.push(nextProcess);
            nextProcess++;
        }

        // Check if process has completed
        if (process.remainingTime == 0) {
            process.state = ProcessState::TERMINATED;
            completionTime[index] = currentTime;
            completed++;
        } else {
            process.state = ProcessState::READY;
            readyQueue.push(index);
        }
    }

    double totalWaitingTime = 0;
    double totalTurnaroundTime = 0;

    for (size_t i = 0; i < processes.size(); i++) {
        int turnaroundTime = completionTime[i] - processes[i].arrivalTime;
        int waitingTime = turnaroundTime - processes[i].burstTime;

        totalWaitingTime += waitingTime;
        totalTurnaroundTime += turnaroundTime;
    }

    if (!processes.empty()) {
        result.averageWaitingTime = totalWaitingTime / processes.size();
        result.averageTurnaroundTime = totalTurnaroundTime / processes.size();
    }

    result.totalExecutionTime = currentTime;
    result.contextSwitches = contextSwitcher.getTotalContextSwitches();

    return result;
}

}