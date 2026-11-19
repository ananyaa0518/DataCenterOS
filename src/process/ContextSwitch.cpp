#include "process/ContextSwitch.h"

#include <iostream>

namespace datacenteros {

ContextSwitch::ContextSwitch(int overhead)
    : totalContextSwitches(0),
      contextSwitchTime(overhead) {
}

void ContextSwitch::switchProcess(PCB& current, PCB& next) {
    if (current.pid == next.pid) {
        return;
    }

    // Save current process state if it has not terminated
    if (current.state != ProcessState::TERMINATED) {
        current.state = ProcessState::READY;
    }

    // Restore next process state
    next.state = ProcessState::RUNNING;

    // Count context switch
    totalContextSwitches++;

    std::cout << "[Context Switch] P"
              << current.pid << " -> P"
              << next.pid << " (Overhead: "
              << contextSwitchTime << " unit)\n";
}

int ContextSwitch::getTotalContextSwitches() const {
    return totalContextSwitches;
}

int ContextSwitch::getContextSwitchTime() const {
    return contextSwitchTime;
}

void ContextSwitch::reset() {
    totalContextSwitches = 0;
}

void ContextSwitch::displayStats() const {
    std::cout << "\n========== CONTEXT SWITCH ==========\n";
    std::cout << "Total Context Switches: "
              << totalContextSwitches << "\n";
    std::cout << "Context Switch Overhead: "
              << contextSwitchTime << "\n";
    std::cout << "=================================\n";
}

}