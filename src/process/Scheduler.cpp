#include "process/Scheduler.h"

#include <algorithm>
#include <queue>
#include <iostream>

namespace datacenteros {

SchedulingResult Scheduler::FCFS(std::vector<PCB>& processes) {
    SchedulingResult result;

    if (processes.empty()) {
        return result;
    }

    // Sort processes by arrival time
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

    for (auto& process : processes) {

        // CPU remains idle if no process has arrived
        if (currentTime < process.arrivalTime) {
            currentTime = process.arrivalTime;
        }

        process.state = ProcessState::RUNNING;

        int waitingTime = currentTime - process.arrivalTime;

        currentTime += process.burstTime;

        int completionTime = currentTime;
        int turnaroundTime = completionTime - process.arrivalTime;

        process.remainingTime = 0;
        process.state = ProcessState::TERMINATED;

        totalWaitingTime += waitingTime;
        totalTurnaroundTime += turnaroundTime;

        result.executionOrder.push_back(process.pid);
    }

    result.averageWaitingTime =
        totalWaitingTime / processes.size();

    result.averageTurnaroundTime =
        totalTurnaroundTime / processes.size();

    result.totalExecutionTime = currentTime;

    return result;
}


// ---------------- ROUND ROBIN ----------------

SchedulingResult Scheduler::RoundRobin(
    std::vector<PCB>& processes,
    int timeQuantum
) {
    SchedulingResult result;

    if (processes.empty() || timeQuantum <= 0) {
        return result;
    }

    // Reset remaining time for a fresh simulation
    for (auto& process : processes) {
        process.remainingTime = process.burstTime;
        process.state = ProcessState::READY;
    }

    // Sort by arrival time
    std::sort(processes.begin(), processes.end(),
        [](const PCB& a, const PCB& b) {
            if (a.arrivalTime == b.arrivalTime) {
                return a.pid < b.pid;
            }
            return a.arrivalTime < b.arrivalTime;
        });

    std::queue<int> readyQueue;

    std::vector<int> completionTime(processes.size(), 0);
    std::vector<int> firstResponseTime(processes.size(), -1);

    int currentTime = 0;
    int completed = 0;
    int nextProcess = 0;

    // Add processes that have arrived at time 0
    while (nextProcess < static_cast<int>(processes.size()) &&
           processes[nextProcess].arrivalTime <= currentTime) {

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

                    readyQueue.push(nextProcess);
                    nextProcess++;
                }
            }

            continue;
        }

        int index = readyQueue.front();
        readyQueue.pop();

        PCB& process = processes[index];

        process.state = ProcessState::RUNNING;

        // Calculate response time on first execution
        if (firstResponseTime[index] == -1) {
            firstResponseTime[index] =
                currentTime - process.arrivalTime;
        }

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

    for (int i = 0; i < static_cast<int>(processes.size()); i++) {

        int turnaroundTime =
            completionTime[i] - processes[i].arrivalTime;

        int waitingTime =
            turnaroundTime - processes[i].burstTime;

        totalWaitingTime += waitingTime;
        totalTurnaroundTime += turnaroundTime;
    }

    result.averageWaitingTime =
        totalWaitingTime / processes.size();

    result.averageTurnaroundTime =
        totalTurnaroundTime / processes.size();

    result.totalExecutionTime = currentTime;

    return result;
}

}