#include "process/ContextSwitch.h"

#include <stdexcept>

namespace datacenteros {

ContextSwitcher::ContextSwitcher(uint64_t overhead)
    : overheadPerSwitch(overhead) {
}

void ContextSwitcher::dispatchFirst(
    int processId,
    CPUContext& cpu
) {

    if (currentProcessId != -1) {
        throw std::logic_error(
            "A process is already running"
        );
    }

    currentProcessId = processId;

    auto it = savedContexts.find(processId);

    if (it != savedContexts.end()) {
        cpu = it->second;
    }
    else {
        cpu = CPUContext{};
    }
}

bool ContextSwitcher::switchTo(
    int nextProcessId,
    CPUContext& cpu
) {

    if (currentProcessId == -1) {
        dispatchFirst(nextProcessId, cpu);
        return false;
    }

    if (currentProcessId == nextProcessId) {
        return false;
    }

    // Save current process state.
    savedContexts[currentProcessId] = cpu;

    // Restore next process state.
    auto it = savedContexts.find(nextProcessId);

    if (it != savedContexts.end()) {
        cpu = it->second;
    }
    else {
        cpu = CPUContext{};
    }

    currentProcessId = nextProcessId;

    stats.switchCount++;

    stats.overheadCycles += overheadPerSwitch;

    return true;
}

int ContextSwitcher::getCurrentProcess() const {
    return currentProcessId;
}

ContextSwitchStats ContextSwitcher::getStats() const {
    return stats;
}

}