#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include "common/PCB.h"

namespace datacenteros {

struct SchedulingResult {
    std::vector<int> executionOrder;

    double averageWaitingTime = 0.0;
    double averageTurnaroundTime = 0.0;

    int totalExecutionTime = 0;
    int contextSwitches = 0;
};

class Scheduler {
public:
    SchedulingResult FCFS(std::vector<PCB>& processes);

    SchedulingResult RoundRobin(
        std::vector<PCB>& processes,
        int timeQuantum
    );
};

}

#endif