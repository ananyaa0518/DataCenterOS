#ifndef CONTEXT_SWITCH_H
#define CONTEXT_SWITCH_H

#include <array>
#include <cstdint>
#include <unordered_map>

namespace datacenteros {

struct CPUContext {

    uint64_t programCounter = 0;

    std::array<uint64_t, 8> registers{};

};

struct ContextSwitchStats {

    uint64_t switchCount = 0;

    uint64_t overheadCycles = 0;

};

class ContextSwitcher {

private:

    std::unordered_map<int, CPUContext> savedContexts;

    int currentProcessId = -1;

    uint64_t overheadPerSwitch;

    ContextSwitchStats stats;

public:

    explicit ContextSwitcher(uint64_t overhead = 5);

    void dispatchFirst(int processId, CPUContext& cpu);

    bool switchTo(int nextProcessId, CPUContext& cpu);

    int getCurrentProcess() const;

    ContextSwitchStats getStats() const;

};

}

#endif