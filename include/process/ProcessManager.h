#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include <vector>
#include "common/PCB.h"

namespace datacenteros {

class ProcessManager {
private:
    std::vector<PCB> processTable;
    int nextPID;

public:
    ProcessManager();

    int createProcess(
        const std::string& name,
        int arrivalTime,
        int burstTime,
        int priority = 1
    );

    PCB* getProcess(int pid);

    std::vector<PCB>& getAllProcesses();

    const std::vector<PCB>& getAllProcesses() const;

    bool updateState(int pid, ProcessState newState);

    bool terminateProcess(int pid);

    void resetProcesses();

    void clearProcesses();

    void displayProcesses() const;
};

}

#endif