#ifndef PCB_H
#define PCB_H

#include <string>
#include "common/ProcessState.h"

namespace datacenteros {

struct PCB {
    int pid;
    std::string name;

    int arrivalTime;
    int burstTime;
    int remainingTime;

    int priority;

    ProcessState state;

    PCB(int processId, const std::string& processName,
        int arrival, int burst, int processPriority = 1)
        : pid(processId),
          name(processName),
          arrivalTime(arrival),
          burstTime(burst),
          remainingTime(burst),
          priority(processPriority),
          state(ProcessState::NEW) {
    }
};

}

#endif