#ifndef CONTEXT_SWITCH_H
#define CONTEXT_SWITCH_H

#include "common/PCB.h"

namespace datacenteros {

class ContextSwitch {
private:
    int totalContextSwitches;
    int contextSwitchTime;

public:
    explicit ContextSwitch(int overhead = 1);

    void switchProcess(PCB& current, PCB& next);

    int getTotalContextSwitches() const;

    int getContextSwitchTime() const;

    void reset();

    void displayStats() const;
};

}

#endif