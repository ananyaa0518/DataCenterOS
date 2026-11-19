#ifndef PROCESS_STATE_H
#define PROCESS_STATE_H

namespace datacenteros {

enum class ProcessState {
    NEW,
    READY,
    RUNNING,
    WAITING,
    TERMINATED
};

}

#endif